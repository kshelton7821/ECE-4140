#ifndef __circbufferH_H
#define __circbufferH_H


#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
//Initialization Defines -------------------------------------------------------
//#include "initialization.c"
typedef struct {
    uint8_t* pu8t_buffer;
    size_t st_head;
    size_t st_tail;
    size_t st_capacity;
} circular_buffer_t;
//Circular Buffer Functions
void initBuffer(volatile circular_buffer_t *cb_circBuf, uint8_t *pu8t_buffer, size_t st_capacity);
int pushBuffer(volatile circular_buffer_t *cb_circBuf, uint8_t u8t_data);
int popBuffer(volatile circular_buffer_t *cb_circBuf, volatile uint8_t *pu8t_data);
int peekBuffer(volatile circular_buffer_t *cb_circBuf, volatile uint8_t *pu8t_data);

#endif