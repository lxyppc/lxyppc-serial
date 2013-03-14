#include <polarssl/rsa.h>
#include <polarssl/md2.h>
#include <polarssl/md4.h>
#include <polarssl/md5.h>
#include <polarssl/sha1.h>
#include <polarssl/sha2.h>
#include <polarssl/sha4.h>
#include <polarssl/entropy.h>
#include <polarssl/ctr_drbg.h>
#include <polarssl/error.h>

#include <polarssl/config.h>

#include <math.h>
#include <stdlib.h>


#define  assert(x)		do{ if(x){}else{printf("Assert fail at line:%d\n", __LINE__ ); exit(-1);}  }while(0)
/*
 * 32-bit integer manipulation macros (big endian)
 */
#ifndef GET_UINT32_BE
#define GET_UINT32_BE(n,b,i)                            \
{                                                       \
    (n) = ( (uint32_t) (b)[(i)    ] << 24 )             \
        | ( (uint32_t) (b)[(i) + 1] << 16 )             \
        | ( (uint32_t) (b)[(i) + 2] <<  8 )             \
        | ( (uint32_t) (b)[(i) + 3]       );            \
}
#endif

#ifndef PUT_UINT32_BE
#define PUT_UINT32_BE(n,b,i)                            \
{                                                       \
    (b)[(i)    ] = (unsigned char) ( (n) >> 24 );       \
    (b)[(i) + 1] = (unsigned char) ( (n) >> 16 );       \
    (b)[(i) + 2] = (unsigned char) ( (n) >>  8 );       \
    (b)[(i) + 3] = (unsigned char) ( (n)       );       \
}
#endif

int unhexify(unsigned char *obuf, const char *ibuf)
{
    unsigned char c, c2;
    int len = strlen(ibuf) / 2;
    assert(!(strlen(ibuf) %1)); // must be even number of bytes

    while (*ibuf != 0)
    {
        c = *ibuf++;
        if( c >= '0' && c <= '9' )
            c -= '0';
        else if( c >= 'a' && c <= 'f' )
            c -= 'a' - 10;
        else if( c >= 'A' && c <= 'F' )
            c -= 'A' - 10;
        else
            assert( 0 );

        c2 = *ibuf++;
        if( c2 >= '0' && c2 <= '9' )
            c2 -= '0';
        else if( c2 >= 'a' && c2 <= 'f' )
            c2 -= 'a' - 10;
        else if( c2 >= 'A' && c2 <= 'F' )
            c2 -= 'A' - 10;
        else
            assert( 0 );

        *obuf++ = ( c << 4 ) | c2;
    }

    return len;
}

void hexify(unsigned char *obuf, const unsigned char *ibuf, int len)
{
    unsigned char l, h;

    while (len != 0)
    {
        h = (*ibuf) / 16;
        l = (*ibuf) % 16;

        if( h < 10 )
            *obuf++ = '0' + h;
        else
            *obuf++ = 'a' + h - 10;

        if( l < 10 )
            *obuf++ = '0' + l;
        else
            *obuf++ = 'a' + l - 10;

        ++ibuf;
        len--;
    }
    *obuf = 0;
}




/**
 * This function just returns data from rand().
 * Although predictable and often similar on multiple
 * runs, this does not result in identical random on
 * each run. So do not use this if the results of a
 * test depend on the random data that is generated.
 *
 * rng_state shall be NULL.
 */
static int rnd_std_rand( void *rng_state, unsigned char *output, size_t len )
{
    size_t i;

    if( rng_state != NULL )
        rng_state  = NULL;

    for( i = 0; i < len; ++i )
        output[i] = rand();

    return( 0 );
}

/**
 * This function only returns zeros
 *
 * rng_state shall be NULL.
 */
static int rnd_zero_rand( void *rng_state, unsigned char *output, size_t len )
{
    if( rng_state != NULL )
        rng_state  = NULL;

    memset( output, 0, len );

    return( 0 );
}

typedef struct
{
    unsigned char *buf;
    size_t length;
} rnd_buf_info;

/**
 * This function returns random based on a buffer it receives.
 *
 * rng_state shall be a pointer to a rnd_buf_info structure.
 * 
 * The number of bytes released from the buffer on each call to
 * the random function is specified by per_call. (Can be between
 * 1 and 4)
 *
 * After the buffer is empty it will return rand();
 */
