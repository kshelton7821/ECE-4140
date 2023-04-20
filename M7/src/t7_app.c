/*
* Authors: Keaton Shelton, Josh White, and Emma Brown
* Date: 4/5/2023
*
* Abstract: This is the main file for the M5 project. It contains the main program that
*     that is an expanded version of M4 and M5. This time with EduBoard :)
*
*
*
*
* Revisions:
* 01ks, 01jw, 01eb 4/5/2023: Initial Revision
* 02ks 4/12/2023: Change M6 intro, possibly fix stupid List Period bug
* 03ks, 03eb, 03jw 4/12/2023: Add is ESOS SUI Stuff
* 04ks 4/13/2023: Implement OPMODE system for state selection
* 05ks 4/19/2023: Begin M7
*/
//******************** I N C L U D E S ***************************************
#include "ptb.h"
#include "vigenereH.h"
#include "circbufferH.h"
#include "opmode.h"
#include "esos_stm32l4_ptb_sui.h"
#include "esos_stm32l4_edub.h"
//
//
//
//
//******************** G L O B A L S *****************************************
//Circular Buffer Globals
#define CB_SIZE 256
circular_buffer_t volatile cb_recieve, cb_send;
uint8_t u8t_bufferRecieve[CB_SIZE], u8t_bufferSend[CB_SIZE];

//Key Tracker
uint16_t u16t_keyTracker = 0;

//Message Strings
char* pch_key = "BOLDFEARLESSCONFIDENT";
char* pch_rmNonAlphaMessage = "\nRemove Non Alpha Mode Active\r\n";
char* pch_toUpperMessage = "\nTo Upper Mode Active\r\n";
char* pch_echoMessage = "\nEcho Mode Active\r\n";
char* pch_encryptMessage = "\nEncypting Mode Active\r\n";
char* pch_decryptMessage = "\nDecrypting Mode Active\r\n";
char* pch_startMessage = "\nWelcome to Milestone 6, Vigenere Cipher and Other Functions\r\n";
char* pch_commandMessage = "\nCommand Mode Intiated, Please Enter L to List Period\r\nOr Enter S to Set Period\r\n";
char* pch_commandSetPeriod = "\nCommand Mode Set Period, Please Enter LED Number n\r\n";
char* pch_commandExit = "\nExiting Command Mode\r\n";
char* pch_commandSuccess = "\nExiting Command Mode\r\nTimer Set To: ";
char* pch_commandMS = " ms\r\n";
char* pch_errorMessage = "\nError, Invalid Command\r\n";
char* pch_periodValue = "\nPeriod Value: ";

//Timer Periods
uint32_t volatile u32t_led0_period = 1000;
uint32_t volatile u32t_led1_period = 1000;
uint32_t volatile u32t_led2_period = 1000;
uint32_t volatile u32t_led3_period = 1000;
uint32_t volatile u32t_nucleoLED2_period = 1000;

//Timer Periods Half
uint32_t volatile u32t_led0_period_half = 500;
uint32_t volatile u32t_led1_period_half = 500;
uint32_t volatile u32t_led2_period_half = 500;
uint32_t volatile u32t_led3_period_half = 500;
uint32_t volatile u32t_nucleoLED2_period_half = 500;

//Trackers
uint8_t volatile u8t_commandCounter = 0;
uint8_t volatile u8t_arrTracker = 0;
uint8_t volatile u8tArr_periodSet[4] = {0, 0, 0, 0};

//Show Period Array
char volatile u8tArr_showPeriod[4] = {'0', '0', '0', '0'};


//Encryption State / Other Mode Bools.
bool volatile b_encrypt = false, b_decrypt = false, b_toUpper = false, b_rmNonAlpha = false, b_echo = false, b_commandMode = false, b_commandSetPeriod = false, b_commandListPeriod = false;

//Booleans for Running LED's at half speed
bool volatile b_led0_half = false, b_led1_half = false, b_led2_half = false, b_led3_half = false;

//Operating Mode
st_opmode volatile opmode;
uint8_t volatile u8t_mode = OPMODE_ECHO;

