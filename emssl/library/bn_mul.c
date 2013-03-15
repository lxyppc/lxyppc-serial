#include <polarSSL/bn_mul.h>

#if defined(EXTERN_MUL_HELP)



#if  defined( __TARGET_CPU_CORTEX_M3 ) || defined( __TARGET_CPU_CORTEX_M4 ) 

__asm void mpi_mul_hlp(size_t i, t_uint *s, t_uint *d, t_uint b)
{
    // r0 = i, r3 = b
    push   {r4,r5,r6,r7,lr}
    mov    r5, #0    // carry, 
    b      loopend
loopstart
    ldr    r4, [r1], #4      // r4 = *s++
    mov    r6, #0            // r6 = 0
    umlal  r5, r6, r3, r4    // r6,r5 = r6,r5 + r3 * r4
    ldr    r7, [r2]          // r7 = *d
    adds   r7, r7, r5        // r7 = r7 + r5
    adc    r5, r6, #0        // r5 = r6 + carry
    str    r7, [r2], #4      // *d++ = r7
    sub    r0,r0,#1
loopend
    cmp    r0, #0
    bne    loopstart        // if(r0 != 0) goto loopstart
    //
again
    ldr    r1, [r2]         //
    adds   r1, r1, r5       //
    str    r1, [r2], #4     // *d = *d + r5; d++;
    adc    r5, r0, #0       //  r5 = 0 + carry
    cmp    r5, #0           //  if(r5 != 0)
    bne    again            //   goto again
    pop    {r4,r5,r6,r7,pc}
}

#endif  // defined( __TARGET_CPU_CORTEX_M3 ) || defined( __TARGET_CPU_CORTEX_M4 ) 

#if defined( __TARGET_CPU_CORTEX_M0 )

__asm void umlal_r5_r6_r3_r4()
{
    push  {r0 - r2, lr}
    movs  r2, #0
    uxth  r0, r3
    uxth  r1, r4
    muls  r0,r1,r0      // r0  = r3.low * r4.low
    adds  r5,r5,r0
    adcs  r6,r6,r2      //r6,r5 = r6,r5 + 0,r0

    lsrs   r0, r3, #16
    muls   r0,r1,r0     // r0 = r3.high * r4.low
    lsrs   r1, r0, #16  // r1 = r0.high >>16
    lsls   r0, r0, #16  // r0 = r0.low <<16
    adds  r5,r5,r0      
    adcs  r6,r6,r1      // r6,r5 = r6,r5 + r1,r0

    lsrs  r1, r4, #16   // r1 = r4.high
    lsrs  r0, r3, #16   // r0 = r3.high
    muls  r0,r1,r0      // r0 = r4.high * r3.high
    adds  r6,r6,r0      // r6,r5 = r6,r5 + r0,0

    uxth  r0, r3        // r0 = r3.low
    muls  r0,r1,r0      // r0 = r3.low * r4.high
    lsrs  r1, r0, #16   // r1 = r0.high >>16
    lsls  r0, r0, #16   // r0 = r0.low << 16
    adds  r5,r5,r0
    adcs  r6,r6,r1      // r6,r5 = r6,r5 + r1,r0
    
    pop  {r0 - r2, pc}
}

__asm void mpi_mul_hlp(size_t i, t_uint *s, t_uint *d, t_uint b)
{
    // r0 = i, r3 = b
    push   {r4,r5,r6,r7,lr}
    movs   r5, #0    // carry, 
    b      loopend
loopstart
    ldr     r4, [r1]          // r4 = *s++
    adds    r1,r1,#4
    movs    r6, #0            // r6 = 0
    bl     umlal_r5_r6_r3_r4
    ldr    r7, [r2]          // r7 = *d
    adds   r7, r7, r5        // r7 = r7 + r5
    str    r7, [r2]          // *d++ = r7
    movs   r7, #0
    adcs   r6, r6, r7        // r5 = r6 + carry
    mov    r5, r6
    adds   r2, r2, #4
    
    subs   r0,r0,#1
loopend
    cmp    r0, #0
    bne    loopstart        // if(r0 != 0) goto loopstart
    //
again
    ldr    r1, [r2]         //
    adds   r1, r1, r5       //
    str    r1, [r2]         // *d = *d + r5; d++;
    movs   r5, #0
    adcs   r5, r5, r0       //  r5 = 0 + carry
    adds   r2, r2, #4
    cmp    r5, #0           //  if(r5 != 0)
    bne    again            //   goto again
    pop    {r4,r5,r6,r7,pc}
}

#endif   // defined( __TARGET_CPU_CORTEX_M0 )


#endif  // defined(EXTERN_MUL_HELP)

