/**
  ******************************************************************************
  * @file    mem_util.c 
  * @author  lxyppc@gmail.com
  * @date    20-September-2012
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "mem_util.h"

__asm uint32_t init_stack(void)
{
    IMPORT  Stack_Mem
    ldr r0, = Stack_Mem
    mov    r2, sp
    movs   r1, #0xcc
init_stack_1
    subs   r2, r2, #1
    strb   r1, [r2]
    cmp    r2, r0
    bne    init_stack_1
    mov    r2, sp
    subs   r0, r2, r0
    bx lr
}

__asm uint32_t init_heap(void)
{
    IMPORT Heap_Mem
    IMPORT __heap_limit
    ldr     r0, = Heap_Mem
    ldr     r2, = __heap_limit
    movs    r1, #0xcc
init_heap_1
    adds    r0, r0, #1
    strb    r1, [r0]
    cmp     r2, r0
    bne     init_heap_1
    ldr     r0, = Heap_Mem
    subs    r0, r2, r0
    bx lr
}

__asm uint32_t stack_usage(void)
{
    IMPORT  Stack_Mem
    IMPORT  __initial_sp
    ldr     r0, = Stack_Mem
stack_usage_1
    adds    r0, r0, #1
    ldrb    r1, [r0]
    cmp     r1, #0xcc
    beq     stack_usage_1
    ldr     r1, = __initial_sp
    subs    r0, r1, r0
    bx      lr
}

__asm uint32_t heap_usage(void)
{
    IMPORT Heap_Mem
    IMPORT __heap_limit
    ldr     r1, = __heap_limit
heap_usage_1
    subs    r1, r1, #1
    ldrb    r0, [r1]
    cmp     r0, #0xcc
    beq     heap_usage_1
    ldr     r0, = Heap_Mem
    subs    r0, r1, r0
    bx      lr
}