static int rnd_buffer_rand( void *rng_state, unsigned char *output, size_t len )
{
    rnd_buf_info *info = (rnd_buf_info *) rng_state;
    size_t use_len;

    if( rng_state == NULL )
        return( rnd_std_rand( NULL, output, len ) );

    use_len = len;
    if( len > info->length )
        use_len = info->length;

    if( use_len )
    {
        memcpy( output, info->buf, use_len );
        info->buf += use_len;
        info->length -= use_len;
    }

    if( len - use_len > 0 )
        return( rnd_std_rand( NULL, output + use_len, len - use_len ) );

    return( 0 );
}

/**
 * Info structure for the pseudo random function
 *
 * Key should be set at the start to a test-unique value.
 * Do not forget endianness!
 * State( v0, v1 ) should be set to zero.
 */
typedef struct
{
    uint32_t key[16];
    uint32_t v0, v1;
} rnd_pseudo_info;

/**
 * This function returns random based on a pseudo random function.
 * This means the results should be identical on all systems.
 * Pseudo random is based on the XTEA encryption algorithm to
 * generate pseudorandom.
 *
 * rng_state shall be a pointer to a rnd_pseudo_info structure.
 */
static int rnd_pseudo_rand( void *rng_state, unsigned char *output, size_t len )
{
    rnd_pseudo_info *info = (rnd_pseudo_info *) rng_state;
    uint32_t i, *k, sum, delta=0x9E3779B9;
    unsigned char result[4];

    if( rng_state == NULL )
        return( rnd_std_rand( NULL, output, len ) );

    k = info->key;

    while( len > 0 )
    {
        size_t use_len = ( len > 4 ) ? 4 : len;
        sum = 0;

        for( i = 0; i < 32; i++ )
        {
            info->v0 += (((info->v1 << 4) ^ (info->v1 >> 5)) + info->v1) ^ (sum + k[sum & 3]);
            sum += delta;
            info->v1 += (((info->v0 << 4) ^ (info->v0 >> 5)) + info->v0) ^ (sum + k[(sum>>11) & 3]);
        }

        PUT_UINT32_BE( info->v0, result, 0 );
        memcpy( output, result, use_len );
        len -= use_len;
    }

    return( 0 );
}
               //                   1                   2                   3                   4                   5                   6                   7                   8                   9                   a                   b                   c                   d
               // 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
#define  PUB_N  "008a39fb7aff0b860d538c801dd48cf9e641ee3f0a7a467f3488dd56022ef7856e5aa405870e3edd48016ae5bf5f5b143eea2a211efde22081a719a55fab1944a87b58aa7a4075bb80013e3a0f2c712f10b99f4108bffe0bdbf7948b30f77c3320c1e921227c3202d9334f687b46344cc764164ecf58886f975fee1d640da0572b"
#define  PUB_E  "010001"
#define  PRI_N  PUB_N
#define  PRI_E  "3640d9d705e2050498056e87c6d46a8598dd253b3c910cfe96b5a13b8c29b4e2828b1c6c4d08199c588a17910ca15809f5a90185038b4cccf6c457277ca5974fa1f6e2593304337e881e8cddfac23c701074d535ab72414461ad748f66e744eb991174cd304c6c25ed413be7ddde47ef67c71b70883a92e6cb51a870b401d389"

void log_info(const char* desc, int r)
{
	char buf[1024];
	error_strerror(r,buf,1024);
	printf("%s = %d(%s)\n",desc,r,buf);
}

void log_buf(const char* desc, const unsigned char* buf, size_t len)
{
        unsigned char x[1024*4];
        hexify(x,buf,len);
        printf("%s(%d): %s\n",desc, len, x);
}

