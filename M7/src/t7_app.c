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
 * 06ks 4/22/2023: M7 LCD Period Display Control Working, LCD Encrypt / Decrypt Working
 * 07ks 4/23/2023: MAJOR ISSUE DISCOVERED, Something with the LCD subsystem utterly screws with
 *    the ESOS_SEND_STRING function. I have no idea why, but it does. I have fixed it with using direct inserts
 *    of the string itself into the function call. DO NOT FEED ANY CHAR* ARRAYS INTO THAT FUNCTION, IT WILL
 *    START TO PRINT OUT PART OF A RANDOM OTHER CHAR* ARRAY. Seems to be a boundary issue that only occurs when
 *    the LCD is being used. Why? No clue and I'm not about to go digging into the ESOS implementation of the LCD
 *    system to see why it's doing this. All I know is it can be avoided by not using any char* arrays in the ESOS_SEND_STRING function
 *    and instead just directly insert the string into the function call. I have done this for all the strings in this program except for a very
 *    few specific ones that did not break. It has no utter consistency, changing one string call in an unrelated task can break the
 *    output of a string call in another task. Like I said, it has to be some type of bounds issue resulting in reading from other parts
 *    of memory. Anyways, onto actual changes:
 *    
 */
//******************** I N C L U D E S ***************************************
#include "ptb.h"
#include "vigenereH.h"
#include "circbufferH.h"
#include "opmode.h"
#include "keypad.h"
#include "esos_stm32l4_ptb_sui.h"
#include "esos_stm32l4_edub.h"
//
//
//
//
//******************** G L O B A L S *****************************************
// Circular Buffer Globals
#define CB_SIZE 256
circular_buffer_t volatile cb_recieve, cb_send;
uint8_t u8t_bufferRecieve[CB_SIZE], u8t_bufferSend[CB_SIZE];

// Repeat Arrays
uint8_t u8tArr_cipherArr[16], u8tArr_decipherArr[16], u8tArr_inputPeriodLCD[4];

// Key Tracker
uint16_t volatile u16t_keyTracker = 0;

// Message Strings (ALL VOIDED OUT IN REPLACEMENT OF DIRECT STRING INSERTS)
char *pch_key = "BOLDFEARLESSCONFIDENT";
//char *pch_rmNonAlphaMessage = "\nRemove Non Alpha Mode Active\r\n";
//char *pch_toUpperMessage = "\nTo Upper Mode Active\r\n";
//char *pch_echoMessage = "\nEcho Mode Active\r\n";
//char *pch_encryptMessage = "\nEncypting Mode Active\r\n";
//char *pch_decryptMessage = "\nDecrypting Mode Active\r\n";
//THIS IS THE ONLY CHAR* ARRAY THAT DOES NOT BREAK?????
char *pch_startMessage = "\nWelcome to Milestone 7, Vigenere Cipher and Other Functions\r\n";
//char *pch_commandMessage = "\nCommand Mode Intiated, Please Enter L to List Period\r\nOr Enter S to Set Period\r\n\0";
//char *pch_commandMessage = "\n Command Mode\r\n";
//char *pch_commandSetPeriod = "\nCommand Mode Set Period, Please Enter LED Number n\r\n";
//char *pch_commandExit = "\nExiting Command Mode\r\n";
//char *pch_commandSuccess = "\nExiting Command Mode\r\nTimer Set To: ";
//char *pch_commandMS = " ms\r\n";
//char *pch_errorMessage = "\nError, Invalid Command\r\n";
//char *pch_periodValue = "\nPeriod Value: ";

// Timer Periods
uint32_t volatile u32t_led0_period = 1000;
uint32_t volatile u32t_led1_period = 1000;
uint32_t volatile u32t_led2_period = 1000;
uint32_t volatile u32t_led3_period = 1000;
uint32_t volatile u32t_nucleoLED2_period = 1000;

// Timer Periods Half
uint32_t volatile u32t_led0_period_half = 500;
uint32_t volatile u32t_led1_period_half = 500;
uint32_t volatile u32t_led2_period_half = 500;
uint32_t volatile u32t_led3_period_half = 500;
uint32_t volatile u32t_nucleoLED2_period_half = 500;

// Periods for LCD
uint32_t volatile u32t_lcd_led0_period = 1000;
uint32_t volatile u32t_lcd_led1_period = 1000;
uint32_t volatile u32t_lcd_led2_period = 1000;
uint32_t volatile u32t_lcd_led3_period = 1000;
uint32_t volatile u32t_lcd_nucleoLED2_period = 1000;

// Trackers
uint8_t volatile u8t_commandCounter = 0;
uint8_t volatile u8t_arrTracker = 0;
uint8_t volatile u8tArr_periodSet[4] = {0, 0, 0, 0};
uint8_t volatile u8t_periodSetLCDTracker = 0;

// Show Period Array UART
char volatile u8tArr_showPeriod[4] = {'0', '0', '0', '0'};

// Encryption State / Other Mode Bools.
bool volatile b_encrypt = false, b_decrypt = false, b_toUpper = false, b_rmNonAlpha = false, b_echo = false, b_commandMode = false, b_commandSetPeriod = false, b_commandListPeriod = false;

// Booleans for Running LED's at half speed
bool volatile b_led0_half = false, b_led1_half = false, b_led2_half = false, b_led3_half = false;

// Booleans for editing period through LCD panel
bool volatile b_editPeriod = false;
// Operating Mode
st_opmode volatile opmode;
uint8_t volatile u8t_mode = OPMODE_ECHO;

// LCD Mode
enum LCD_MODE LCD_STATE = STANDBY;

// LED Selected for LCD
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
// LED Defines
_st_esos_sui_LED NUCELO_LED2;
_st_esos_sui_LED EDUB_LED3;
_st_esos_sui_LED EDUB_LED2;
_st_esos_sui_LED EDUB_LED1;
_st_esos_sui_LED EDUB_LED0;

// SWITCH Defines
_st_esos_sui_Switch NUCLEO_SW1;
_st_esos_sui_Switch EDUB_SW2;
_st_esos_sui_Switch EDUB_SW3;
_st_esos_sui_Switch EDUB_SW4;
_st_esos_sui_Switch EDUB_SW5;
//******************** F U N C T I O N S **************************************
// Function to choose correct selected LED

