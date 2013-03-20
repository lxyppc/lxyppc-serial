#include "polarssl/config.h"

#ifdef POLARSSL_MEM_C

#ifdef  EMBEDDED_SYSTEM
#ifdef PRINTF
#undef PRINTF
#endif
#define PRINTF(...)
#define EXIT(x, reason, args...)     while(1);
#else
#define EXIT(x, reason, args...)     do{ printf(reason, ## args); exit(x);}while(0)
#endif

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

static unsigned char mem_pool[4096*4];
static unsigned short used_map[1];

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
            PRINTF("Static memory not enough\n");
        }else{
            free(p);
        }
}

void* x_mem_init(void)
{
    PRINTF("\nMemory pool inited\n");
    memcnt = 0;
    maxcnt = 0;
    xcnt = 0;
    alloc_cnt = 0;
    free_cnt = 0;
    MEMSET(mem_pool, 0 , sizeof(mem_pool));
    return NULL;
}

void show_free_links(void);
int max_mem_position(void);
void x_mem_free(void* pool)
{
    mem_list* t = first;
    int i;
    int step = 16;
    (void)pool;
    for(;t;){
        mem_list* x = t->next;
        free(t);
        t=x;
    }
    PRINTF("Memory pool free. cnt = %d(%d), max = %d, %d(%d)\n",memcnt,xcnt,maxcnt,alloc_cnt,free_cnt);
    PRINTF("max_mem_position() = %d\n",max_mem_position());
    for(i=0; i<alloc_cnt; i++){
        PRINTF("%d, ",used_map[i]);
        if( (i&15) == 15 ) PRINTF("\n");
    }
    if( (i&15) != 15 )PRINTF("\n");


    for(i=0; i<(int)sizeof(mem_pool); i+= step){
        int j;
        const char* mark = "_";
        for(j=0;j<step;j++){
            if(mem_pool[i+j]){
                mark = "*";
                break;
            }
        }
        PRINTF("%s",mark);
        if( ( (i/step)&63 ) == 63 ) PRINTF("\n");
    }
    if( ( (i/step)&63 ) != 63 ) PRINTF("\n");
    show_free_links();
    MEMSET(mem_pool, 0 , sizeof(mem_pool));
    first = NULL;
    last = NULL;
    alloc_cnt = 0;
    free_cnt = 0;
}

#define  RND1 16
#define  RND2 80
#define  RND3 140
#define  RND4 280
#define  RND5 560

unsigned char * p_pool = mem_pool;
typedef struct _mem_mark{
    //unsigned short length : 14;
    //unsigned short used : 1;
    //unsigned short alloc : 1;
    
    unsigned char  used;
    unsigned char  alloc;
    unsigned short length;
}mem_mark;

size_t size_cap(size_t size)
{
    if(size < RND1) return RND1;
    else if(size < RND2) return RND2;
    else if(size < RND3) return RND3;
    else if(size < RND4) return RND4;
    else if(size < RND5) return RND5;
    return size;
}

#define  get_nex_mark(mark) \
    (mark + mark->length/(sizeof(mem_mark)) + 1)

#define  mark_from_mem(p)   \
    ((mem_mark*)(p) - 1)