//LCD Mode
enum LCD_MODE LCD_STATE = STANDBY;

//LED Selected for LCD
enum LED_SELECTED LED_STATE = LED0;
//
//
//
//
//******************** E S O S  H A N D L E S **********************
ESOS_TMR_HANDLE tmr_handle_LED0, tmr_handle_LED1, tmr_handle_LED2, tmr_handle_LED3, tmr_handle_nucleoLED2, tmr_handle_commandMode;
ESOS_SUI_LED_HANDLE h_LED0, h_LED1, h_LED2, h_LED3, h_LED4;
ESOS_SUI_SWITCH_HANDLE h_SW1, h_SW2, h_SW3, h_SW4, h_SW5;
//
//
//
//
//******************** E S O S  D E F I N E S *********************************
//LED Defines
_st_esos_sui_LED NUCELO_LED2;
_st_esos_sui_LED EDUB_LED3;
_st_esos_sui_LED EDUB_LED2;
_st_esos_sui_LED EDUB_LED1;
_st_esos_sui_LED EDUB_LED0;

//SWITCH Defines
_st_esos_sui_Switch NUCLEO_SW1;
_st_esos_sui_Switch EDUB_SW2;
_st_esos_sui_Switch EDUB_SW3;
_st_esos_sui_Switch EDUB_SW4;
_st_esos_sui_Switch EDUB_SW5;
//******************** F U N C T I O N S **************************************