void selectLED(enum LED_SELECTED *LD_STATE, char tempKey)
{
    // Check up or down
    if (*LD_STATE == LED0)
    {
        if (tempKey == 'B')
        {
            *LD_STATE = LED1;
            return;
        }
        else
        {
            return;
        }
    }
    else if (*LD_STATE == LED1)
    {
        if (tempKey == 'A')
        {
            *LD_STATE = LED0;
            return;
        }
        else if (tempKey == 'B')
        {
            *LD_STATE = LED2;
            return;
        }
        else
        {
            return;
        }
    }
    else if (*LD_STATE == LED2)
    {
        if (tempKey == 'A')
        {
            *LD_STATE = LED1;
            return;
        }
        else if (tempKey == 'B')
        {
            *LD_STATE = LED3;
            return;
        }
        else
        {
            return;
        }
    }
    else if (*LD_STATE == LED3)
    {
        if (tempKey == 'A')
        {
            *LD_STATE = LED2;
            return;
        }
        else if (tempKey == 'B')
        {
            *LD_STATE = LED4;
            return;
        }
        else
        {
            return;
        }
    }
    else // LED4
    {
        if (tempKey == 'A')
        {
            *LD_STATE = LED3;
            return;
        }
        else
        {
            return;
        }
    }
    return;
}

void initDisplay(void)
{
    char chArr_tempPeriodOut1[4] = {'0', '0', '0', '0'};
    // Update Display to Show LED0 Stats

    // Clear Display
    esos_lcd44780_clearScreen();
    //ESOS_TASK_WAIT_ON_LCD44780_REFRESH();

    //****** Row 0 ******
    // No Up Arrow
    esos_lcd44780_writeChar(0, 0, ' ');
    // LED0
    esos_lcd44780_writeString(0, 1, "LED0");
    // Clear Current Period Array
    for (int i = 0; i < 4; i++)
    {
        chArr_tempPeriodOut1[i] = '0';
    }
    // Convert Period to String
    sprintf(chArr_tempPeriodOut1, "%lu", u32t_led0_period);
    // Write Period
    esos_lcd44780_writeChar(0, 9, chArr_tempPeriodOut1[0]);
    esos_lcd44780_writeChar(0, 10, chArr_tempPeriodOut1[1]);
    esos_lcd44780_writeChar(0, 11, chArr_tempPeriodOut1[2]);
    esos_lcd44780_writeChar(0, 12, chArr_tempPeriodOut1[3]);
    // ms
    esos_lcd44780_writeString(0, 14, "ms");

    //****** Row 1 ******
    // Down Arrow
    esos_lcd44780_writeChar(1, 0, 'v');
    // Edit Message
    esos_lcd44780_writeString(1, 1, "Press D to Edit");
}

