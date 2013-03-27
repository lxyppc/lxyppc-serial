/**
  ******************************************************************************
  * @file    mem_util.c 
  * @author  lxyppc@gmail.com
  ******************************************************************************
  */

#ifndef MEM_UTIL_H
#define MEM_UTIL_H
#include "stdint.h"

uint32_t init_stack(void);
uint32_t init_heap(void);

uint32_t stack_usage(void);
uint32_t heap_usage(void);





#endif
