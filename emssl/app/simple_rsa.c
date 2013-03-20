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

/**
  RSA algorithm only use the big numbers
 */

int rsa_calc(const unsigned char* n, const unsigned char* e, const unsigned char* data, size_t bits, size_t e_len, unsigned char* output)
{
    int ret = 0;
    mpi N = {0,0,0};
    mpi E = {0,0,0};
    mpi V = {0,0,0};
    mpi RN = {0,0,0};
    MPI_CHK(mpi_read_binary(&N,n,bits/8));
    MPI_CHK(mpi_read_binary(&E,e,e_len));
    MPI_CHK(mpi_read_binary(&V,data,bits/8));
    if( mpi_cmp_mpi( &V, &N ) >= 0 ){
        ret = POLARSSL_ERR_RSA_BAD_INPUT_DATA;
        goto cleanup;
    }
    MPI_CHK(mpi_exp_mod( &V, &V, &E, &N, &RN ));
    MPI_CHK(mpi_write_binary( &V, output, bits/8 ));
cleanup:
    mpi_free( &N );
    mpi_free( &E );
    mpi_free( &RN );
    mpi_free( &V );
    return ret;
}


int rsa_calc_str(const char* n, const char* e, const unsigned char* data, unsigned char* output)
{
    int ret = 0;
    mpi N = {0,0,0};
    mpi E = {0,0,0};
    mpi V = {0,0,0};
    mpi RN = {0,0,0};
    size_t l = 128;
    int j;
    MPI_CHK(mpi_read_string(&N,16,n));
    for(j=N.n;j>=0;j--){
        if(N.p[j-1])break;
    }
    l = j * sizeof(t_uint);
    MPI_CHK(mpi_read_string(&E,16,e));
    MPI_CHK(mpi_read_binary(&V,data, l));
    if( mpi_cmp_mpi( &V, &N ) >= 0 ){
        ret = POLARSSL_ERR_RSA_BAD_INPUT_DATA;
        goto cleanup;
    }
    printf("===========================>>>>>>>\n");
    MPI_CHK(mpi_exp_mod( &V, &V, &E, &N, &RN ));
    printf("<<<<<<<===========================\n");
    MPI_CHK(mpi_write_binary( &V, output, l ));
cleanup:
    mpi_free( &N );
    mpi_free( &E );
    mpi_free( &RN );
    mpi_free( &V );
    return ret;
}