void leftShifter(uint8_t *u8t_array, uint8_t u8t_in, size_t size)
{
    // Shift Array Left
    for (int i = 0; i < size - 1; i++)
    {
        *(u8t_array + i) = *(u8t_array + (i + 1));
    }
    // New Element
    *(u8t_array + (size - 1)) = u8t_in;
}
//******************** E S O S  C H I L D  T A S K S **************************
// Command Interpretter Task
ESOS_CHILD_TASK(interpretter, uint8_t u8t_dataIN)
{
    // UPDATE BLOCK
    //  Removed all calls to
    //  ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
    //  This utterly breaks everything with the LCD_Manager enabled. Why? I have no idea.
    //  I'm tired of trying to figure it out so if someone wants to fix it, go ahead. But it won't be me. -KS
    static uint8_t u8t_led;
    ESOS_TASK_BEGIN();
    // Check for Command
    // List LEDx Period
    if (u8t_dataIN == 'L' && u8t_commandCounter == 0)
    {
        // Echo Back
        ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
        ESOS_TASK_WAIT_ON_SEND_STRING("L\r\n");
        ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

        ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
        ESOS_TASK_WAIT_ON_SEND_STRING("ENTER 0, 1, 2, 3, 4 to select LED\r\n");
        ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

        // Increment Command Counter
        u8t_commandCounter++;
        b_commandListPeriod = true;
        b_commandSetPeriod = false;
    }
    // Check for LED Number
    else if (u8t_commandCounter == 1 && b_commandListPeriod && isdigit(u8t_dataIN))
    {
        if (u8t_dataIN == '0')
        {

            uint32_t test = u32t_led0_period;
            sprintf(u8tArr_showPeriod, "%lu", test);
            // Send LED0 Period
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING("\nPeriod Value: ");
            ESOS_TASK_WAIT_ON_SEND_STRING(u8tArr_showPeriod);
            // ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
            ESOS_TASK_WAIT_ON_SEND_STRING(" ms\r\n");
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
            //Reset period array
        }
        else if (u8t_dataIN == '1')
        {
            sprintf(u8tArr_showPeriod, "%lu", u32t_led1_period);
            // Send LED1 Period
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING("\nPeriod Value: ");
            ESOS_TASK_WAIT_ON_SEND_STRING(u8tArr_showPeriod);
            // ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
            ESOS_TASK_WAIT_ON_SEND_STRING(" ms\r\n");
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        }
        else if (u8t_dataIN == '2')
        {
            sprintf(u8tArr_showPeriod, "%lu", u32t_led2_period);
            // Send LED2 Period
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING("\nPeriod Value: ");
            ESOS_TASK_WAIT_ON_SEND_STRING(u8tArr_showPeriod);
            // ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
            ESOS_TASK_WAIT_ON_SEND_STRING(" ms\r\n");
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        }
        else if (u8t_dataIN == '3')
        {
            sprintf(u8tArr_showPeriod, "%lu", u32t_led3_period);
            // Send LED3 Period
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING("\nPeriod Value: ");
            ESOS_TASK_WAIT_ON_SEND_STRING(u8tArr_showPeriod);
            // ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
            ESOS_TASK_WAIT_ON_SEND_STRING(" ms\r\n");
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        }
        else if (u8t_dataIN == '4')
        {
            sprintf(u8tArr_showPeriod, "%lu", u32t_nucleoLED2_period);
            // Send Nucleo LED2 Period
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING("\nPeriod Value: ");
            ESOS_TASK_WAIT_ON_SEND_STRING(u8tArr_showPeriod);
            // ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS);
            ESOS_TASK_WAIT_ON_SEND_STRING(" ms\r\n");
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        }
        // Reset
        b_commandListPeriod = false;
        u8t_commandCounter = 0;
    }
    else if (u8t_dataIN == 'S' && u8t_commandCounter == 0)
    {
        // Command S Message
        ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
        ESOS_TASK_WAIT_ON_SEND_STRING("ENTER 0, 1, 2, 3, 4 to select LED\r\n");
        ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

        // Increment Command Counter
        u8t_commandCounter++;
        b_commandSetPeriod = true;
        b_commandListPeriod = false;
    }
    else if (u8t_commandCounter == 1 && b_commandSetPeriod && isdigit(u8t_dataIN))
    {
        // Check for LED Number
        if (u8t_dataIN == '0')
        {
            // Echo Back Selection
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING("LED0 has been selected\r\nEnter new period in nnnn format\r\n");
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

            // Select LED0
            u8t_led = 0;
            u8t_commandCounter++;
        }
        else if (u8t_dataIN == '1')
        {
            // Echo Back Selection
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING("LED1 has been selected\r\nEnter new period in nnnn format\r\n");
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

            // Select LED1
            u8t_led = 1;
            u8t_commandCounter++;
        }
        else if (u8t_dataIN == '2')
        {
            // Echo Back Selection
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING("LED2 has been selected\r\nEnter new period in nnnn format\r\n");
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

            // Select LED2
            u8t_led = 2;
            u8t_commandCounter++;
        }
        else if (u8t_dataIN == '3')
        {
            // Echo Back Selection
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING("LED3 has been selected\r\nEnter new period in nnnn format\r\n");
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

            // Select LED3
            u8t_led = 3;
            u8t_commandCounter++;
        }
        else if (u8t_dataIN == '4')
        {
            // Echo Back Selection
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING("Nucleo LED2 has been selected\r\nEnter new period in nnnn format\r\n");
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

            // Select Nucleo LED2
            u8t_led = 4;
            u8t_commandCounter++;
        }
    }
    else if (u8t_commandCounter == 2 && b_commandSetPeriod && isdigit(u8t_dataIN))
    {
        // Take in period
        u8tArr_periodSet[u8t_arrTracker] = u8t_dataIN;
        // Increment Array Tracker
        u8t_arrTracker++;
        // Check if period is complete
        if (u8t_arrTracker > 3)
        {
            // Set Period for respective LED
            if (u8t_led == 0)
            {
                u32t_led0_period = atoi(u8tArr_periodSet);
                u32t_led0_period_half = u32t_led0_period / 2;
                esos_ChangeTimerPeriod(tmr_handle_LED0, u32t_led0_period);

                // Send LED0 Period
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING("Period Set To: ");
                ESOS_TASK_WAIT_ON_SEND_STRING(u8tArr_periodSet);
                // ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS); -- Exact issue specified on line 936
                ESOS_TASK_WAIT_ON_SEND_STRING(" ms\r\n");
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

                // Fix stupid bug that took me 4 hours to find with the List mode
                for (int i = 0; i < 4; i++)
                {
                    u8tArr_periodSet[i] = '0';
                }
            }
            else if (u8t_led == 1)
            {
                u32t_led1_period = atoi(u8tArr_periodSet);
                u32t_led1_period_half = u32t_led1_period / 2;
                esos_ChangeTimerPeriod(tmr_handle_LED1, u32t_led1_period);

                // Send LED1 Period
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING("Period Set To: ");
                ESOS_TASK_WAIT_ON_SEND_STRING(u8tArr_periodSet);
                // ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS); -- Exact issue specified on line 936
                ESOS_TASK_WAIT_ON_SEND_STRING(" ms\r\n");
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

                // Fix stupid bug that took me 4 hours to find with the List mode
                for (int i = 0; i < 4; i++)
                {
                    u8tArr_periodSet[i] = '0';
                }
            }
            else if (u8t_led == 2)
            {
                u32t_led2_period = atoi(u8tArr_periodSet);
                u32t_led2_period_half = u32t_led2_period / 2;
                esos_ChangeTimerPeriod(tmr_handle_LED2, u32t_led2_period);

                // Send LED2 Period
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING("Period Set To: ");
                ESOS_TASK_WAIT_ON_SEND_STRING(u8tArr_periodSet);
                // ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS); -- Exact issue specified on line 936
                ESOS_TASK_WAIT_ON_SEND_STRING(" ms\r\n");
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

                // Fix stupid bug that took me 4 hours to find with the List mode
                for (int i = 0; i < 4; i++)
                {
                    u8tArr_periodSet[i] = '0';
                }
            }
            else if (u8t_led == 3)
            {
                u32t_led3_period = atoi(u8tArr_periodSet);
                u32t_led3_period_half = u32t_led3_period / 2;
                esos_ChangeTimerPeriod(tmr_handle_LED3, u32t_led3_period);

                // Send LED3 Period
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING("Period Set To: ");
                ESOS_TASK_WAIT_ON_SEND_STRING(u8tArr_periodSet);
                // ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS); -- Exact issue specified on line 936
                ESOS_TASK_WAIT_ON_SEND_STRING(" ms\r\n");
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

                // Fix stupid bug that took me 4 hours to find with the List mode
                for (int i = 0; i < 4; i++)
                {
                    u8tArr_periodSet[i] = '0';
                }
            }
            else if (u8t_led == 4)
            {
                u32t_nucleoLED2_period = atoi(u8tArr_periodSet);
                u32t_nucleoLED2_period_half = u32t_nucleoLED2_period / 2;
                esos_ChangeTimerPeriod(tmr_handle_nucleoLED2, u32t_nucleoLED2_period);

                // Send Nucleo LED2 Period
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING("Period Set To: ");
                ESOS_TASK_WAIT_ON_SEND_STRING(u8tArr_periodSet);
                // ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMS); -- Exact issue specified on line 936
                ESOS_TASK_WAIT_ON_SEND_STRING(" ms\r\n");
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();

                // Fix stupid bug that took me 4 hours to find with the List mode
                for (int i = 0; i < 4; i++)
                {
                    u8tArr_periodSet[i] = '0';
                }
            }
            // Reset Array Tracker
            u8t_arrTracker = 0;
            // Reset Command Counter
            u8t_commandCounter = 0;
            // Reset Command Flag
            b_commandSetPeriod = false;
            // Reset Period Flag
            b_commandListPeriod = false;
        }
    }
    else
    {
        // Input Error
        // Reset Variables
        u8t_commandCounter = 0;
        u8t_arrTracker = 0;
        b_commandSetPeriod = false;
        b_commandListPeriod = false;
        // Send Error Message
        ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
        ESOS_TASK_WAIT_ON_SEND_STRING("\nError, Invalid Command\r\n");
        ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
    }
    ESOS_TASK_END();
}