int main()
{
	unsigned char message_str[1000];
	unsigned char output[1000];
    unsigned char output_str[1000];
	unsigned char output_data[1000];
        unsigned char hash[1204] = {1,2,3,4,5,6,7,8,9,10};
    rsa_context ctx;
    size_t msg_len;
	size_t output_len = 0;
	int r = 0;
    rnd_pseudo_info rnd_info;

	memset( &rnd_info, 0, sizeof( rnd_pseudo_info ) );
	rsa_init( &ctx, RSA_PKCS_V15, 0 );

        ctx.len = 1024 / 8;
	mpi_read_string( &ctx.N, 16, PUB_N);//"b38ac65c8141f7f5c96e14470e851936a67bf94cc6821a39ac12c05f7c0b06d9e6ddba2224703b02e25f31452f9c4a8417b62675fdc6df46b94813bc7b9769a892c482b830bfe0ad42e46668ace68903617faf6681f4babf1cc8e4b0420d3c7f61dc45434c6b54e2c3ee0fc07908509d79c9826e673bf8363255adb0add2401039a7bcd1b4ecf0fbe6ec8369d2da486eec59559dd1d54c9b24190965eafbdab203b35255765261cd0909acf93c3b8b8428cbb448de4715d1b813d0c94829c229543d391ce0adab5351f97a3810c1f73d7b1458b97daed4209c50e16d064d2d5bfda8c23893d755222793146d0a78c3d64f35549141486c3b0961a7b4c1a2034f" );
	//mpi_read_string( &ctx.E, 16, "3" );
	mpi_read_string( &ctx.E, 16, PUB_E);
	mpi_read_string( &ctx.D, 16, PRI_E);
	
	r = rsa_check_pubkey( &ctx );
	log_info("rsa_check_pubkey", r);
	msg_len = unhexify( message_str, "4E636AF98E40F3ADCFCCB698F4E80B9F" );
        log_buf("raw_data", message_str,msg_len);
	r = rsa_pkcs1_encrypt( &ctx, &rnd_pseudo_rand, &rnd_info, RSA_PUBLIC, msg_len, message_str, output );
	log_info("rsa_pkcs1_encrypt", r);
	log_buf("enc_data", output,128);
	
	output_len = 0;
	r = rsa_pkcs1_decrypt( &ctx, RSA_PRIVATE, &output_len, output, output_data, 1000);
	log_info("rsa_pkcs1_decrypt", r);
	hexify( output_str, output_data, output_len);
        log_buf("dec_data", output_data, output_len);
        r = strcasecmp( (char *) output_str, (char*)"4E636AF98E40F3ADCFCCB698F4E80B9F" );
	printf("Result:%d\n",r);


        unhexify( output_data, "199ad6f4a1d593b57a5ef7e7f217661472f40cc8d5decbd8f8168f5d6bf3c4ca92d53ca000468324b8ebd2f8bff331d570dcdd21095895861639fd86a0c707ed69f5d23378701998dd304607de0193a0838c3f9ec6df1daaaf8817f3d8e71857edbb4b388376b11cb8b2cb85814b6370fd2cda688d30507d528a367a20576de6" );
        sha1(hash, 10, hash);
        //r = rsa_pkcs1_sign(&ctx, &rnd_pseudo_rand, &rnd_info, RSA_PRIVATE, SIG_RSA_SHA1, sizeof(hash), hash, output_data);
        //log_info("rsa_pkcs1_sign", r);
        //log_buf("sign", output_data, 128);
        r = rsa_pkcs1_verify(&ctx, RSA_PUBLIC, SIG_RSA_SHA1, sizeof(hash), hash, output_data);
        log_info("rsa_pkcs1_verify", r);
	rsa_free( &ctx );
	return 0;
}
int rsa_calc(const unsigned char* n, const unsigned char* e, const unsigned char* data, size_t bits, size_t e_len, unsigned char* output);
int rsa_calc_str(const char* n, const char* e, const unsigned char* data, unsigned char* output);

#define XX "0a15582a2c95e3a265a12b71a5c721f5e07f00f66e9360e496ca7bd6f31b433d0cb1fadb4a9dd50366491b8cb407d75ba0e52b0fee5ff71f3caf5bbefb421dfb0e59a45ff1c7de97ca3b40902cf3e4099150870179437ce4e414fbd0c0291c4b43331db77e06424c13ca6da4ad7e1b4eb9477ee9275d630783ce1196c7db6ce3"
int main2()
{
    unsigned char data[128] = {};
    unsigned char out_data[1024] = {};
    int r = 0;
    unhexify(data, XX);
    rsa_context ctx;
    rsa_init( &ctx, RSA_PKCS_V15, 0 );
    rsa_calc_str(PRI_N, PRI_E, data, out_data);
    log_info("rsa_calc_str", r);
    log_buf("dec_data", out_data, 128);
    rsa_free( &ctx );
    return 0;
}

