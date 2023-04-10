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
#include "opmode.h"
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
char* pch_startMessage = "\nWelcome to Milestone 5, Vigenere Cipher and Other Functions\r\n";
char* pch_commandMessage = "\nCommand Mode Intiated, Please Enter L to List Period\r\nOr Enter S to Set Period\r\n";
char* pch_commandSetPeriod = "\nCommand Mode Set Period, Please Enter LED Number n\r\n";
char* pch_commandExit = "\nExiting Command Mode\r\n";
char* pch_commandSuccess = "\nExiting Command Mode\r\nTimer Set To: ";
char* pch_commandMS = " ms\r\n";
char* pch_errorMessage = "\nError, Invalid Command\r\n";
char* pch_periodValue = "\nPeriod Value: ";

//Timer Periods
uint16_t u16t_led0_period = 1000;
uint16_t u16t_led1_period = 1000;
uint16_t u16t_led2_period = 1000;
uint16_t u16t_led3_period = 1000;
uint16_t u16t_nucleoLED2_period = 1000;
//Trackers
uint8_t u8t_commandCounter = 0;
uint8_t u8t_arrTracker = 0;
uint8_t u8tArr_periodSet[4] = {0, 0, 0, 0};


//Encryption State / Other Mode Bools.
bool volatile b_encrypt = false, b_decrypt = false, b_toUpper = false, b_rmNonAlpha = false, b_echo = false, b_commandMode = false, b_commandSetPeriod = false, b_commandListPeriod = false;

//Operating Mode
st_opmode volatile opmode;
uint8_t volatile u8t_mode = OPMODE_ECHO;
//
//
//
//
//******************** E S O S  T I M E R  H A N D L E S **********************
ESOS_TMR_HANDLE tmr_handle_LED0, tmr_handle_LED1, tmr_handle_LED2, tmr_handle_LED3, tmr_handle_nucleoLED2, tmr_handle_commandMode;
//
//
//
//
//******************** F U N C T I O N S **************************************


//******************** E S O S  C H I L D  T A S K S **************************
//Command Interpretter Task
ESOS_CHILD_TASK(interpretter, uint8_t u8t_dataIN)
{
    static uint8_t u8tArr_showPeriod[4];
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
    }
    //Check for LED Number
    else if(u8t_commandCounter == 1 && b_commandListPeriod && isdigit(u8t_dataIN))
    {
        if(u8t_dataIN == '0')
        {
        sprintf(u8tArr_showPeriod, "%d", u16t_led0_period);
        //Send LED0 Period
        ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
        ESOS_TASK_WAIT_ON_SEND_STRING(pch_periodValue);
        ESOS_TASK_WAIT_ON_SEND_U8BUFFER(u8tArr_showPeriod, 4);
        ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
        ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        }
        else if(u8t_dataIN == '1')
        {
            sprintf(u8tArr_showPeriod, "%d", u16t_led1_period);
            //Send LED1 Period
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_periodValue);
            ESOS_TASK_WAIT_ON_SEND_U8BUFFER(u8tArr_showPeriod, 4);
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        }
        else if(u8t_dataIN == '2')
        {
            sprintf(u8tArr_showPeriod, "%d", u16t_led2_period);
            //Send LED2 Period
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_periodValue);
            ESOS_TASK_WAIT_ON_SEND_U8BUFFER(u8tArr_showPeriod, 4);
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        }
        else if(u8t_dataIN == '3')
        {
            sprintf(u8tArr_showPeriod, "%d", u16t_led3_period);
            //Send LED3 Period
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_periodValue);
            ESOS_TASK_WAIT_ON_SEND_U8BUFFER(u8tArr_showPeriod, 4);
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        }
        else if(u8t_dataIN == '4')
        {
            sprintf(u8tArr_showPeriod, "%d", u16t_nucleoLED2_period);
            //Send Nucleo LED2 Period
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_periodValue);
            ESOS_TASK_WAIT_ON_SEND_U8BUFFER(u8tArr_showPeriod, 4);
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        }
        //Reset
        b_commandListPeriod = false;
        u8t_commandCounter = 0;
    }
    else if(u8t_dataIN == 'S')
    {
        //Command S Message
        ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
        ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandSetPeriod);
        ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

        //Increment Command Counter
        u8t_commandCounter++;
        b_commandSetPeriod = true;
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
        if(u8t_arrTracker >= 4)
        {
            //Set Period for respective LED
            if(u8t_led == 0)
            {
                u16t_led0_period = atoi(u8tArr_periodSet);
                esos_ChangeTimerPeriod(tmr_handle_LED0, u16t_led0_period);

                //Send LED0 Period
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandSuccess);
                ESOS_TASK_WAIT_ON_SEND_U8BUFFER(u8tArr_periodSet, 4);
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
            }
            else if(u8t_led == 1)
            {
                u16t_led1_period = atoi(u8tArr_periodSet);
                esos_ChangeTimerPeriod(tmr_handle_LED1, u16t_led1_period);

                //Send LED1 Period
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandSuccess);
                ESOS_TASK_WAIT_ON_SEND_U8BUFFER(u8tArr_periodSet, 4);
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
            }
            else if(u8t_led == 2)
            {
                u16t_led2_period = atoi(u8tArr_periodSet);
                esos_ChangeTimerPeriod(tmr_handle_LED2, u16t_led2_period);

                //Send LED2 Period
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandSuccess);
                ESOS_TASK_WAIT_ON_SEND_U8BUFFER(u8tArr_periodSet, 4);
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
            }
            else if(u8t_led == 3)
            {
                u16t_led3_period = atoi(u8tArr_periodSet);
                esos_ChangeTimerPeriod(tmr_handle_LED3, u16t_led3_period);

                //Send LED3 Period
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandSuccess);
                ESOS_TASK_WAIT_ON_SEND_U8BUFFER(u8tArr_periodSet, 4);
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
            }
            else if(u8t_led == 4)
            {
                u16t_nucleoLED2_period = atoi(u8tArr_periodSet);
                esos_ChangeTimerPeriod(tmr_handle_nucleoLED2, u16t_nucleoLED2_period);

                //Send Nucleo LED2 Period
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandSuccess);
                ESOS_TASK_WAIT_ON_SEND_U8BUFFER(u8tArr_periodSet, 4);
                ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
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
    if(isalpha(u8t_dataIN))
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
        //If in command mode
        if(NUCLEO_BUTTON_PUSHED())
        {
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
        else if(EDUB_SW2_PUSHED())
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
        else if(EDUB_SW3_PUSHED())
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
        else if(EDUB_SW4_PUSHED())
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
        else if(EDUB_SW5_PUSHED())
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
    NUCLEO_LED2_TOGGLE();
}