//******************** E S O S  C H I L D  T A S K S **************************
//Command Interpretter Task
ESOS_CHILD_TASK(interpretter, uint8_t u8t_dataIN)
{
    static uint8_t u8tArr_periodSet[4] = {0, 0, 0, 0};
    static char u8tArr_showPeriod[4] = {'0', '0', '0', '0'};
    static uint8_t u8t_led;
    ESOS_TASK_BEGIN();
    //Check for Command
    //List LEDx Period
    if(u8t_dataIN == 'L' && u8t_commandCounter == 0)
    {
        //Echo Back
        ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
        ESOS_TASK_WAIT_ON_SEND_STRING("L\r\n");
        ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

        ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
        ESOS_TASK_WAIT_ON_SEND_STRING("ENTER 0, 1, 2, 3, 4 to select LED\r\n");
        ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

        //Increment Command Counter
        u8t_commandCounter++;
        b_commandListPeriod = true;
        b_commandSetPeriod = false;
    }
    //Check for LED Number
    else if(u8t_commandCounter == 1 && b_commandListPeriod && isdigit(u8t_dataIN))
    {
        if(u8t_dataIN == '0')
        {
        
        uint32_t test = u32t_led0_period;
        sprintf(u8tArr_showPeriod, "%lu", test);
        //Send LED0 Period
        ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
        ESOS_TASK_WAIT_ON_SEND_STRING(pch_periodValue);
        ESOS_TASK_WAIT_ON_SEND_STRING(u8tArr_showPeriod);
        ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
        ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        }
        else if(u8t_dataIN == '1')
        {
            sprintf(u8tArr_showPeriod, "%lu", u32t_led1_period);
            //Send LED1 Period
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_periodValue);
            ESOS_TASK_WAIT_ON_SEND_U8BUFFER(&u8tArr_showPeriod[0], 4);
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        }
        else if(u8t_dataIN == '2')
        {
            sprintf(u8tArr_showPeriod, "%lu", u32t_led2_period);
            //Send LED2 Period
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_periodValue);
            ESOS_TASK_WAIT_ON_SEND_U8BUFFER(&u8tArr_showPeriod[0], 4);
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        }
        else if(u8t_dataIN == '3')
        {
            sprintf(u8tArr_showPeriod, "%lu", u32t_led3_period);
            //Send LED3 Period
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_periodValue);
            ESOS_TASK_WAIT_ON_SEND_U8BUFFER(&u8tArr_showPeriod[0], 4);
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        }
        else if(u8t_dataIN == '4')
        {
            sprintf(u8tArr_showPeriod, "%lu", u32t_nucleoLED2_period);
            //Send Nucleo LED2 Period
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_periodValue);
            ESOS_TASK_WAIT_ON_SEND_U8BUFFER(&u8tArr_showPeriod[0], 4);
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        }
        //Reset
        b_commandListPeriod = false;
        u8t_commandCounter = 0;
    }
    else if(u8t_dataIN == 'S' && u8t_commandCounter == 0)
    {
        //Command S Message
        ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
        ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandSetPeriod);
        ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

        //Increment Command Counter
        u8t_commandCounter++;
        b_commandSetPeriod = true;
        b_commandListPeriod = false;
    }
    else if(u8t_commandCounter == 1 && b_commandSetPeriod && isdigit(u8t_dataIN))
    {
        //Check for LED Number
        if(u8t_dataIN == '0')
        {
            //Echo Back Selection
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING("LED0 has been selected\r\nEnter new period in nnnn format\r\n");
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
            
            //Select LED0
            u8t_led = 0;
            u8t_commandCounter++;
        }
        else if(u8t_dataIN == '1')
        {
            //Echo Back Selection
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING("LED1 has been selected\r\nEnter new period in nnnn format\r\n");
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

            //Select LED1
            u8t_led = 1;
            u8t_commandCounter++;
        }
        else if(u8t_dataIN == '2')
        {
            //Echo Back Selection
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING("LED2 has been selected\r\nEnter new period in nnnn format\r\n");
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

            //Select LED2
            u8t_led = 2;
            u8t_commandCounter++;
        }
        else if(u8t_dataIN == '3')
        {
            //Echo Back Selection
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING("LED3 has been selected\r\nEnter new period in nnnn format\r\n");
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

            //Select LED3
            u8t_led = 3;
            u8t_commandCounter++;
        }
        else if(u8t_dataIN == '4')
        {
            //Echo Back Selection
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING("Nucleo LED2 has been selected\r\nEnter new period in nnnn format\r\n");
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

            //Select Nucleo LED2
            u8t_led = 4;
            u8t_commandCounter++;
        }
    }
    else if(u8t_commandCounter == 2 && b_commandSetPeriod && isdigit(u8t_dataIN))
    {
        //Take in period
        u8tArr_periodSet[u8t_arrTracker] = u8t_dataIN;
        //Increment Array Tracker
        u8t_arrTracker++;
        //Check if period is complete
        if(u8t_arrTracker > 3)
        {
            //Set Period for respective LED
            if(u8t_led == 0)
            {
                u32t_led0_period = atoi(u8tArr_periodSet);
                u32t_led0_period_half = u32t_led0_period / 2;
                esos_ChangeTimerPeriod(tmr_handle_LED0, u32t_led0_period);
                

                //Send LED0 Period
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandSuccess);
                ESOS_TASK_WAIT_ON_SEND_U8BUFFER(&u8tArr_periodSet[0], 4);
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

                //Fix stupid bug that took me 4 hours to find with the List mode
                for(int i = 0; i < 4; i++)
                {
                    u8tArr_periodSet[i] = '0';
                }
            }
            else if(u8t_led == 1)
            {
                u32t_led1_period = atoi(u8tArr_periodSet);
                u32t_led1_period_half = u32t_led1_period / 2;
                esos_ChangeTimerPeriod(tmr_handle_LED1, u32t_led1_period);

                //Send LED1 Period
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandSuccess);
                ESOS_TASK_WAIT_ON_SEND_U8BUFFER(&u8tArr_periodSet[0], 4);
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

                //Fix stupid bug that took me 4 hours to find with the List mode
                for(int i = 0; i < 4; i++)
                {
                    u8tArr_periodSet[i] = '0';
                }
            }
            else if(u8t_led == 2)
            {
                u32t_led2_period = atoi(u8tArr_periodSet);
                u32t_led2_period_half = u32t_led2_period / 2;
                esos_ChangeTimerPeriod(tmr_handle_LED2, u32t_led2_period);

                //Send LED2 Period
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandSuccess);
                ESOS_TASK_WAIT_ON_SEND_U8BUFFER(&u8tArr_periodSet[0], 4);
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

                //Fix stupid bug that took me 4 hours to find with the List mode
                for(int i = 0; i < 4; i++)
                {
                    u8tArr_periodSet[i] = '0';
                }
            }
            else if(u8t_led == 3)
            {
                u32t_led3_period = atoi(u8tArr_periodSet);
                u32t_led3_period_half = u32t_led3_period / 2;
                esos_ChangeTimerPeriod(tmr_handle_LED3, u32t_led3_period);

                //Send LED3 Period
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandSuccess);
                ESOS_TASK_WAIT_ON_SEND_U8BUFFER(&u8tArr_periodSet[0], 4);
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

                //Fix stupid bug that took me 4 hours to find with the List mode
                for(int i = 0; i < 4; i++)
                {
                    u8tArr_periodSet[i] = '0';
                }
            }
            else if(u8t_led == 4)
            {
                u32t_nucleoLED2_period = atoi(u8tArr_periodSet);
                u32t_nucleoLED2_period_half = u32t_nucleoLED2_period / 2;
                esos_ChangeTimerPeriod(tmr_handle_nucleoLED2, u32t_nucleoLED2_period);

                //Send Nucleo LED2 Period
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandSuccess);
                ESOS_TASK_WAIT_ON_SEND_U8BUFFER(&u8tArr_periodSet[0], 4);
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

                //Fix stupid bug that took me 4 hours to find with the List mode
                for(int i = 0; i < 4; i++)
                {
                    u8tArr_periodSet[i] = '0';
                }
            }
            //Reset Array Tracker
            u8t_arrTracker = 0;
            //Reset Command Counter
            u8t_commandCounter = 0;
            //Reset Command Flag
            b_commandSetPeriod = false;
            //Reset Period Flag
            b_commandListPeriod = false;
        }
    }
    else
    {
        //Input Error
        //Reset Variables
        u8t_commandCounter = 0;
        u8t_arrTracker = 0;
        b_commandSetPeriod = false;
        b_commandListPeriod = false;
        //Send Error Message
        ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
        ESOS_TASK_WAIT_ON_SEND_STRING(pch_errorMessage);
        ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
    }
    ESOS_TASK_END();
}

