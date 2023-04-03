/*
* Authors: Josh White, Emma Brown, Jared Vega
* Date: 4/2/2023
* Abstract: This is a demo of the barrier problem using semaphores.
*
*
*
*
*
*
* Revisions:
* 01jw, 01eb, 01jr 4/2/2023: Original
*/
#include "esos.h"
#include "stm32l4_ocm3/esos_stm32l4.h"
#include "embsysS20.h"

char Task[] = "Start Task: ";		//Initializing the messages and counters
char Done[] = "Completed Task: ";
uint8_t u8_count = 0;
uint8_t u8_n = 3;


// *************** S E M A P H O R E S ***************
ESOS_SEMAPHORE(MUTEX);			//Initializing the semaphores
ESOS_SEMAPHORE(BARRIER);

// *************** F U N C T I O N S ****************
inline uint32_t getRandomDelay() {
	return ((esos_GetRandomUint32() & 0x0FFF) | 0xFF);	//Creates pseudo-random
}																										  //Numbers

// *************** T I M E R S **********************
ESOS_USER_TIMER(heartbeat) {		//Creates the LD2 timer
	TOGGLE_LD2();
}


// *************** E S O S  T A S K S ****************
ESOS_USER_TASK(task1) {		//Each task is the same
	ESOS_TASK_BEGIN();

		ESOS_TASK_WAIT_TICKS(getRandomDelay());			//Starts at a random task

		ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();			//Waits to write to putty
		ESOS_TASK_WAIT_ON_SEND_STRING(Task);			//and signals when finished
		ESOS_TASK_WAIT_ON_SEND_UINT8_AS_DEC_STRING(1);
		ESOS_TASK_WAIT_ON_SEND_UINT8(' ');
		ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

		ESOS_TASK_WAIT_SEMAPHORE(MUTEX,1);			//Whichever task starts first gets
		u8_count = u8_count+1;					//the baton
		ESOS_SIGNAL_SEMAPHORE(MUTEX,1);				//Signal the next task
		if(u8_count == u8_n) {
			ESOS_SIGNAL_SEMAPHORE(BARRIER,1);		//Once all finish, signal barrier
		}
		ESOS_TASK_WAIT_SEMAPHORE(BARRIER,1);	//Wait for a signal and wait for the next
		ESOS_SIGNAL_SEMAPHORE(BARRIER,1);

		ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();		//Prints finished message and ends
		ESOS_TASK_WAIT_ON_SEND_STRING(Done);
		ESOS_TASK_WAIT_ON_SEND_UINT8_AS_DEC_STRING(1);
		ESOS_TASK_WAIT_ON_SEND_UINT8(' ');
		ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

	ESOS_TASK_END();
}

ESOS_USER_TASK(task2) {
	ESOS_TASK_BEGIN();

		ESOS_TASK_WAIT_TICKS(getRandomDelay());

		ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
		ESOS_TASK_WAIT_ON_SEND_STRING(Task);
		ESOS_TASK_WAIT_ON_SEND_UINT8_AS_DEC_STRING(2);
		ESOS_TASK_WAIT_ON_SEND_UINT8(' ');
		ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

		ESOS_TASK_WAIT_SEMAPHORE(MUTEX,1);
		u8_count = u8_count+1;
		ESOS_SIGNAL_SEMAPHORE(MUTEX,1);
		if(u8_count == u8_n) {
			ESOS_SIGNAL_SEMAPHORE(BARRIER,1);
		}
		ESOS_TASK_WAIT_SEMAPHORE(BARRIER,1);
		ESOS_SIGNAL_SEMAPHORE(BARRIER,1);

		ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
		ESOS_TASK_WAIT_ON_SEND_STRING(Done);
		ESOS_TASK_WAIT_ON_SEND_UINT8_AS_DEC_STRING(2);
		ESOS_TASK_WAIT_ON_SEND_UINT8(' ');
		ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

	ESOS_TASK_END();
}

ESOS_USER_TASK(task3) {
	ESOS_TASK_BEGIN();

		ESOS_TASK_WAIT_TICKS(getRandomDelay());

		ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
		ESOS_TASK_WAIT_ON_SEND_STRING(Task);
		ESOS_TASK_WAIT_ON_SEND_UINT8_AS_DEC_STRING(3);
		ESOS_TASK_WAIT_ON_SEND_UINT8(' ');
		ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

		ESOS_TASK_WAIT_SEMAPHORE(MUTEX,1);
		u8_count = u8_count+1;
		ESOS_SIGNAL_SEMAPHORE(MUTEX,1);
		if(u8_count == u8_n) {
			ESOS_SIGNAL_SEMAPHORE(BARRIER,1);
		}
		ESOS_TASK_WAIT_SEMAPHORE(BARRIER,1);
		ESOS_SIGNAL_SEMAPHORE(BARRIER,1);

		ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
		ESOS_TASK_WAIT_ON_SEND_STRING(Done);
		ESOS_TASK_WAIT_ON_SEND_UINT8_AS_DEC_STRING(3);
		ESOS_TASK_WAIT_ON_SEND_UINT8(' ');
		ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

	ESOS_TASK_END();
}

// *************** I N I T  F U N C T I O N S ********
void user_init() {
	gpio_mode_setup(LED2_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, LED2_Pin);
	ESOS_INIT_SEMAPHORE(MUTEX,1);
	ESOS_INIT_SEMAPHORE(BARRIER,0);		//Initialize all HW and semaphores
	esos_RegisterTask(task1);		//Register Tasks and Timers
	esos_RegisterTask(task2);
	esos_RegisterTask(task3);
	esos_RegisterTimer(heartbeat, 500);
}
