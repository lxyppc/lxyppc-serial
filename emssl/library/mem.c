#include "polarssl/config.h"

#ifdef POLARSSL_MEM_C
#include "polarssl/mem.h"

typedef struct _mem_list
{
	struct _mem_list* next;
	void* mem;
	size_t size;
}mem_list;

static mem_list* first = NULL;
static mem_list* last = NULL;
static int memcnt = 0;
static int maxcnt = 0;
static int xcnt = 0;
static int alloc_cnt = 0;
static int free_cnt = 0;


static unsigned short used_map[4096];

static unsigned char mem_pool[8192];

unsigned char* get_static_mem()
{
    return mem_pool;
}

int is_static_mem(void* p)
{
    size_t pos = (size_t)p;
    size_t start = (size_t)&mem_pool[0];
    size_t end = sizeof(mem_pool) + start;
    return pos >= start && pos < end;
}

static void add_mem(void*p , size_t size)
{
    mem_list* t = (mem_list*)malloc(sizeof(mem_list));
    memcnt += size;
    xcnt += size;
    if(maxcnt < memcnt){
        maxcnt = memcnt;
    }
    t->next = NULL;
    t->mem = p;
    t->size = size;
    if(last){
        last->next = t;
    }
    last = t;
    if(!first) first = t;

    used_map[alloc_cnt] = size;
    alloc_cnt++;
}

static void remove_mem(void* p)
{
    mem_list* t = first;
    for(;t;t=t->next){
        if(p == t->mem){
            memcnt -= t->size;
            t->mem = 0;
        }
    }
    free_cnt++;
}

void* x_malloc_(void* pool, size_t size)
{
    void* p = malloc(size);
    (void)pool;
    add_mem(p,size);
    return p;
}

void* x_realloc_(void* pool, void*p, size_t size){
    void* rp = 0;
    (void)pool;
    rp = realloc(p,size);
    remove_mem(p);
    add_mem(rp,size);
    return rp;
}

void x_free_( void* pool, void* p )
{
    (void)pool;
        remove_mem(p);
        if(is_static_mem(p)){
            printf("Static memory not enough\n");
        }else{
            free(p);
        }
}

void* x_mem_init()
{
	printf("\nMemory pool inited\n");
	memcnt = 0;
	maxcnt = 0;
        xcnt = 0;
        alloc_cnt = 0;
        free_cnt = 0;
	return NULL;
}

void x_mem_free(void* pool)
{
	mem_list* t = first;
	int i;
	(void)pool;
        memset(mem_pool, 0 , sizeof(mem_pool));
	for(;t;){
		mem_list* x = t->next;
		free(t);
		t=x;
	}
        printf("Memory pool free. cnt = %d(%d), max = %d, %d(%d)\n",memcnt,xcnt,maxcnt,alloc_cnt,free_cnt);
        for(i=0; i<alloc_cnt; i++){
                printf("%d, ",used_map[i]);
                if( (i&15) == 15 ) printf("\n");
        }
        if( (i&15) != 15 )printf("\n");
	first = NULL;
	last = NULL;
	alloc_cnt = 0;
	free_cnt = 0;
}

#define  RND1 16
#define  RND2 140
#define  RND3 280

unsigned char * p_pool = mem_pool;
typedef struct _mem_mark{
    unsigned short length : 14;
    unsigned short used : 1;
    unsigned short alloc : 1;
}mem_mark;

size_t size_cap(size_t size)
{
    if(size < RND1) return RND1;
    else if(size < RND2) return RND2;
    else if(size < RND3) return RND3;
    return size;
}


static mem_mark* skip_used(mem_mark* mark)
{
    while(mark->used){
        mark = mark + mark->length/2 + 1;
    }
    return mark;
}

static void display_mem_info(const char* desc, void* p, size_t size)
{
    size_t x = (unsigned char*)p - mem_pool;
    size_t r1 = 0;
    size_t r2 = 0;
    size_t r3 = 0;
    size_t r4 = 0;
    mem_mark* mark = (mem_mark*)mem_pool;
    printf("%s at %d, size = %d\n", desc, x, size);
    do{
        size_t mp = (unsigned char*)mark - mem_pool;
        size_t vp = mp + 2;
        (void)vp;
        //printf("Memory at %d(%d), len = %d, alloc = %d, used = %d\n", mp, vp, mark->length, mark->alloc, mark->used);

        switch(mark->length){
        case RND1:
            r1++; break;
        case RND2:
            r2++; break;
        case RND3:
            r3++; break;
        default:
            r4++; break;
        }
        mark = mark + mark->length/2 + 1;
    }while(mark->alloc || mark->used);
    printf("%d(%d), %d(%d), %d(%d), other(%d)",RND1,r1,RND2,r2,RND3,r3,r4);
    printf("================\n");
}

void* _x_malloc(void* pool, size_t size)
{
    (void)pool;
    size_t s = size_cap(size);
    mem_mark* r = 0;
    mem_mark* mark = (mem_mark*)mem_pool;
    do{
        mark = skip_used( mark );
        if(!mark->alloc){
            mark->alloc = 1;
            mark->used = 1;
            mark->length = s;
            r = mark;
        }else if(mark->length == s){
            mark->used = 1;
            r = mark;
        }else{
            mark = mark + mark->length/2 + 1;
            r = 0;
        }
    }while(r == 0);
    display_mem_info("Allocate", r+1, size);
    if( (unsigned char*)r + r->length > mem_pool + sizeof(mem_pool)){
        return 0;
    }
    if(size == 8){
        size = 1;
        return r + size;
    }
    return r+1;
}

void* _x_realloc(void* pool, void*p, size_t size)
{
    void* r = 0;
    mem_mark* mark = ((mem_mark*)p) - 1;
    if(mark->length > size) return p;
    mark->used = 0;
    display_mem_info("Re free", p, size);
    r = _x_malloc(pool, size);
    if(r){
        memcpy(r, p, mark->length);
    }
    return r;
}

void _x_free(void* pool, void*p)
{
    mem_mark* mark = ((mem_mark*)p) - 1;
    mem_mark* next = mark + mark->length/2 + 1;
    mark->used = 0;
    (void)pool;
    if(next->alloc == 0 && next->used == 0){
        //mark->alloc = 0;
    }
    display_mem_info("free", p, 0);
}


void* x_malloc(void* pool, size_t size)
{
    return _x_malloc(pool, size);
}

void* x_realloc(void* pool, void*p, size_t size)
{
    return _x_realloc(pool,p,size);
}

void x_free(void* pool, void*p)
{
    _x_free(pool, p);
}
#endif