//Remove Non-Alpha Task
ESOS_CHILD_TASK(removeNonAlpha, uint8_t u8t_dataIN)
{
    ESOS_TASK_BEGIN();
    //If so, check if it is alpha
    if(isalpha(u8t_dataIN) || isdigit(u8t_dataIN))
    {
        //Push to outbound buffer
        pushBuffer(&cb_send, u8t_dataIN);
    }
    ESOS_TASK_END();
}

//To Upper
ESOS_CHILD_TASK(toUpperFunc, uint8_t u8t_dataIN)
{
    ESOS_TASK_BEGIN();
    //If so, check if it is lower case
    if(islower(u8t_dataIN))
    {
        u8t_dataIN = toupper(u8t_dataIN);
        pushBuffer(&cb_send, u8t_dataIN);
    }
    ESOS_TASK_END();
}

//Encrypt Task
ESOS_CHILD_TASK(encryptUINT, uint8_t u8t_dataIN)
{
    ESOS_TASK_BEGIN();
    if(isalpha(u8t_dataIN))
    {
        //If so, check if it is lower case
        if (islower(u8t_dataIN))
        {
            u8t_dataIN = toupper(u8t_dataIN);
        }

        //Encrypt
        encryptBoard(&u8t_dataIN, pch_key, &u16t_keyTracker);

        //Push to outbound buffer
        pushBuffer(&cb_send, u8t_dataIN);
    }
    ESOS_TASK_END();
}
//Decrypt Task
ESOS_CHILD_TASK(decryptUINT, uint8_t u8t_dataIN)
{
    ESOS_TASK_BEGIN();
    //If so, check if it is alpha
    if (isalpha(u8t_dataIN))
    {
        //If so, check if it is lower case
        if (islower(u8t_dataIN))
        {
            u8t_dataIN = toupper(u8t_dataIN);
        }

        //Decrypt
        decryptBoard(&u8t_dataIN, pch_key, &u16t_keyTracker);

        //Push to outbound buffer
        pushBuffer(&cb_send, u8t_dataIN);
    }
    ESOS_TASK_END();
}
//
//
//
//
//******************** E S O S  T A S K S *************************************
//LCD Task
ESOS_USER_TASK(lcd_manager)
{
    ESOS_TASK_BEGIN();
    while(1)
    {
        //Check LCD State
        if(LCD_STATE == STANDBY)
        {
            
        }
        else if(LCD_STATE == EDIT)
        {

        }
        else //LCD_STATE == REPEAT
        {

        }
        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

//USART Sending Task
ESOS_USER_TASK(sending)
{
    static uint8_t u8t_dataOut;
    ESOS_TASK_BEGIN();
    while(1)
    {
        //Check if anything is in outbound buffer
        while(popBuffer(&cb_send, &u8t_dataOut) == 0)
        {
            //If so, send it out
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
    static uint8_t u8t_dataIn;
    ESOS_TASK_BEGIN();
    //Send Welcome Message
    ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
    ESOS_TASK_WAIT_ON_SEND_STRING(pch_startMessage);
    ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
    while(1)
    {
        //Check if anything is in inbound buffer
        ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();
        ESOS_TASK_WAIT_ON_GET_UINT8(u8t_dataIn);
        ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();
        pushBuffer(&cb_recieve, u8t_dataIn);
        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

//Mode Select Task
ESOS_USER_TASK(modeSelect)
{
    static uint8_t u8t_dataIn;
    static uint8_t u8t_buttons[5] = {0,0,0,0,0};

    ESOS_TASK_HANDLE tskHandle_imTired;
    ESOS_TASK_BEGIN();
    while(1)
    {
        //Check the OPMODE

        //If in command mode
        if(u8t_mode == OPMODE_KEYBOARD)
        {
            //Check for other switches
            if(esos_hw_sui_isSwitchPressed(h_SW2))
            {
                b_led3_half = true;
            }
            else if (esos_hw_sui_isSwitchPressed(h_SW3))
            {
                b_led2_half = true;
            }
            else if (esos_hw_sui_isSwitchPressed(h_SW4))
            {
                b_led1_half = true;
            }
            else if (esos_hw_sui_isSwitchPressed(h_SW5))
            {
                b_led0_half = true;
            }
            else
            {
                //Reset
                b_led0_half = false;
                b_led1_half = false;
                b_led2_half = false;
                b_led3_half = false;
            }

            //Check if previously in command mode
            if(!b_commandMode)
            {
                //Send Message
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMessage);
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                u16t_keyTracker = 0;
            }
            //Set various bools
            b_commandMode = true;
            b_encrypt = false;
            b_decrypt = false;
            b_toUpper = false;
            b_rmNonAlpha = false;
            b_echo = false;

            if(popBuffer(&cb_recieve, &u8t_dataIn) == 0)
            {
                //Spawn command mode task
                ESOS_ALLOCATE_CHILD_TASK(tskHandle_imTired);
                ESOS_TASK_SPAWN_AND_WAIT(tskHandle_imTired, interpretter, u8t_dataIn);
                ESOS_TASK_YIELD();
            }
        }
        else if(u8t_mode == OPMODE_RM_NON_ALPHA)
        {
            //Check if previously in rmNonAlpha mode
            if(!b_rmNonAlpha)
            {
                //Send Message
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_rmNonAlphaMessage);
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                u16t_keyTracker = 0;
            }
            //Set various bools
            b_rmNonAlpha = true;
            b_encrypt = false;
            b_decrypt = false;
            b_toUpper = false;
            b_echo = false;
            b_commandMode = false;
            b_commandListPeriod = false;
            b_commandSetPeriod = false;

            if(popBuffer(&cb_recieve, &u8t_dataIn) == 0)
            {
                //Spawn rmNonAlpha task
                ESOS_ALLOCATE_CHILD_TASK(tskHandle_imTired);
                ESOS_TASK_SPAWN_AND_WAIT(tskHandle_imTired, removeNonAlpha, u8t_dataIn);
                ESOS_TASK_YIELD();
            }
        }
        else if(u8t_mode == OPMODE_TO_UPPER)
        {
            //Check if previously in toUpper mode
            if(!b_toUpper)
            {
                //Send Message
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_toUpperMessage);
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                u16t_keyTracker = 0;
            }
            //Set various bools
            b_toUpper = true;
            b_encrypt = false;
            b_decrypt = false;
            b_rmNonAlpha = false;
            b_echo = false;
            b_commandMode = false;
            b_commandListPeriod = false;
            b_commandSetPeriod = false;

            if(popBuffer(&cb_recieve, &u8t_dataIn) == 0)
            {
                //Spawn toUpper task
                ESOS_ALLOCATE_CHILD_TASK(tskHandle_imTired);
                ESOS_TASK_SPAWN_AND_WAIT(tskHandle_imTired, toUpperFunc, u8t_dataIn);
                ESOS_TASK_YIELD();
            }
        }
        else if(u8t_mode == OPMODE_ENCRYPT)
        {
            //Check if previously in encrypt mode
            if(!b_encrypt)
            {
                //Send Message
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_encryptMessage);
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                //Reset key tracker
                u16t_keyTracker = 0;
            }
            //Set various bools
            b_encrypt = true;
            b_decrypt = false;
            b_toUpper = false;
            b_rmNonAlpha = false;
            b_echo = false;
            b_commandMode = false;
            b_commandListPeriod = false;
            b_commandSetPeriod = false;

            if(popBuffer(&cb_recieve, &u8t_dataIn) == 0)
            {
                //Spawn encrypt task
                ESOS_ALLOCATE_CHILD_TASK(tskHandle_imTired);
                ESOS_TASK_SPAWN_AND_WAIT(tskHandle_imTired, encryptUINT, u8t_dataIn);
                ESOS_TASK_YIELD();
            }
        }
        else if(u8t_mode == OPMODE_DECRYPT)
        {
            //Check if previously in decrypt mode
            if(!b_decrypt)
            {
                //Send Message
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_decryptMessage);
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                //Reset key tracker
                u16t_keyTracker = 0;
            }
            //Set various bools
            b_encrypt = false;
            b_decrypt = true;
            b_toUpper = false;
            b_rmNonAlpha = false;
            b_echo = false;
            b_commandMode = false;
            b_commandListPeriod = false;
            b_commandSetPeriod = false;

            if(popBuffer(&cb_recieve, &u8t_dataIn) == 0)
            {
                //Spawn decrypt task
                ESOS_ALLOCATE_CHILD_TASK(tskHandle_imTired);
                ESOS_TASK_SPAWN_AND_WAIT(tskHandle_imTired, decryptUINT, u8t_dataIn);
                ESOS_TASK_YIELD();
            }
        }
        else //OPMODE_ECHO
        {
            //Check if previously in echo mode
            if(!b_echo)
            {
                //Send Message
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_echoMessage);
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                u16t_keyTracker = 0;
            }

            //Set various bools
            b_encrypt = false;
            b_decrypt = false;
            b_toUpper = false;
            b_rmNonAlpha = false;
            b_echo = true;
            b_commandMode = false;
            b_commandListPeriod = false;
            b_commandSetPeriod = false;

            if(popBuffer(&cb_recieve, &u8t_dataIn) == 0)
            {
                //push to outbound buffer
                pushBuffer(&cb_send, u8t_dataIn);
            }

            ESOS_TASK_YIELD();
        }
        if(b_led0_half && esos_hw_sui_isSwitchPressed(h_SW5) && !esos_hw_sui_isSwitchPressed(h_SW1))
        {
            esos_ChangeTimerPeriod(tmr_handle_LED0, u32t_led0_period_half);
        }            
        else if(b_led1_half && esos_hw_sui_isSwitchPressed(h_SW4) && !esos_hw_sui_isSwitchPressed(h_SW1))
        {
            esos_ChangeTimerPeriod(tmr_handle_LED1, u32t_led1_period_half);
        }
        else if(b_led2_half && esos_hw_sui_isSwitchPressed(h_SW3) && !esos_hw_sui_isSwitchPressed(h_SW1))
        {
            esos_ChangeTimerPeriod(tmr_handle_LED2, u32t_led2_period_half);
        }
        else if(b_led3_half && esos_hw_sui_isSwitchPressed(h_SW2) && !esos_hw_sui_isSwitchPressed(h_SW1))
        {
            esos_ChangeTimerPeriod(tmr_handle_LED3, u32t_led3_period_half);
        }
        else
        {
            esos_ChangeTimerPeriod(tmr_handle_LED0, u32t_led0_period);
            esos_ChangeTimerPeriod(tmr_handle_LED1, u32t_led1_period);
            esos_ChangeTimerPeriod(tmr_handle_LED2, u32t_led2_period);
            esos_ChangeTimerPeriod(tmr_handle_LED3, u32t_led3_period);
        }


        ESOS_TASK_YIELD();
    }
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
    esos_hw_sui_toggleLED(h_LED0);
}

