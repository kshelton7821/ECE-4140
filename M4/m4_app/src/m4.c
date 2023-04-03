/*
Author: Keaton Shelton
Date: 3/22/2023
Abstract:
   This is a program that will encrypt and decrypt messages using the Vigenere Cipher using
   the ESOS framework.


Questions:
n/a

Revisions:
01ks 3/22/2023: Original
02ks 4/2/2023: Added comments and cleaned up code
*/
//************** I N C L U D E S *****************
#include "embsysS20.h"
#include "circbufferH.h"
#include "vigenereH.h"
//#include "esos32/include/esos.h"
//#include "esos32/include/stm32l4_ocm3/esos_stm32l4.h"
#include "esos.h"
#include "stm32l4_ocm3/esos_stm32l4.h"

//************** G L O B A L S *****************
#define CB_SIZE 256
//Circular Buffers
circular_buffer_t volatile cb_bufferRecieve, cb_bufferSend;
//Buffers
uint8_t u8t_bufferRecieve[CB_SIZE], u8t_bufferSend[CB_SIZE];
//Various Global uint8_t
uint8_t u8t_commandTracker = 0, u8t_timArrTracker = 0;
//Time period for multiplication and entry
uint16_t u16t_timPeriod = 1000;
//Time period for print to screen
char chArr_timPeriod[5] = {'1','0','0','0', 0};
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
//Key Tracker
uint16_t u16t_keyTracker = 0;
//Various Booleans
bool bl_encrypt = true, bl_decrypt = false, bl_commandMode = false, bl_commandMessageOut = false;
//Timer
ESOS_TMR_HANDLE bigTimerHandle;

//************** F U N C T I O N S *****************
void hardware_init(void)
{
   //LED SETUP
   rcc_periph_clock_enable(RCC_GPIOA);
   gpio_mode_setup(LED2_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, LED2_Pin);
   TURN_ON_LD2();

   //Button Setup
   rcc_periph_clock_enable(RCC_GPIOC);
   gpio_mode_setup(B1_GPIO_Port, GPIO_MODE_INPUT, GPIO_PUPD_NONE, B1_Pin);
}

//************** E S O S  T A S K S *****************
ESOS_USER_TASK(encryptMode)
{
   //Variables
   static uint8_t u8t_letter, u8t_letterOUT;
   ESOS_TASK_BEGIN();

   ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
   ESOS_TASK_WAIT_ON_SEND_STRING(pch_startMessage);
   ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

   ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
   ESOS_TASK_WAIT_ON_SEND_STRING(pch_encryptMessage);
   ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
   while(1)
   {
      //Check if button pressed and set encrypt logic along with mode message
      if(IS_B1_PRESSED())
      {
         if(bl_encrypt)
         {
            u16t_keyTracker = 0;
            //Decrypt Message
            //usart_send_string(pch_decryptMessage);
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_decryptMessage);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
         }
         bl_encrypt = false;
         bl_decrypt = true;
      }
      else
      {
         if(bl_decrypt)
         {
            u16t_keyTracker = 0;
            //Encrypt Message
            //usart_send_string(pch_encryptMessage);
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_encryptMessage);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
         }
         //Test Timer = 2500/5000 = 0.5s
         bl_encrypt = true;
         bl_decrypt = false;
      }

      //Check if in Command Mode
      if(u8t_commandTracker == 3 && bl_commandMessageOut)
      {
         //Send Command Message
         ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
         ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMessage);
         ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
         bl_commandMessageOut = false;
      }
      ESOS_TASK_YIELD();
   }
   ESOS_TASK_END();
}

