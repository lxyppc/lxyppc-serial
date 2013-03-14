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
#include "main.h"
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

int main(void)
{
    /* 2 bit for pre-emption priority, 2 bits for subpriority */
    unsigned char data[128] = {0};
    unsigned char out_data[1024] = {0};
    int r = 0;
    uint32_t tick;
    rsa_context ctx;
    enable_tick_count();
    unhexify(data, XX);
    x_mem_init();
    tick = get_tick_count();
    rsa_calc_str(PRI_N, PUB_E, data, out_data);
    tick = get_tick_count() - tick;
    //log_info("rsa_calc_str", r);
    //log_buf("dec_data", out_data, 128);
    x_mem_free(0);
    return 0;
}


void enable_tick_count(void)
{
    //RCC_ClocksTypeDef RCC_Clocks;
    //RCC_GetClocksFreq(&RCC_Clocks);
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    //tick_per_us = RCC_Clocks.SYSCLK_Frequency/1000000;
}

uint32_t get_tick_count(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    return DWT->CYCCNT;
}

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
