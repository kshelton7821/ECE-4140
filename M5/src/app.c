/*
* Authors: Keaton Shelton, Josh White, and Emma Brown
* Team Members: Keaton Shelton, Josh White, Emma Brown, Jared Vega, and Cole 
* Date: 4/5/2023
*
* Abstract: This is the main file for the M5 project. It contains the main program that
*     that is an expanded version of M4. This time with EduBoard :)
*
*
*
*
* Revisions:
* 4/5/2023: Initial Revision
*/
//******************** I N C L U D E S ***************************************
#include "ptb.h"
#include "vigenereH.h"
#include "circbufferH.h"
#include "esos.h"
#include "stm32l4_ocm3/esos_stm32l4.h"

//******************** G L O B A L S *****************************************
//Circular Buffer Globals
#define CB_SIZE 256
circular_buffer_t volatile cb_recieve, cb_send;
uint8_t u8t_bufferRecieve[CB_SIZE], u8t_bufferSend[CB_SIZE];

//Key Tracker
uint8_t volatile u8t_keyTracker = 0;

//Message Strings
char* pch_key = "BOLDFEARLESSCONFIDENT";
char* pch_encryptMessage = "\nEncypting Mode Active\r\n";
char* pch_decryptMessage = "\nDecrypting Mode Active\r\n";
char* pch_startMessage = "\nWelcome to Milestone 4, Vigenere Cipher Encryption/Decryption\r\n";
char* pch_commandMessage = "\nCommand Mode Intiated, Please Enter L to List Period\r\nOr Enter S to Set Period\r\nOr Press ! to Exit Command Mode\r\n";
char* pch_commandSetPeriod = "\nCommand Mode Set Period, Please Enter Period in nnnn format\r\n with (n) being an integer between 0 and 9\r\n";
char* pch_commandExit = "\nExiting Command Mode\r\n";
char* pch_commandSuccess = "\n Command Mode Success, Exiting Command Mode\r\nTimer Set To: ";
char* pch_commandMS = " ms\r\n";
char* pch_periodValue = "\nPeriod Value: ";

//Timer Periods
uint16_t u16t_led0_period = 500;
uint16_t u16t_led1_period = 500;
uint16_t u16t_led2_period = 500;
uint16_t u16t_led3_period = 500;
uint16_t u16t_nucleoLED2_period = 500;
//
//
//
//
//******************** E S O S  T I M E R  H A N D L E S **********************
ESOS_TMR_HANDLE tmrHandle_LED0, tmr_handle_LED1, tmr_handle_LED2, tmr_handle_LED3, tmr_handle_nucleoLED2, tmr_handle_commandMode;
//
//
//
//
//******************** F U N C T I O N S **************************************

//
//
//
//
//******************** E S O S  T A S K S *************************************
//USART Sending Task
ESOS_USER_TASK(sending)
{
    static uint8_t u8t_dataOut;
    ESOS_TASK_BEGIN();
    while(1)
    {
        while(popBuffer(&cb_send, &u8t_dataOut) == 0)
        {
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_UINT8(u8t_dataOut);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        }
        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

//USART Recieving Task
ESOS_USER_TASK(recieving)
{
    ESOS_TASK_BEGIN();

    ESOS_TASK_END();
}

//Mode Select Task
ESOS_USER_TASK(modeSelect)
{
    ESOS_TASK_BEGIN();

    ESOS_TASK_END();
}
//
//
//
//
//******************** E S O S  C H I L D  T A S K S **************************
//Command Interpretter Task
ESOS_CHILD_TASK(interpret)
{
    ESOS_TASK_BEGIN();

    ESOS_TASK_END();
}

//Remove Non-Alpha Task
ESOS_CHILD_TASK(removeNonAlpha)
{
    static uint8_t u8_data_in;
    ESOS_TASK_BEGIN();
    if(popBuffer(&cb_recieve, &u8_data_in) == 0)
    {
        if(isalpha(u8_data_in))
        {
            pushBuffer(&cb_send, u8_data_in);
        }
    }
    ESOS_TASK_END();
}

//To Upper
ESOS_CHILD_TASK(toUpper)
{
    static uint8_t u8_data_in;
    ESOS_TASK_BEGIN();
    if(popBuffer(&cb_recieve, &u8_data_in) == 0)
    {
        if(islower(u8_data_in))
        {
            u8_data_in = toupper(u8_data_in);
            pushBuffer(&cb_send, u8_data_in);
        }
    }    

    ESOS_TASK_END();
}

//Encrypt Task
ESOS_CHILD_TASK(encrypt)
{
    ESOS_TASK_BEGIN();

    ESOS_TASK_END();
}
//Decrypt Task
ESOS_CHILD_TASK(decrypt)
{
    ESOS_TASK_BEGIN();

    ESOS_TASK_END();
}
//
//
//
//

//******************** E S O S  T I M E R S ***********************************
//LED0 Timer
ESOS_USER_TIMER(led0)
{
    //Toggle LED0
    EDUB_LED0_TOGGLE();
}

//LED1 Timer
ESOS_USER_TIMER(led1)
{
    //Toggle LED1
    EDUB_LED1_TOGGLE();
}

//LED2 Timer
ESOS_USER_TIMER(led2)
{
    //Toggle LED2
    EDUB_LED2_TOGGLE();
}

//LED3 Timer
ESOS_USER_TIMER(led3)
{
    //Toggle LED3
    EDUB_LED3_TOGGLE();
}

//Nucleo LED2 Timer
ESOS_USER_TIMER(nucleoLED2)
{
    //Toggle Nucleo LED2
    EDUB_NUCLEO_LED2_TOGGLE();
}

//Command Mode Timer
ESOS_USER_TIMER(commandMode)
{
    
}
//
//
//
//
//******************** I N I T  F U N C T I O N S *****************************
void hw_init(void)
{

}

void user_init(void)
{




//Register ESOS Timers
tmrHandle_LED0 = esos_RegisterTimer(led0, u16t_led0_period);
tmr_handle_LED1 = esos_RegisterTimer(led1, u16t_led1_period);
tmr_handle_LED2 = esos_RegisterTimer(led2, u16t_led2_period);
tmr_handle_LED3 = esos_RegisterTimer(led3, u16t_led3_period);
tmr_handle_nucleoLED2 = esos_RegisterTimer(nucleoLED2, u16t_nucleoLED2_period);
tmr_handle_commandMode = esos_RegisterTimer(commandMode, 100);
}