//LED1 Timer
ESOS_USER_TIMER(led1)
{
    //Toggle LED1
    esos_hw_sui_toggleLED(h_LED1);
}

//LED2 Timer
ESOS_USER_TIMER(led2)
{
    //Toggle LED2
    esos_hw_sui_toggleLED(h_LED2);
}

//LED3 Timer
ESOS_USER_TIMER(led3)
{
    //Toggle LED3
    esos_hw_sui_toggleLED(h_LED3);
}

//Nucleo LED2 Timer
ESOS_USER_TIMER(nucleoLED2)
{
    //Toggle Nucleo LED2
    esos_hw_sui_toggleLED(h_LED4);
}

//This for some reason would not work, honestly no reason why it shouldn't since its right but its 4:48am and I'm tired

//Command Mode Timer
ESOS_USER_TIMER(commandMode)
{
    bool b_buttons[5] = {0,0,0,0,0};
    b_buttons[0] = !esos_hw_sui_isSwitchPressed(h_SW1);
    b_buttons[1] = esos_hw_sui_isSwitchPressed(h_SW2);
    b_buttons[2] = esos_hw_sui_isSwitchPressed(h_SW3);
    b_buttons[3] = esos_hw_sui_isSwitchPressed(h_SW4);
    b_buttons[4] = esos_hw_sui_isSwitchPressed(h_SW5);
    fnst_opmodeUpdate(&opmode, b_buttons[0], b_buttons[1], b_buttons[2], b_buttons[3], b_buttons[4]);
    u8t_mode = fnst_opmodePriority(&opmode);
}