ESOS_USER_TASK(encryptDecrypt)
{
   static uint8_t u8t_dataOut, u8t_status;
   ESOS_TASK_BEGIN();
   while(1)
   {
      //Vigenere Encryption or Command Interpreter
      //Pull Data from Circular Buffer
      u8t_status = popBuffer(&cb_bufferRecieve, &u8t_dataOut);
      if(u8t_status == 0 && isalpha(u8t_dataOut) && bl_encrypt == true && u8t_commandTracker != 3)
      {
         u8t_dataOut = toupper(u8t_dataOut);
         //Do Encryption
         encryptBoard(&u8t_dataOut, pch_key, &u16t_keyTracker);
         pushBuffer(&cb_bufferSend, u8t_dataOut);
         //Reset Command Tracker
         u8t_commandTracker = 0;
         //Yield
         ESOS_TASK_YIELD();
      }
      else if(u8t_status == 0 && isalpha(u8t_dataOut) && bl_encrypt == false && u8t_commandTracker != 3)
      {
         u8t_dataOut = toupper(u8t_dataOut);
         //Do Decryption
         decryptBoard(&u8t_dataOut, pch_key, &u16t_keyTracker);
         pushBuffer(&cb_bufferSend, u8t_dataOut);
         //Reset Command Tracker
         u8t_commandTracker = 0;
         //Yield
         ESOS_TASK_YIELD();
      }
      //Not a normal character
      else if(u8t_status == 0 && !isalpha(u8t_dataOut) && !isdigit(u8t_dataOut) && u8t_commandTracker != 3 && u8t_dataOut != '!')
      {
         pushBuffer(&cb_bufferSend, u8t_dataOut);
         //Reset Command Tracker
         u8t_commandTracker = 0;
         //Command Error
         if(bl_commandMode)
         {
               ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
               ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandExit);
               ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
               bl_commandMode = false;
         }
         //Yeild
         ESOS_TASK_YIELD();
      }
      //Command Character
      else if(u8t_status == 0 && u8t_dataOut == '!')
      {
         u8t_commandTracker++;
         //Send
         ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
         ESOS_TASK_WAIT_ON_SEND_UINT8(u8t_dataOut);
         ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
         if(u8t_commandTracker >= 3)
         {
               //Command Mode
               bl_commandMode = true; 
               //Command Message
               bl_commandMessageOut = true;       
               //Reset Command Tracker
               if(bl_commandMode && u8t_commandTracker > 3)
               {
                  u8t_commandTracker = 0;
                  ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();
                  ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandExit);
                  ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();
                  bl_commandMode = false;
               }
         }
         ESOS_TASK_YIELD();
      }
      //Print Period Mode
      else if(u8t_status == 0 && u8t_dataOut == 'L' && u8t_commandTracker == 3)
      {
         //Send Data
         ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
         ESOS_TASK_WAIT_ON_SEND_UINT8(u8t_dataOut);
         ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

         //Reset Command Tracker
         u8t_commandTracker = 0;
         //Reset Command Mode
         bl_commandMode = false;
         //Print Period
         ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
         ESOS_TASK_WAIT_ON_SEND_STRING(pch_periodValue);
         ESOS_TASK_WAIT_ON_SEND_STRING(chArr_timPeriod);
         ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
         ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
         ESOS_TASK_YIELD();
      }
      //Set Period Mode
      else if(u8t_status == 0 && u8t_dataOut == 'S' && u8t_commandTracker == 3)
      {
         //Send Data
         ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
         ESOS_TASK_WAIT_ON_SEND_UINT8(u8t_dataOut);
         ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
         //Send Period Message
         ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
         ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandSetPeriod);
         ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
         ESOS_TASK_YIELD();
      }
      //Set Period Input
      else if(u8t_status == 0 && isdigit(u8t_dataOut) && u8t_commandTracker == 3)
      {
         ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
         ESOS_TASK_WAIT_ON_SEND_UINT8(u8t_dataOut);
         ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
         //Get Digits
         chArr_timPeriod[u8t_timArrTracker] = u8t_dataOut;
         //Increment Tracker
         u8t_timArrTracker++;
         //Set Period
         if(u8t_timArrTracker == 4)
         {
            //Turn Into Unsigned Int
            u16t_timPeriod = atoi(chArr_timPeriod);
            //Reset Tracker
            u8t_timArrTracker = 0;
            //Reset Command Tracker
            u8t_commandTracker = 0;
            //Disable Command Mode
            bl_commandMode = false;
            //Set Period and reset counter, this refused to work unless everything
            //was set to the period it needed to be
            esos_ChangeTimerPeriod(bigTimerHandle, u16t_timPeriod);
            //Send Success Message
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandSuccess);
            ESOS_TASK_WAIT_ON_SEND_STRING(chArr_timPeriod);
            ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
         }
         ESOS_TASK_YIELD();
      }
      ESOS_TASK_YIELD();
   }
   ESOS_TASK_END();
}

ESOS_USER_TASK(sendData)
{
   static uint8_t u8t_dataOut;
   ESOS_TASK_BEGIN();
   while(1)
   {
      while(popBuffer(&cb_bufferSend, &u8t_dataOut) == 0)
      {
         ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
         ESOS_TASK_WAIT_ON_SEND_UINT8(u8t_dataOut);
         ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
      }
      ESOS_TASK_YIELD();
   }
   ESOS_TASK_END();
}

ESOS_USER_TASK(recieveData)
{
   static uint8_t u8t_dataIn;
   ESOS_TASK_BEGIN();
   while(1)
   {
      ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();
      ESOS_TASK_WAIT_ON_GET_UINT8(u8t_dataIn);
      ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();
      pushBuffer(&cb_bufferRecieve, u8t_dataIn);
      ESOS_TASK_YIELD();
   }
   ESOS_TASK_END();
}

//************** T I M E R S *****************
ESOS_USER_TIMER(bigTimer)
{
   TOGGLE_LD2();
}


//************** I N I T  F U N C T I O N S *****************
void user_init(void)
{
   //Setup Hardware
   hardware_init();

   //Initialize Circular Buffer Recieve
   initBuffer(&cb_bufferRecieve, u8t_bufferRecieve, CB_SIZE);
   //Initialize Circular Buffer Transmit
   initBuffer(&cb_bufferSend, u8t_bufferSend, CB_SIZE);


   //Register ESOS Tasks
   esos_RegisterTask(encryptMode);
   esos_RegisterTask(encryptDecrypt);
   esos_RegisterTask(sendData);
   esos_RegisterTask(recieveData);
   //Register ESOS Timers
   bigTimerHandle = esos_RegisterTimer(bigTimer, 1000);
}