static mem_mark* skip_used(mem_mark* mark)
{
    while(mark->used){
        mark = get_nex_mark(mark);
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
    PRINTF("%s at %d, size = %d\n", desc, x, size);
    do{
        size_t mp = (unsigned char*)mark - mem_pool;
        size_t vp = mp + sizeof(mem_mark);
        (void)vp;
        PRINTF("Memory at %d(%d), len = %d, alloc = %d, used = %d\n", mp, vp, mark->length, mark->alloc, mark->used);

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
        mark = get_nex_mark(mark);
    }while(mark->alloc || mark->used);
    PRINTF("%d(%d), %d(%d), %d(%d), other(%d)",RND1,r1,RND2,r2,RND3,r3,r4);
    PRINTF("================\n");
}

void* _x_malloc(void* pool, size_t size)
{
    size_t s = size_cap(size);
    mem_mark* r = 0;
    mem_mark* mark = (mem_mark*)mem_pool;
    (void)pool;
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
            mark = get_nex_mark(mark);
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
    mem_mark* mark = mark_from_mem(p);
    if(mark->length > size) {
        display_mem_info("Re success", p, size);
        return p;
    }
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
    mem_mark* mark = mark_from_mem(p);
    mem_mark* next = get_nex_mark(mark);
    mark->used = 0;
    (void)pool;
    if(next->alloc == 0 && next->used == 0){
        //mark->alloc = 0;
    }
    display_mem_info("free", p, 0);
}

void  x_memset(void* p, int v, size_t len)
{
    unsigned char* x = (unsigned char*)p;
    while(len--) *x++ = (unsigned char)v;
}


typedef struct _mem_link{
    unsigned short next;
    unsigned short length;
}mem_link;

#define  link_to_mem(link)      ((void*)((link) + 1))
#define  mem_to_link(mem)       ((mem_link*)((char*)(mem) - sizeof(mem_link)))
#define  next_link(link)        ((mem_link*)((link)->next ? (link)->next + mem_pool : 0))
#define  add_link(link, link_new)   \
do{ \
    link_new->next = link ?  (unsigned char*)(link) - mem_pool: 0;\
    link = link_new;\
}while(0);

//static mem_link* s1_free = 0;
//static mem_link* s2_free = 0;
//static mem_link* s3_free = 0;
//static unsigned char* p_mem = mem_pool+12;

#define  s1_free        (*((mem_link**)(mem_pool)))
#define  s2_free        (*((mem_link**)(mem_pool+sizeof(mem_link))))
#define  s3_free        (*((mem_link**)(mem_pool+sizeof(mem_link)*2)))
#define  s4_free        (*((mem_link**)(mem_pool+sizeof(mem_link)*3)))
#define  s5_free        (*((mem_link**)(mem_pool+sizeof(mem_link)*4)))
#define  p_mem          (*((unsigned char**)(mem_pool+sizeof(mem_link)*5)))
#define  mem_start      ( mem_pool+sizeof(mem_link)*5+sizeof(unsigned char*) )

mem_link* check_round(mem_link* l1)
{
    mem_link* l2 = l1;
    while(l1 && l2){
        l1 = next_link(l1);
        l2 = next_link(l2);
        if(l2){
            l2 = next_link(l2);
        }
        if(l1 != 0 && l1 == l2){
            return l1;
        }
    }
    return 0;
}

void show_link(const char* name, mem_link* l){
    mem_link* x = check_round(l);
    int s = 0;
    if(!l) PRINTF("%s <null>\n", name);
    FFLUSH(stdout);
    for( ;l != 0; ){
        mem_link* n = next_link(l);
        PRINTF("%s: %p(%d)->%d (%p)\n",name, l, l->length, l->next, mem_pool+l->next);
        FFLUSH(stdout);
        if(x == n && x != 0){
            if(s){
                PRINTF("%s: %p -> %p <round>\n",name, l, n);
                break;
            }else{
                s = 1;
            }
        }
        l = n;
    }
    FFLUSH(stdout);
}

void show_free_links(void){
    show_link("s1", s1_free);
    show_link("s2", s2_free);
    show_link("s3", s3_free);
    show_link("s4", s4_free);
    show_link("s5", s5_free);
}

int max_mem_position(void)
{
    return  p_mem - mem_pool;
}

void* x_malloc__(void* pool, size_t size)
{
    size_t s = size_cap(size);
    void* m = 0;
    mem_link* link;
    if(p_mem == 0){
        p_mem = mem_start;
    }
    link = (mem_link*)p_mem;
    (void)pool;
    switch(s){
    case RND1:
        if(s1_free){
            m = link_to_mem(s1_free);
            s1_free = next_link(s1_free);
        }
        break;
    case RND2:
        if(s2_free){
            m = link_to_mem(s2_free);
            s2_free = next_link(s2_free);
        }
        break;
    case RND3:
        if(s3_free){
            m = link_to_mem(s3_free);
            s3_free = next_link(s3_free);
        }
        break;
    case RND4:
        if(s4_free){
            m = link_to_mem(s4_free);
            s4_free = next_link(s4_free);
        }
        break;
    case RND5:
        if(s5_free){
            m = link_to_mem(s5_free);
            s5_free = next_link(s5_free);
        }
        break;
    }
    if(m) return m;
    if(p_mem + s - mem_pool > (int)sizeof(mem_pool)) {
        EXIT(1, "mem fail, require %d\n", p_mem + s - mem_pool);
        return 0;
    }
    p_mem += (s + sizeof(mem_link));
    link->length = s;
    return link_to_mem(link);
}

void x_free__(void* pool, void*p)
{
    mem_link* link = mem_to_link(p);
    switch(link->length){
    case RND1:
        add_link(s1_free,link); break;
    case RND2:
        add_link(s2_free,link); break;
    case RND3:
        add_link(s3_free,link); break;
    case RND4:
        add_link(s4_free,link); break;
    case RND5:
        add_link(s5_free,link); break;
    default:
        PRINTF("memory will waste");
        break;
    }
    check_round(link);
    (void)pool;
}

void* x_realloc__(void* pool, void*p, size_t size)
{
    void* r = 0;
    mem_link* link = mem_to_link(p);
    if(link->length > size) {
        //display_mem_info("Re success", p, size);
        return p;
    }
    x_free__(pool,p);
    (void)pool;
    r = x_malloc__(pool, size);
    if(r){
        memcpy(r, p, link->length);
    }
    return r;
}

void* x_malloc(void* pool, size_t size)
{
    return x_malloc__(pool, size);
}

void* x_realloc(void* pool, void*p, size_t size)
{
    return x_realloc__(pool,p,size);
}

void x_free(void* pool, void*p)
{
    x_free__(pool, p);
}
#else   //POLARSSL_MEM_C
void* x_mem_init(void){ return 0;}
void x_mem_free(void* pool){ (void)pool; }
#endif  //POLARSSL_MEM_C