//This for some reason would not work, honestly no reason why it shouldn't since its right but its 4:48am and I'm tired
/*
//Command Mode Timer
ESOS_USER_TIMER(commandMode)
{
    uint8_t u8t_buttons[5] = {0,0,0,0,0};
    u8t_buttons[0] = NUCLEO_BUTTON_PUSHED();
    u8t_buttons[1] = EDUB_SW2_PUSHED();
    u8t_buttons[2] = EDUB_SW3_PUSHED();
    u8t_buttons[3] = EDUB_SW4_PUSHED();
    u8t_buttons[4] = EDUB_SW5_PUSHED();
    fnst_opmodeUpdate(&opmode, u8t_buttons[0], u8t_buttons[1], u8t_buttons[2], u8t_buttons[3], u8t_buttons[4]);
    u8t_mode = fnst_opmodePriority(&opmode);
}
*/
//
//
//
//
//******************** I N I T  F U N C T I O N S *****************************
void hw_init(void)
{
    //Setup RCC for buttons and LEDs
    GPIOA_SETUP_RCC();
    GPIOB_SETUP_RCC();
    GPIOC_SETUP_RCC();

    //Nucleo HW setup
    NUCLEO_BUTTON_SETUP();
    NUCLEO_LED2_SETUP();

    //Eduboard Button Setup
    EDUB_KEYPAD_ROW0_SETUP();
    EDUB_KEYPAD_ROW1_SETUP();
    EDUB_KEYPAD_ROW2_SETUP();
    EDUB_KEYPAD_ROW3_SETUP();
    EDUB_KEYPAD_COL0_SETUP();
    EDUB_KEYPAD_COL1_SETUP();
    EDUB_KEYPAD_COL2_SETUP();
    EDUB_KEYPAD_COL3_SETUP();
    EDUB_SW2_SETUP();
    EDUB_SW3_SETUP();
    EDUB_SW4_SETUP();
    EDUB_SW5_SETUP();

    //Eduboard LED setup
    EDUB_LED0_SETUP();
    EDUB_LED1_SETUP();
    EDUB_LED2_SETUP();
    EDUB_LED3_SETUP();

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
    esos_RegisterTask(modeSelect);

    //Register ESOS Timers
    tmr_handle_LED0 = esos_RegisterTimer(led0, u16t_led0_period);
    tmr_handle_LED1 = esos_RegisterTimer(led1, u16t_led1_period);
    tmr_handle_LED2 = esos_RegisterTimer(led2, u16t_led2_period);
    tmr_handle_LED3 = esos_RegisterTimer(led3, u16t_led3_period);
    tmr_handle_nucleoLED2 = esos_RegisterTimer(nucleoLED2, u16t_nucleoLED2_period);
    //tmr_handle_commandMode = esos_RegisterTimer(commandMode, 100);
}