// Remove Non-Alpha Task
ESOS_CHILD_TASK(removeNonAlpha, uint8_t u8t_dataIN)
{
    ESOS_TASK_BEGIN();
    // If so, check if it is alpha
    if (isalpha(u8t_dataIN) || isdigit(u8t_dataIN))
    {
        // Push to outbound buffer
        pushBuffer(&cb_send, u8t_dataIN);
    }
    ESOS_TASK_END();
}

// To Upper
ESOS_CHILD_TASK(toUpperFunc, uint8_t u8t_dataIN)
{
    ESOS_TASK_BEGIN();
    // If so, check if it is lower case
    if (islower(u8t_dataIN))
    {
        u8t_dataIN = toupper(u8t_dataIN);
        pushBuffer(&cb_send, u8t_dataIN);
    }
    ESOS_TASK_END();
}

// Encrypt Task
ESOS_CHILD_TASK(encryptUINT, uint8_t u8t_dataIN)
{
    ESOS_TASK_BEGIN();
    if (isalpha(u8t_dataIN))
    {
        // If so, check if it is lower case
        if (islower(u8t_dataIN))
        {
            u8t_dataIN = toupper(u8t_dataIN);
        }
        // Add to Decrypted Buffer
        leftShifter(&u8tArr_decipherArr, u8t_dataIN, (sizeof(u8tArr_decipherArr) / sizeof(u8tArr_decipherArr[0])));
        // Encrypt
        encryptBoard(&u8t_dataIN, pch_key, &u16t_keyTracker);
        // Add to Cyper Buffer
        leftShifter(&u8tArr_cipherArr, u8t_dataIN, (sizeof(u8tArr_decipherArr) / sizeof(u8tArr_decipherArr[0])));
        // Push to outbound buffer
        pushBuffer(&cb_send, u8t_dataIN);
    }
    ESOS_TASK_END();
}
// Decrypt Task
ESOS_CHILD_TASK(decryptUINT, uint8_t u8t_dataIN)
{
    ESOS_TASK_BEGIN();
    // If so, check if it is alpha
    if (isalpha(u8t_dataIN))
    {
        // If so, check if it is lower case
        if (islower(u8t_dataIN))
        {
            u8t_dataIN = toupper(u8t_dataIN);
        }
        // Add to Cipher Buffer
        leftShifter(&u8tArr_cipherArr, u8t_dataIN, (sizeof(u8tArr_decipherArr) / sizeof(u8tArr_decipherArr[0])));
        // Decrypt
        decryptBoard(&u8t_dataIN, pch_key, &u16t_keyTracker);
        // Add to Decrypted Buffer
        leftShifter(&u8tArr_decipherArr, u8t_dataIN, (sizeof(u8tArr_decipherArr) / sizeof(u8tArr_decipherArr[0])));

        // Push to outbound buffer
        pushBuffer(&cb_send, u8t_dataIN);
    }
    ESOS_TASK_END();
}
//
//
//
//
//******************** E S O S  T A S K S *************************************
// LCD Task
ESOS_USER_TASK(lcd_manager)
{
    static uint16_t u16t_tempKeys;
    static uint8_t volatile u8t_tempNum = ' ';
    // Show Period Array LCD
    static uint8_t u8tArr_tempPeriodOut[4] = {'0', '0', '0', '0'};
    static uint8_t u8tArr_periodSetLCD[4] = {'_', '_', '_', '_'};
    ESOS_TASK_BEGIN();
    while (1)
    {
        // Check LCD State
        if (LCD_STATE == STANDBY)
        {
            // Get Keys
            u16t_tempKeys = keypad_entry();
            // Check if key was move up or down
            if (u16t_tempKeys & KEYPAD_KEYA_MASK)
            {
                selectLED(&LED_STATE, 'A');
                // WAIT FOR DEBOUNCE
                ESOS_TASK_WAIT_UNTIL(keypad_entry() == 0);
            }
            else if (u16t_tempKeys & KEYPAD_KEYB_MASK)
            {
                selectLED(&LED_STATE, 'B');
                // WAIT FOR DEBOUNCE
                ESOS_TASK_WAIT_UNTIL(keypad_entry() == 0);
            }
            // Check which LED is selected
            if (LED_STATE == LED0)
            {
                // Update Display to Show LED0 Stats

                // Clear Display
                esos_lcd44780_clearScreen();

                //****** Row 0 ******
                // No Up Arrow
                esos_lcd44780_writeChar(0, 0, ' ');
                // LED0
                esos_lcd44780_writeString(0, 1, "LED0");
                // Clear Current Period Array
                for (int i = 0; i < 4; i++)
                {
                    u8tArr_tempPeriodOut[i] = '0';
                }

                // Convert Period to String
                sprintf(u8tArr_tempPeriodOut, "%lu", u32t_lcd_led0_period);
                // Write Period
                esos_lcd44780_writeString(0, 9, u8tArr_tempPeriodOut);
                // ms
                esos_lcd44780_writeString(0, 14, "ms");

                //****** Row 1 ******
                // Down Arrow
                esos_lcd44780_writeChar(1, 0, 'v');
                // Edit Message
                esos_lcd44780_writeString(1, 1, "Press D to Edit");
                for (int i = 0; i < 4; i++)
                {
                    u8tArr_tempPeriodOut[i] = '0';
                }

                // Wait for Debounce
                ESOS_TASK_WAIT_TICKS(100);
                ESOS_TASK_WAIT_ON_LCD44780_REFRESH();
                ESOS_TASK_YIELD();
            }
            else if (LED_STATE == LED1)
            {
                // Update Display to Show LED1 Stats

                // Clear Display
                esos_lcd44780_clearScreen();

                //****** Row 0 ******
                // Up Arrow
                esos_lcd44780_writeChar(0, 0, '^');
                // LED1
                esos_lcd44780_writeString(0, 1, "LED1");
                // Clear Current Period Array
                for (int i = 0; i < 4; i++)
                {
                    u8tArr_tempPeriodOut[i] = '0';
                }
                // Convert Period to String
                sprintf(u8tArr_tempPeriodOut, "%lu", u32t_lcd_led1_period);
                // Write Period
                esos_lcd44780_writeString(0, 9, u8tArr_tempPeriodOut);
                // ms
                esos_lcd44780_writeString(0, 14, "ms");

                //****** Row 1 ******
                // Down Arrow
                esos_lcd44780_writeChar(1, 0, 'v');
                // Edit Message
                esos_lcd44780_writeString(1, 1, "Press D to Edit");
                // Wait for Debounce
                ESOS_TASK_WAIT_TICKS(100);
                ESOS_TASK_WAIT_ON_LCD44780_REFRESH();
                ESOS_TASK_YIELD();
            }
            else if (LED_STATE == LED2)
            {
                // Update Display to Show LED2 Stats

                // Clear Display
                esos_lcd44780_clearScreen();

                //****** Row 0 ******
                // Up Arrow
                esos_lcd44780_writeChar(0, 0, '^');
                // LED2
                esos_lcd44780_writeString(0, 1, "LED2");
                // Clear Current Period Array
                for (int i = 0; i < 4; i++)
                {
                    u8tArr_tempPeriodOut[i] = '0';
                }
                // Convert Period to String
                sprintf(u8tArr_tempPeriodOut, "%lu", u32t_lcd_led2_period);
                // Write Period
                esos_lcd44780_writeString(0, 9, u8tArr_tempPeriodOut);
                // ms
                esos_lcd44780_writeString(0, 14, "ms");

                //****** Row 1 ******
                // Down Arrow
                esos_lcd44780_writeChar(1, 0, 'v');
                // Edit Message
                esos_lcd44780_writeString(1, 1, "Press D to Edit");
                // Wait for Debounce
                ESOS_TASK_WAIT_TICKS(100);
                ESOS_TASK_WAIT_ON_LCD44780_REFRESH();
                ESOS_TASK_YIELD();
            }
            else if (LED_STATE == LED3)
            {
                // Update Display to Show LED3 Stats

                // Clear Display
                esos_lcd44780_clearScreen();

                //****** Row 0 ******
                // Up Arrow
                esos_lcd44780_writeChar(0, 0, '^');
                // LED3
                esos_lcd44780_writeString(0, 1, "LED3");
                // Clear Current Period Array
                for (int i = 0; i < 4; i++)
                {
                    u8tArr_tempPeriodOut[i] = '0';
                }
                // Convert Period to String
                sprintf(u8tArr_tempPeriodOut, "%lu", u32t_lcd_led3_period);
                // Write Period
                esos_lcd44780_writeString(0, 9, u8tArr_tempPeriodOut);
                // ms
                esos_lcd44780_writeString(0, 14, "ms");

                //****** Row 1 ******
                // Down Arrow
                esos_lcd44780_writeChar(1, 0, 'v');
                // Edit Message
                esos_lcd44780_writeString(1, 1, "Press D to Edit");
                // Wait for Debounce
                ESOS_TASK_WAIT_TICKS(100);
                ESOS_TASK_WAIT_ON_LCD44780_REFRESH();
                ESOS_TASK_YIELD();
            }
            else if (LED_STATE == LED4)
            {
                // Update Display to Show LED4 Stats

                // Clear Display
                esos_lcd44780_clearScreen();

                //****** Row 0 ******
                // Up Arrow
                esos_lcd44780_writeChar(0, 0, '^');
                // LED4
                esos_lcd44780_writeString(0, 1, "LED4");
                // Clear Current Period Array
                for (int i = 0; i < 4; i++)
                {
                    u8tArr_tempPeriodOut[i] = '0';
                }
                // Convert Period to String
                sprintf(u8tArr_tempPeriodOut, "%lu", u32t_lcd_nucleoLED2_period);
                // Write Period
                esos_lcd44780_writeString(0, 9, u8tArr_tempPeriodOut);
                // ms
                esos_lcd44780_writeString(0, 14, "ms");

                //****** Row 1 ******
                // No Down Arrow
                esos_lcd44780_writeChar(1, 0, ' ');
                // Edit Message
                esos_lcd44780_writeString(1, 1, "Press D to Edit");
                // Wait for Debounce
                ESOS_TASK_WAIT_TICKS(100);
                ESOS_TASK_WAIT_ON_LCD44780_REFRESH();
                ESOS_TASK_YIELD();
            }
        }
        else if (LCD_STATE == EDIT)
        {
            //DEV
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_STRING("Made it to Edit!\r\n");
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
            //Begin Updates
            if (LED_STATE == LED0)
            {
                //Wait for Debounce from D key
                ESOS_TASK_WAIT_UNTIL((keypad_entry()) == 0);
                //Reset u8t_tempNum
                u8t_tempNum = ' ';
                //NEW STUFF TO TEST
                //Get it stuck in a loop until the user presses the * key
                do
                {
                    // Get Keys
                    u16t_tempKeys = keypad_entry();
                    //WAIT FOR DEBOUNCE
                    ESOS_TASK_WAIT_UNTIL((keypad_entry()) == 0);
                    //Acquire the number
                    u8t_tempNum = keypad_interpret(u16t_tempKeys);
                    //Check if it is a number
                    if(u16t_tempKeys & KEYPAD_ONLY_NUMS)
                    {
                        //Shift into the array
                        leftShifter(&u8tArr_periodSetLCD, u8t_tempNum, (sizeof(u8tArr_periodSetLCD)/sizeof(u8tArr_periodSetLCD[0])));
                        //Wait
                        ESOS_TASK_WAIT_TICKS(300);
                        ESOS_TASK_WAIT_UNTIL((keypad_entry()) == 0);
                    }
                    //No Entry Update Display
                    else
                    {
                        //Clear Display
                        esos_lcd44780_clearScreen();
                        //LED0
                        esos_lcd44780_writeString(0, 1, "LED0");
                        //Current Buffer
                        //esos_lcd44780_writeString(0, 9, u8tArr_periodSetLCD);
                        esos_lcd44780_writeChar(0, 9, u8tArr_periodSetLCD[0]);
                        esos_lcd44780_writeChar(0, 10, u8tArr_periodSetLCD[1]);
                        esos_lcd44780_writeChar(0, 11, u8tArr_periodSetLCD[2]);
                        esos_lcd44780_writeChar(0, 12, u8tArr_periodSetLCD[3]);
                        //esos_lcd44780_writeBuffer(0, 9, u8tArr_periodSetLCD, 4);
                        //ms
                        //esos_lcd44780_writeString(0, 14, "ms");
                        //Confirm Message
                        esos_lcd44780_writeString(1, 1, "Press * to Save");
                        ESOS_TASK_WAIT_TICKS(300);
                    }
                    //IN LOOP
                    ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                    ESOS_TASK_WAIT_ON_SEND_STRING("Made it to LED0 Loop!\r\n");
                    ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                    ESOS_TASK_WAIT_TICKS(500);
                } while(u8t_tempNum != '*');
                //Loop is broken, user has pressed *
                //Delete '_' from the array
                for (int i = 0; i < (sizeof(u8tArr_periodSetLCD)/sizeof(u8tArr_periodSetLCD[0])); i++)
                {
                    if(u8tArr_periodSetLCD[i] == '_')
                    {
                        u8tArr_periodSetLCD[i] = '0';
                    }
                }

                //Set New Period
                u32t_led0_period = atoi(u8tArr_periodSetLCD);
                u32t_led0_period = u32t_led0_period / 1000;
                //Set Timer
                esos_ChangeTimerPeriod(tmr_handle_LED0, u32t_led0_period);
                //Set LCD State back to Standby
                LCD_STATE = STANDBY;
                //No longer editing period
                b_editPeriod = false;
                //Reset Array
                for (int i = 0; i < (sizeof(u8tArr_periodSetLCD)/sizeof(u8tArr_periodSetLCD[0])); i++)
                {
                    u8tArr_periodSetLCD[i] = '_';
                }
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING("Made it to LED0!");
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                //Finally Release
                ESOS_TASK_YIELD();
            }
        }
        else // LCD_STATE == REPEAT
        {
            // Get Keys
            u16t_tempKeys = keypad_entry();
            //TEST THIS
            //Check for Keypad Entry State coming from REPEAT MODE
            if (u16t_tempKeys & KEYPAD_KEYD_MASK)
            {
                //GOTO EDIT MODE
                LCD_STATE = EDIT;
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING("EDIT MODE");
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_UNTIL(keypad_entry() == 0);
                b_editPeriod = true;

            }
            //Row 0
            esos_lcd44780_writeString(0, 0, u8tArr_decipherArr);
            //Row 1
            esos_lcd44780_writeString(1, 0, u8tArr_cipherArr);
        }
        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

// USART Sending Task
ESOS_USER_TASK(sending)
{
    static uint8_t u8t_dataOut;
    ESOS_TASK_BEGIN();
    while (1)
    {
        // Check if anything is in outbound buffer
        while (popBuffer(&cb_send, &u8t_dataOut) == 0)
        {
            // If so, send it out
            ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
            ESOS_TASK_WAIT_ON_SEND_UINT8(u8t_dataOut);
            ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
        }
        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

// USART Recieving Task
ESOS_USER_TASK(recieving)
{
    static uint8_t u8t_dataIn;
    ESOS_TASK_BEGIN();
    // Send Welcome Message
    ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
    ESOS_TASK_WAIT_ON_SEND_STRING(pch_startMessage);
    ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
    while (1)
    {
        // Check if anything is in inbound buffer
        ESOS_TASK_WAIT_ON_AVAILABLE_IN_COMM();
        ESOS_TASK_WAIT_ON_GET_UINT8(u8t_dataIn);
        ESOS_TASK_SIGNAL_AVAILABLE_IN_COMM();
        pushBuffer(&cb_recieve, u8t_dataIn);
        ESOS_TASK_YIELD();
    }
    ESOS_TASK_END();
}

// Mode Select Task
ESOS_USER_TASK(modeSelect)
{
    static uint8_t u8t_dataIn;
    static uint8_t u8t_buttons[5] = {0, 0, 0, 0, 0};

    ESOS_TASK_HANDLE tskHandle_imTired;
    ESOS_TASK_BEGIN();
    while (1)
    {
        // If in command mode
        if (!esos_hw_sui_isSwitchPressed(h_SW1))
        {
            // Change LCD Mode
            LCD_STATE = STANDBY;
            // Check for other switches
            if (esos_hw_sui_isSwitchPressed(h_SW2))
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
                // Reset
                b_led0_half = false;
                b_led1_half = false;
                b_led2_half = false;
                b_led3_half = false;
            }

            // Check if previously in command mode
            if (!b_commandMode)
            {
                //UPDATE BLOCK
                // Took out all this send string for command mode.
                // Why? Utterly breaks when LCD manager is enabled, don't ask my why
                // Since I can't tell you. Has to be some random ESOS crap that I'm tired
                // of trying to figure out. -KS
                // UPDATE BLOCK 2
                // FIGURED IT OUT, IF YOU PASS A CHAR ARRAY TO SEND_STRING IT UTTERLY BREAKS FOR CERTAIN
                // STRINGS, WHY? I DON'T KNOW, BUT I'M NOT GOING TO WASTE MY TIME FIGURING IT OUT
                // THATS AN ESOS ISSUE THAT I WILL NOT BE TRYING TO DEBUG. IF I HAVE TIME I WILL
                // RE-ADD ALL FORMATTING MESSAGES THAT MADE OUR OUTPUT LOOK PRETTY. WHY DOES
                // OTHER SEND_STRING CALLS WORK WITH THE CHAR* ARRAYS BUT OTHERS DON'T OR JUST
                // STRAIGHT UP OUPUT A DIFFERENT CHAR* ARRAY? WHO KNOWS, NOT ME. I'M NOT THE ESOS
                // MAINTAINER, SORRY FOR ALL CAPS, LEFT CAPS ON AND DONT WANT TO RETYPE THIS -KS
                // Send Message
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                //ESOS_TASK_WAIT_ON_SEND_STRING(pch_commandMessage); -THIS DOESN'T WORK WITH EXACT SAME STRING??? FAILS ENTIRELY IN ARRAY FORMAT, OUTPUTS PART OF OTHER CHAR* ARRAY IN CHAR* FORMAT
                ESOS_TASK_WAIT_ON_SEND_STRING("\nCommand Mode Intiated, Please Enter L to List Period\r\nOr Enter S to Set Period\r\n");
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                u16t_keyTracker = 0;

                // Reset Repeat Arrays to spaces
                for (int i = 0; i < 16; i++)
                {
                    u8tArr_cipherArr[i] = ' ';
                    u8tArr_decipherArr[i] = ' ';
                }
            }
            // Set various bools
            b_commandMode = true;
            b_encrypt = false;
            b_decrypt = false;
            b_toUpper = false;
            b_rmNonAlpha = false;
            b_echo = false;

            if (popBuffer(&cb_recieve, &u8t_dataIn) == 0)
            {
                // Spawn command mode task
                ESOS_ALLOCATE_CHILD_TASK(tskHandle_imTired);
                ESOS_TASK_SPAWN_AND_WAIT(tskHandle_imTired, interpretter, u8t_dataIn);
                ESOS_TASK_YIELD();
            }
        }
        else if (esos_hw_sui_isSwitchPressed(h_SW2))
        {
            // Change LCD Mode
            LCD_STATE = STANDBY;
            // Check if previously in rmNonAlpha mode
            if (!b_rmNonAlpha)
            {
                // Send Message
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING("\nRemove Non Alpha Mode Active\r\n");
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                u16t_keyTracker = 0;

                // Reset Repeat Arrays to spaces
                for (int i = 0; i < 16; i++)
                {
                    u8tArr_cipherArr[i] = ' ';
                    u8tArr_decipherArr[i] = ' ';
                }
            }
            // Set various bools
            b_rmNonAlpha = true;
            b_encrypt = false;
            b_decrypt = false;
            b_toUpper = false;
            b_echo = false;
            b_commandMode = false;
            b_commandListPeriod = false;
            b_commandSetPeriod = false;

            if (popBuffer(&cb_recieve, &u8t_dataIn) == 0)
            {
                // Spawn rmNonAlpha task
                ESOS_ALLOCATE_CHILD_TASK(tskHandle_imTired);
                ESOS_TASK_SPAWN_AND_WAIT(tskHandle_imTired, removeNonAlpha, u8t_dataIn);
                ESOS_TASK_YIELD();
            }
        }
        else if (esos_hw_sui_isSwitchPressed(h_SW3))
        {
            // Change LCD Mode
            LCD_STATE = STANDBY;
            // Check if previously in toUpper mode
            if (!b_toUpper)
            {
                // Send Message
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING("\nTo Upper Mode Active\r\n");
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                u16t_keyTracker = 0;

                // Reset Repeat Arrays to spaces
                for (int i = 0; i < 16; i++)
                {
                    u8tArr_cipherArr[i] = ' ';
                    u8tArr_decipherArr[i] = ' ';
                }
            }
            // Set various bools
            b_toUpper = true;
            b_encrypt = false;
            b_decrypt = false;
            b_rmNonAlpha = false;
            b_echo = false;
            b_commandMode = false;
            b_commandListPeriod = false;
            b_commandSetPeriod = false;

            if (popBuffer(&cb_recieve, &u8t_dataIn) == 0)
            {
                // Spawn toUpper task
                ESOS_ALLOCATE_CHILD_TASK(tskHandle_imTired);
                ESOS_TASK_SPAWN_AND_WAIT(tskHandle_imTired, toUpperFunc, u8t_dataIn);
                ESOS_TASK_YIELD();
            }
        }
        else if (esos_hw_sui_isSwitchPressed(h_SW4))
        {
            // Change LCD Mode
            LCD_STATE = REPEAT;
            // Check if previously in encrypt mode
            if (!b_encrypt)
            {
                // Send Message
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING("\nEncypting Mode Active\r\n");
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                // Reset key tracker
                u16t_keyTracker = 0;
            }
            // Set various bools
            b_encrypt = true;
            b_decrypt = false;
            b_toUpper = false;
            b_rmNonAlpha = false;
            b_echo = false;
            b_commandMode = false;
            b_commandListPeriod = false;
            b_commandSetPeriod = false;

            if (popBuffer(&cb_recieve, &u8t_dataIn) == 0)
            {
                // Spawn encrypt task
                ESOS_ALLOCATE_CHILD_TASK(tskHandle_imTired);
                ESOS_TASK_SPAWN_AND_WAIT(tskHandle_imTired, encryptUINT, u8t_dataIn);
                ESOS_TASK_YIELD();
            }
        }
        else if (esos_hw_sui_isSwitchPressed(h_SW5))
        {
            // Change LCD Mode
            LCD_STATE = REPEAT;
            // Check if previously in decrypt mode
            if (!b_decrypt)
            {
                // Send Message
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING("\nDecrypting Mode Active\r\n");
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                // Reset key tracker
                u16t_keyTracker = 0;
            }
            // Set various bools
            b_encrypt = false;
            b_decrypt = true;
            b_toUpper = false;
            b_rmNonAlpha = false;
            b_echo = false;
            b_commandMode = false;
            b_commandListPeriod = false;
            b_commandSetPeriod = false;

            if (popBuffer(&cb_recieve, &u8t_dataIn) == 0)
            {
                // Spawn decrypt task
                ESOS_ALLOCATE_CHILD_TASK(tskHandle_imTired);
                ESOS_TASK_SPAWN_AND_WAIT(tskHandle_imTired, decryptUINT, u8t_dataIn);
                ESOS_TASK_YIELD();
            }
        }
        else // OPMODE_ECHO
        {
            // Change LCD Mode
            if(b_editPeriod)
            {
                LCD_STATE = EDIT;
            }
            else
            {
                LCD_STATE = STANDBY;
            }
            // Check if previously in echo mode
            if (!b_echo)
            {
                // Send Message
                ESOS_TASK_WAIT_ON_AVAILABLE_OUT_COMM();
                ESOS_TASK_WAIT_ON_SEND_STRING("\nEcho Mode Active\r\n");
                ESOS_TASK_SIGNAL_AVAILABLE_OUT_COMM();
                u16t_keyTracker = 0;

                // Reset Repeat Arrays to spaces
                for (int i = 0; i < 16; i++)
                {
                    u8tArr_cipherArr[i] = ' ';
                    u8tArr_decipherArr[i] = ' ';
                }
            }

            // Set various bools
            b_encrypt = false;
            b_decrypt = false;
            b_toUpper = false;
            b_rmNonAlpha = false;
            b_echo = true;
            b_commandMode = false;
            b_commandListPeriod = false;
            b_commandSetPeriod = false;

            if (popBuffer(&cb_recieve, &u8t_dataIn) == 0)
            {
                // push to outbound buffer
                pushBuffer(&cb_send, u8t_dataIn);
            }

            ESOS_TASK_YIELD();
        }
        // Various Checks for half speed
        if (b_led0_half && esos_hw_sui_isSwitchPressed(h_SW5) && !esos_hw_sui_isSwitchPressed(h_SW1))
        {
            esos_ChangeTimerPeriod(tmr_handle_LED0, u32t_led0_period_half);
        }
        else if (b_led1_half && esos_hw_sui_isSwitchPressed(h_SW4) && !esos_hw_sui_isSwitchPressed(h_SW1))
        {
            esos_ChangeTimerPeriod(tmr_handle_LED1, u32t_led1_period_half);
        }
        else if (b_led2_half && esos_hw_sui_isSwitchPressed(h_SW3) && !esos_hw_sui_isSwitchPressed(h_SW1))
        {
            esos_ChangeTimerPeriod(tmr_handle_LED2, u32t_led2_period_half);
            // LCD PERIOD
            u32t_lcd_led2_period = u32t_led2_period_half;
        }
        else if (b_led3_half && esos_hw_sui_isSwitchPressed(h_SW2) && !esos_hw_sui_isSwitchPressed(h_SW1))
        {
            esos_ChangeTimerPeriod(tmr_handle_LED3, u32t_led3_period_half);
            // LCD PERIOD
            u32t_lcd_led3_period = u32t_led3_period_half;
        }
        else
        {
            // Return to normal speed
            esos_ChangeTimerPeriod(tmr_handle_LED0, u32t_led0_period);
            esos_ChangeTimerPeriod(tmr_handle_LED1, u32t_led1_period);
            esos_ChangeTimerPeriod(tmr_handle_LED2, u32t_led2_period);
            esos_ChangeTimerPeriod(tmr_handle_LED3, u32t_led3_period);

            // LCD PERIOD
            u32t_lcd_led0_period = u32t_led0_period;
            u32t_lcd_led1_period = u32t_led1_period;
            u32t_lcd_led2_period = u32t_led2_period;
            u32t_lcd_led3_period = u32t_led3_period;
            u32t_lcd_nucleoLED2_period = u32t_nucleoLED2_period;
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
// LED0 Timer
ESOS_USER_TIMER(led0)
{
    // Toggle LED0
    esos_hw_sui_toggleLED(h_LED0);
}

// LED1 Timer
ESOS_USER_TIMER(led1)
{
    // Toggle LED1
    esos_hw_sui_toggleLED(h_LED1);
}

// LED2 Timer
ESOS_USER_TIMER(led2)
{
    // Toggle LED2
    esos_hw_sui_toggleLED(h_LED2);
}

// LED3 Timer
ESOS_USER_TIMER(led3)
{
    // Toggle LED3
    esos_hw_sui_toggleLED(h_LED3);
}

// Nucleo LED2 Timer
ESOS_USER_TIMER(nucleoLED2)
{
    // Toggle Nucleo LED2
    esos_hw_sui_toggleLED(h_LED4);
}

// Command Mode Timer
ESOS_USER_TIMER(commandMode)
{
    bool b_buttons[5] = {0, 0, 0, 0, 0};
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
    // Setup RCC for buttons and LEDs
    GPIOA_SETUP_RCC();
    GPIOB_SETUP_RCC();
    GPIOC_SETUP_RCC();
    // ESOS HW setup
    // Define LEDs
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

    // Define Buttons
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

    // Register LEDs
    h_LED0 = esos_sui_registerLED(EDUB_LED0.u32_userData1, EDUB_LED0.u32_userData2);
    h_LED1 = esos_sui_registerLED(EDUB_LED1.u32_userData1, EDUB_LED1.u32_userData2);
    h_LED2 = esos_sui_registerLED(EDUB_LED2.u32_userData1, EDUB_LED2.u32_userData2);
    h_LED3 = esos_sui_registerLED(EDUB_LED3.u32_userData1, EDUB_LED3.u32_userData2);
    h_LED4 = esos_sui_registerLED(NUCELO_LED2.u32_userData1, NUCELO_LED2.u32_userData2);

    // Register Buttons
    h_SW1 = esos_sui_registerSwitch(NUCLEO_SW1.u32_userData1, NUCLEO_SW1.u32_userData2);
    h_SW2 = esos_sui_registerSwitch(EDUB_SW2.u32_userData1, EDUB_SW2.u32_userData2);
    h_SW3 = esos_sui_registerSwitch(EDUB_SW3.u32_userData1, EDUB_SW3.u32_userData2);
    h_SW4 = esos_sui_registerSwitch(EDUB_SW4.u32_userData1, EDUB_SW4.u32_userData2);
    h_SW5 = esos_sui_registerSwitch(EDUB_SW5.u32_userData1, EDUB_SW5.u32_userData2);



    // Config LEDs
    esos_hw_sui_configLED(h_LED0);
    esos_hw_sui_configLED(h_LED1);
    esos_hw_sui_configLED(h_LED2);
    esos_hw_sui_configLED(h_LED3);
    esos_hw_sui_configLED(h_LED4);

    // Eduboard Button Setup
    EDUB_KEYPAD_ROW0_SETUP();
    EDUB_KEYPAD_ROW1_SETUP();
    EDUB_KEYPAD_ROW2_SETUP();
    EDUB_KEYPAD_ROW3_SETUP();
    EDUB_KEYPAD_COL0_SETUP();
    EDUB_KEYPAD_COL1_SETUP();
    EDUB_KEYPAD_COL2_SETUP();
    EDUB_KEYPAD_COL3_SETUP();

    // Set all Columns Low (possible fix for button / keypad dual reads)
    EDUB_KEYPAD_COL0_CLEAR();
    EDUB_KEYPAD_COL1_CLEAR();
    EDUB_KEYPAD_COL2_CLEAR();
    EDUB_KEYPAD_COL3_CLEAR();

    // Config Buttons
    esos_hw_sui_configSwitch(h_SW1);
    esos_hw_sui_configSwitch(h_SW2);
    esos_hw_sui_configSwitch(h_SW3);
    esos_hw_sui_configSwitch(h_SW4);
    esos_hw_sui_configSwitch(h_SW5);

    // Setup LCD
    esos_lcd44780_configDisplay();
    __esos_lcd44780_init();
    // Turn off cursor
    esos_lcd44780_setCursorDisplay(false);
    // Default
    initDisplay();
}

void user_init(void)
{
    // Initialize Hardware
    hw_init();


    // Initialize Software Structures
    initBuffer(&cb_recieve, u8t_bufferRecieve, CB_SIZE);
    initBuffer(&cb_send, u8t_bufferSend, CB_SIZE);
    fnst_opmodeInit(&opmode);

    // Initialize ESOS Tasks
    esos_RegisterTask(recieving);
    esos_RegisterTask(sending);
    esos_RegisterTask(modeSelect);
    esos_RegisterTask(lcd_manager);

    // Register ESOS Timers
    tmr_handle_LED0 = esos_RegisterTimer(led0, u32t_led0_period);
    tmr_handle_LED1 = esos_RegisterTimer(led1, u32t_led1_period);
    tmr_handle_LED2 = esos_RegisterTimer(led2, u32t_led2_period);
    tmr_handle_LED3 = esos_RegisterTimer(led3, u32t_led3_period);
    tmr_handle_nucleoLED2 = esos_RegisterTimer(nucleoLED2, u32t_nucleoLED2_period);
    //tmr_handle_commandMode = esos_RegisterTimer(commandMode, 100); For some reason this started having flipping issues on SW1 and SW3
    //out of nowhere after more LCD logic was added. Going for direct reads now.
}