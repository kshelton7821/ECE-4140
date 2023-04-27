/*
* Author: Keaton Shelton
* Date: 2/16/2023
*
* Abstract: This is a circular buffer implementation along with a small test program
*
* Revisions:
* 01ks 2/16/2023: Original
* 02ks 2/23/2023: Final
*/
//Uncomment bellow for deployment
//#include "embsysS20.h"
#include "circbufferH.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

/*Circular buffer parameters
* pu8t_buffer: pointer to the buffer
* st_head: index of the head of the buffer
* st_tail: index of the tail of the buffer
* st_apacity: capacity of the buffer
*/

//cb_circBuf: pointer to the circular buffer, pu8t_buffer: pointer to the buffer, st_capacity: capacity of the buffer
void initBuffer(volatile circular_buffer_t *cb_circBuf, uint8_t *pu8t_buffer, size_t st_capacity) 
{
    //Initialize the circular buffer
    cb_circBuf->pu8t_buffer = pu8t_buffer;
    cb_circBuf->st_head = 0;
    cb_circBuf->st_tail = 0;
    cb_circBuf->st_capacity = st_capacity;
}

//cb_circBuf: pointer to the circular buffer, u8t_data: u8t_data to be added to the buffer
int pushBuffer(volatile circular_buffer_t *cb_circBuf, uint8_t u8t_data) 
{
    //Wrap the head around the buffer
    size_t st_next = (cb_circBuf->st_head + 1) & (cb_circBuf->st_capacity - 1);
    //Check if the buffer is full
    if (st_next == cb_circBuf->st_tail) 
    {
        return -1; // buffer is full return -1;
    }
    //Add the u8t_data to the buffer
    cb_circBuf->pu8t_buffer[cb_circBuf->st_head] = u8t_data;
    //Update the head
    cb_circBuf->st_head = st_next;
    return 0; // return 0 if successful
}

//cb_circBuf: pointer to the circular buffer, u8t_data: pointer to the u8t_data to be pulled from the buffer
int popBuffer(volatile circular_buffer_t *cb_circBuf, volatile uint8_t *u8t_data) 
{
    //Check if the buffer is empty
    if (cb_circBuf->st_tail == cb_circBuf->st_head) {
        return -1; // buffer is empty return -1;
    }
    //Pull the u8t_data from the buffer
    *u8t_data = cb_circBuf->pu8t_buffer[cb_circBuf->st_tail];
    //Update the tail
    cb_circBuf->st_tail = (cb_circBuf->st_tail + 1) & (cb_circBuf->st_capacity - 1);
    return 0; // return 0 if successful
}

//cb_circBuf: pointer to the circular buffer, u8t_data: pointer to the u8t_data to be peeked from the buffer
int peekBuffer(volatile circular_buffer_t *cb_circBuf, volatile uint8_t *u8t_data) {
    //Check if the buffer is empty
    if (cb_circBuf->st_tail == cb_circBuf->st_head) {
        return -1; // buffer is empty return -1;
    }
    //Pull the u8t_data from the buffer
    *u8t_data = cb_circBuf->pu8t_buffer[cb_circBuf->st_tail];
    return 0; // return 0 if successful
}

//Test Program
//Comment this out for deployment to the board
/*
int main() 
{
    size_t st_size = 4;
    uint8_t u8t_buffer[st_size], u8t_data1 = 1, u8t_data2 = 2, u8t_data3 = 3, u8t_data4 = 4, u8t_data5 = 5, u8t_dataBlank = 0;
    int8_t i8t_status;
    circular_buffer_t cb;

    //Initialize the buffer and load data
    initBuffer(&cb, u8t_buffer, st_size);
    i8t_status = pushBuffer(&cb, u8t_data1);
    printf("Push: %d Status: %d \n", u8t_data1, i8t_status);
    i8t_status = pushBuffer(&cb, u8t_data2);
    printf("Push: %d Status: %d \n", u8t_data2, i8t_status);
    i8t_status = pushBuffer(&cb, u8t_data3);
    printf("Push: %d Status: %d \n", u8t_data3, i8t_status);

    //Test buffer full
    i8t_status = pushBuffer(&cb, u8t_data4);
    printf("Push: %d Status: %d \n", u8t_data4, i8t_status);
    i8t_status = pushBuffer(&cb, u8t_data5);
    printf("Push: %d Status: %d \n", u8t_data5, i8t_status);

    //Test buffer pop and peek
    i8t_status = popBuffer(&cb, &u8t_dataBlank);
    printf("Pop: %d Status: %d \n", u8t_dataBlank, i8t_status);
    u8t_dataBlank = 0;
    popBuffer(&cb, &u8t_dataBlank);
    printf("Pop: %d Status: %d \n", u8t_dataBlank, i8t_status);
    u8t_dataBlank = 0;
    peekBuffer(&cb, &u8t_dataBlank);
    printf("Peek: %d Status: %d \n", u8t_dataBlank, i8t_status);
    u8t_dataBlank = 0;
    popBuffer(&cb, &u8t_dataBlank);
    printf("Pop: %d Status: %d \n", u8t_dataBlank, i8t_status);
    u8t_dataBlank = 0;
    //Test buffer empty
    i8t_status = peekBuffer(&cb, &u8t_dataBlank);
    printf("Peek: %d Status: %d \n", u8t_dataBlank, i8t_status);
    i8t_status = popBuffer(&cb, &u8t_dataBlank);
    printf("Pop: %d Status: %d \n", u8t_dataBlank, i8t_status);

    printf("Test Successful \n");
    return 0;
}
*/