//
//
//
//
//******************** I N I T  F U N C T I O N S *****************************
void hw_init(void)
{
    //Setup LCD
    esos_lcd44780_configDisplay();
    __esos_lcd44780_init();
    //Reset Screen
    esos_lcd44780_clearScreen();

    //ESOS HW setup
    //Define LEDs
    NUCELO_LED2.u32_userData1 = NUCLEO_LED2_Port;
    NUCELO_LED2.u32_userData2 = NUCLEO_LED2_Pin;

    EDUB_LED3.u32_userData1 = EDUB_LED3_PORT;
    EDUB_LED3.u32_userData2 = EDUB_LED3_PIN;

    EDUB_LED2.u32_userData1 = EDUB_LED2_PORT;
    EDUB_LED2.u32_userData2 = EDUB_LED2_PIN;

    EDUB_LED1.u32_userData1 = EDUB_LED1_PORT;
    EDUB_LED1.u32_userData2 = EDUB_LED1_PIN;

    EDUB_LED0.u32_userData1 = EDUB_LED0_PORT;
    EDUB_LED0.u32_userData2 = EDUB_LED0_PIN;

    //Define Buttons
    NUCLEO_SW1.u32_userData1 = NUCLEO_BUTTON_PORT;
    NUCLEO_SW1.u32_userData2 = NUCLEO_BUTTON_PIN;

    EDUB_SW2.u32_userData1 = EDUB_SW2_PORT;
    EDUB_SW2.u32_userData2 = EDUB_SW2_PIN;

    EDUB_SW3.u32_userData1 = EDUB_SW3_PORT;
    EDUB_SW3.u32_userData2 = EDUB_SW3_PIN;

    EDUB_SW4.u32_userData1 = EDUB_SW4_PORT;
    EDUB_SW4.u32_userData2 = EDUB_SW4_PIN;

    EDUB_SW5.u32_userData1 = EDUB_SW5_PORT;
    EDUB_SW5.u32_userData2 = EDUB_SW5_PIN;

    //Register LEDs
    h_LED0 = esos_sui_registerLED(EDUB_LED0.u32_userData1, EDUB_LED0.u32_userData2);
    h_LED1 = esos_sui_registerLED(EDUB_LED1.u32_userData1, EDUB_LED1.u32_userData2);
    h_LED2 = esos_sui_registerLED(EDUB_LED2.u32_userData1, EDUB_LED2.u32_userData2);
    h_LED3 = esos_sui_registerLED(EDUB_LED3.u32_userData1, EDUB_LED3.u32_userData2);
    h_LED4 = esos_sui_registerLED(NUCELO_LED2.u32_userData1, NUCELO_LED2.u32_userData2);

    //Register Buttons
    h_SW1 = esos_sui_registerSwitch(NUCLEO_SW1.u32_userData1, NUCLEO_SW1.u32_userData2);
    h_SW2 = esos_sui_registerSwitch(EDUB_SW2.u32_userData1, EDUB_SW2.u32_userData2);
    h_SW3 = esos_sui_registerSwitch(EDUB_SW3.u32_userData1, EDUB_SW3.u32_userData2);
    h_SW4 = esos_sui_registerSwitch(EDUB_SW4.u32_userData1, EDUB_SW4.u32_userData2);
    h_SW5 = esos_sui_registerSwitch(EDUB_SW5.u32_userData1, EDUB_SW5.u32_userData2);

    //Setup RCC for buttons and LEDs
    GPIOA_SETUP_RCC();
    GPIOB_SETUP_RCC();
    GPIOC_SETUP_RCC();

    //Config LEDs
    esos_hw_sui_configLED(h_LED0);
    esos_hw_sui_configLED(h_LED1);
    esos_hw_sui_configLED(h_LED2);
    esos_hw_sui_configLED(h_LED3);
    esos_hw_sui_configLED(h_LED4);

    //Eduboard Button Setup
    EDUB_KEYPAD_ROW0_SETUP();
    EDUB_KEYPAD_ROW1_SETUP();
    EDUB_KEYPAD_ROW2_SETUP();
    EDUB_KEYPAD_ROW3_SETUP();
    EDUB_KEYPAD_COL0_SETUP();
    EDUB_KEYPAD_COL1_SETUP();
    EDUB_KEYPAD_COL2_SETUP();
    EDUB_KEYPAD_COL3_SETUP();

    //Config Buttons
    esos_hw_sui_configSwitch(h_SW1);
    esos_hw_sui_configSwitch(h_SW2);
    esos_hw_sui_configSwitch(h_SW3);
    esos_hw_sui_configSwitch(h_SW4);
    esos_hw_sui_configSwitch(h_SW5);
}

void user_init(void)
{
    //Initialize Hardware
    hw_init();

    //Initialize Software Structures
    initBuffer(&cb_recieve, u8t_bufferRecieve, CB_SIZE);
    initBuffer(&cb_send, u8t_bufferSend, CB_SIZE);
    fnst_opmodeInit(&opmode);

    //Initialize ESOS Tasks
    esos_RegisterTask(recieving);
    esos_RegisterTask(sending);
    esos_RegisterTask(lcd_manager);
    esos_RegisterTask(modeSelect);

    //Register ESOS Timers
    tmr_handle_LED0 = esos_RegisterTimer(led0, u32t_led0_period);
    tmr_handle_LED1 = esos_RegisterTimer(led1, u32t_led1_period);
    tmr_handle_LED2 = esos_RegisterTimer(led2, u32t_led2_period);
    tmr_handle_LED3 = esos_RegisterTimer(led3, u32t_led3_period);
    tmr_handle_nucleoLED2 = esos_RegisterTimer(nucleoLED2, u32t_nucleoLED2_period);
    tmr_handle_commandMode = esos_RegisterTimer(commandMode, 100);
}