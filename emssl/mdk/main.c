/**
  ******************************************************************************
  * @file    main.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    20-September-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
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
#include <polarssl/mem.h>
#include <polarssl/config.h>
#include <polarssl/bn_mul.h>
#include <math.h>
#include <stdlib.h>

/** @addtogroup STM32F3-Discovery_Demo
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

void enable_tick_count(void);
uint32_t get_tick_count(void);

/* Private variables ---------------------------------------------------------*/

#define  assert(x)  if(!(x)){ while(1); }

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
    MPI_CHK(mpi_exp_mod( &V, &V, &E, &N, &RN ));
    MPI_CHK(mpi_write_binary( &V, output, l ));
cleanup:
    mpi_free( &N );
    mpi_free( &E );
    mpi_free( &RN );
    mpi_free( &V );
    return ret;
}

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


               //                   1                   2                   3                   4                   5                   6                   7                   8                   9                   a                   b                   c                   d
               // 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
#define  PUB_N  "008a39fb7aff0b860d538c801dd48cf9e641ee3f0a7a467f3488dd56022ef7856e5aa405870e3edd48016ae5bf5f5b143eea2a211efde22081a719a55fab1944a87b58aa7a4075bb80013e3a0f2c712f10b99f4108bffe0bdbf7948b30f77c3320c1e921227c3202d9334f687b46344cc764164ecf58886f975fee1d640da0572b"
#define  PUB_E  "010001"
#define  PRI_N  PUB_N
#define  PRI_E  "3640d9d705e2050498056e87c6d46a8598dd253b3c910cfe96b5a13b8c29b4e2828b1c6c4d08199c588a17910ca15809f5a90185038b4cccf6c457277ca5974fa1f6e2593304337e881e8cddfac23c701074d535ab72414461ad748f66e744eb991174cd304c6c25ed413be7ddde47ef67c71b70883a92e6cb51a870b401d389"

#define XX "0a15582a2c95e3a265a12b71a5c721f5e07f00f66e9360e496ca7bd6f31b433d0cb1fadb4a9dd50366491b8cb407d75ba0e52b0fee5ff71f3caf5bbefb421dfb0e59a45ff1c7de97ca3b40902cf3e4099150870179437ce4e414fbd0c0291c4b43331db77e06424c13ca6da4ad7e1b4eb9477ee9275d630783ce1196c7db6ce3"

void mpi_mul_hlp(size_t i, t_uint *s, t_uint *d, t_uint b);
//void mpi_mul_hlp( size_t i, t_uint *s, t_uint *d, t_uint b );

void asm_test(size_t i)
{
    while(i--){
        printf("123");
    }
}

t_uint a[4] = {0x11111111, 0x11111111,0x11111111,0x11111111,};
t_uint b[4] = {0x0000000c, 0x0000000c,0x11111111,0x11111111,};
t_uint c[8] = {0};

void init_stack(uint32_t* stack_end);
uint32_t stack_usage(uint32_t* stack_end, uint32_t* stack_start);
extern uint32_t __initial_sp;
extern uint32_t Stack_Mem;
volatile uint32_t stack_used = 0;
int main(void)
{
    /* 2 bit for pre-emption priority, 2 bits for subpriority */
    unsigned char data[128] = {0};
    unsigned char out_data[1024] = {0};
    int r = 0;
    uint32_t tick;
    rsa_context ctx;
    (void)r;
    (void)ctx;
    (void)tick;
    //asm_test(17);
    //mpi_mul_hlp(4, a, c+1, b[1]);
    //mpi_mul_hlp(4, a, c, b[0]);
    //enable_tick_count();
    unhexify(data, XX);
    x_mem_init();
    init_stack(&Stack_Mem);
    //tick = get_tick_count();
    rsa_calc_str(PRI_N, PRI_E, data, out_data);
    //tick = get_tick_count() - tick;
    //log_info("rsa_calc_str", r);
    //log_buf("dec_data", out_data, 128);
    x_mem_free(0);
    stack_used = stack_usage(&Stack_Mem, &__initial_sp);
    return 0;
}


#if defined(POLARSSL_HAVE_ASM)
#if defined(__arm__)
#warning POLARSSL_HAVE_ASM __arm__
#endif
#endif

#if defined(__TARGET_CPU_CORTEX_M3 )
#warning __TARGET_CPU_CORTEX_M3
#endif

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
