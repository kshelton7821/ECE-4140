## Quick Notes
To edit LED Period use SW4 + D
## Additional Comments
- //******************** t7_app.c**********************//

- //******************** I N C L U D E S ***************************************
- /*this has all teh necessary files that are needed in order to make the file work correctly */ 
- /* these files are :
- #include "ptb.h"
- #include "vigenereH.h"
- #include "circbufferH.h"
- #include "opmode.h"
- #include "keypad.h"
- #include "esos_stm32l4_ptb_sui.h"
- #include "esos_stm32l4_edub.h"*/

- //******************** G L O B A L S *****************************************
- // #define CB_SIZE 256: the size that is needed for this file is 256 bits and this is to ensure that there is plenty of spaces for the circular buffer eto function properly
- //circular_buffer_t volatile cb_recieve, cb_send :the circular buffer will recive the size and the will send the size
- // uint8_t u8tArr_cipherArr[16], u8tArr_decipherArr[16], u8tArr_inputPeriodLCD[4]: the arrrays are usend to cipher, decipher and to input the period length that are needed for this program to work efficeintly
- // uint16_t volatile u16t_keyTracker:we need to use a keytracker to keep up with wher e we are at in the cipher that way when we encipher na ddecipher it will be in the correct spot for the circular buffer
- //char *pch_key = "BOLDFEARLESSCONFIDENT":this the key that will be used to decipher and encipher the text that will be entered in
- //char *pch_startMessage = "\nWelcome to Milestone 7, Vigenere Cipher and Other Functions: this is the message that will come along the screen to tell the user that it is ready for them to input values
- // uint32_t volatile u32t_led0_period = 1000: the full periods will all be set the same to ensure that all of the leds will blink synchronously
- // uint32_t volatile u32t_led0_period_half = 500: the half periods will set all the leds to be 500 ms to ensure that the period is exactly half for all of the periods
- // uint32_t volatile u32t_lcd_led0_period = 1000: the periods for the leds will be set to be equivalent to one another
- //  will keep track of the of the commands(uint8_t volatile u8t_commandCounter = 0;), the array tracker(uint8_t volatile u8t_arrTracker = 0;), the period setter (uint8_t volatile u8tArr_periodSet[4] = {0, 0, 0, 0};) and the tracker for the LCD period(uint8_t volatile u8t_periodSetLCDTracker = 0;)
- // char volatile u8tArr_showPeriod[4]: will be an array to show the period and set it to the correct spaces on the LCD screen
- // bool volatile b_encrypt = false : this is to initialize the conditions
- // bool volatile b_decrypt = false :this is to initialize the conditions
- // bool volatile b_toUpper = false : this is to initialize the conditions
- // bool volatile b_rmNonAlpha = false = false : this is to initialize the conditions
- // bool volatile b_echo  = false : this is to initialize the conditions
- // bool volatile b_commandMode = false : this is to initialize the conditions
- // bool volatile b_commandSetPeriod = false: this is to initialize the conditions
- // bool volatile b_commandListPeriod = false: this is to initialize the conditions
- // Encryption State / Other Mode Bools.
- // Booleans for Running LED's at half spee
- //Booleans for editing period through LCD panel
- // Operating Mode
- //LCD modes
- // Selecting the LCD

- //******************** E S O S  H A N D L E S **********************//
- // includes all the timer handlers for all the differnet leds  and the switches these include: ESOS_TMR_HANDLE tmr_handle_LED0, tmr_handle_LED1, tmr_handle_LED2, tmr_handle_LED3, tmr_handle_nucleoLED2, tmr_handle_commandMode;ESOS_SUI_LED_HANDLE h_LED0, h_LED1, h_LED2, h_LED3, h_LED4; ESOS_SUI_SWITCH_HANDLE h_SW1, h_SW2, h_SW3, h_SW4, h_SW5;

- //******************** E S O S  D E F I N E S *********************************
- // defines all the leds to be able to program them to teh NUCLEO bored correctly

- // defines all teh switches for the program to be able to utlize them on teh NUCLEO bored

- //******************** F U N C T I O N S **************************************
- // void selectLED(enum LED_SELECTED *LD_STATE, char tempKey): thsi will help select teh correct led for the fucntion to use these range from LED0-LED3

- //void initDisplay(void) : this will update the LCD to display the period by putting the variables in teh correect locations on the LCD
- //esos_lcd44780_clearScreen(); thsi will clear the LCD screen
- //sprintf(chArr_tempPeriodOut1, "%lu", u32t_led0_period); will convert period to a string then print this out on the LCD screen
- //void leftShifter(uint8_t *u8t_array, uint8_t u8t_in, size_t size): this will shift the array to the left and an the inputs nad the size

- //******************** E S O S  C H I L D  T A S K S **************************
- //ESOS_CHILD_TASK(interpretter, uint8_t u8t_dataIN): Command Interpretter Task 
- //static uint8_t u8t_led; ESOS_TASK_BEGIN(); will check for a command and list what the period is for the LEDS
- //if (u8t_dataIN == 'L' && u8t_commandCounter == 0) this will increment the command counter
- //else if (u8t_commandCounter == 1 && b_commandListPeriod && isdigit(u8t_dataIN)): when the command counter is equal to 1 then it will go through the period will be shown for whatever number is entered
- //else if (u8t_dataIN == 'S' && u8t_commandCounter == 0): this will increment the counter 
- //else if (u8t_commandCounter == 1 && b_commandSetPeriod && isdigit(u8t_dataIN)): check for the LED number and select the led depending on which one is chosen this will be done as the command counter is incremented until it is equal to 4
- // else the Command counter will be equal to zero and reset the variables and will send out an error message
- // ESOS_CHILD_TASK(removeNonAlpha, uint8_t u8t_dataIN): will remove all non alphabetized characters and check and see if it is an alpha letter
- // ESOS_CHILD_TASK(toUpperFunc, uint8_t u8t_dataIN): will chnage the ltter from lowercase to upper case
- // ESOS_CHILD_TASK(encryptUINT, uint8_t u8t_dataIN), ESOS_CHILD_TASK(decryptUINT, uint8_t u8t_dataIN): will encrypt the data that is coming in and also decript the data and user the decipher array to get the correct output from teh circular buffer
- //******************** E S O S  T A S K S *************************************
- //ESOS_USER_TASK(lcd_manager): this is the task that will affect the LCD functionality these includes the period output, setting the period, the temporary period
- //ESOS_TASK_BEGIN(): this will wait until there is a keypad entry and select the led for the differnet the led states which are A, B it will then check and see which led has been selected and display the correct information pertaining to this led
- //else if (LCD_STATE == EDIT): wait for it to be in a particular state until it debounces or settles in the correct state
- //if led state is 0: then get keys from keypad entry, wait for the debounce, get the number and check to see if the number is correct after this shift the array
- // if no entry then earase the display
- // write characters to sreen and print the set period on the LCD
- //will write ms behind the period to show hwo many seconds
- // ESOS_TASK_WAIT_TICKS(300);wait the 300ms
- // wait on the out comm, send the string "LED0 Editing Mode! All other functionality Disabled", now AVAILABLE_OUT_COMM, nwo wait another 500ms
- //u32t_tempPeriod = 0; set the new period and add teh values
- //esos_ChangeTimerPeriod(tmr_handle_LED0, u32t_led0_period); set the timer and set the LCD state back to standby
- //else the state will be LED==1 and this will repeat for LED==2, LED ==3, LED ==4: now you will get the keys, wait on keypad entry, shift left after recieving the entry and checking if it is a number, wiat for 300ms, and wait until the keypad entry
- // else clear the screen and write string (0, 1, "LED1")
- //esos_lcd44780_writeChar(0, 9, u8tArr_periodSetLCD[0]); esos_lcd44780_writeChar(0, 10, u8tArr_periodSetLCD[1]);esos_lcd44780_writeChar(0, 11, u8tArr_periodSetLCD[2]);esos_lcd44780_writeChar(0, 12, u8tArr_periodSetLCD[3]); now set the new periods for each of these
- //esos_lcd44780_writeString(0, 14, "ms"); write the string and after this confim the message
- //ESOS_USER_TASK(sending): after all the loops have been completed the USART will send the data out
- //while (popBuffer(&cb_send, &u8t_dataOut) == 0) : Check if anything is in outbound buffer, // If so it will send the data out
- //ESOS_USER_TASK(recieving):USART Recieving Task
- //ESOS_TASK_BEGIN(); will send the welcome message
- //while (1) will check to see if anything came into teh buffer
- //ESOS_USER_TASK(modeSelect): this will select the mode for the task
- //static uint8_t u8t_dataIn;, static uint8_t u8t_buttons[5] = {0, 0, 0, 0, 0}; inputs for the datain and the buttons are showing the state of the buttons
- //if (!esos_hw_sui_isSwitchPressed(h_SW1)) will be repeated for the 5 sitches and before a button is pressed it will wait on standby
- // and it will reset if no buttons are pressed
- //if (!b_commandMode): check to see if it was previously in command mode
- //for (int i = 0; i < 16; i++): reset and repeat the arrays to spaces
- // set all the booleans that were stated previouslyb_commandMode = true;, b_encrypt = false; ,b_decrypt = false; ,b_toUpper = false; ,b_rmNonAlpha = false; ,b_echo = false;
- //if (popBuffer(&cb_recieve, &u8t_dataIn) == 0) then spawn the child task
- //repeat this for each switch that is pressed
- //after these are all completed we will check for the half speeds of the led0-led4 and set the new periods for eahc of the LEDS
- //else you will return back to the orginal speed for each of the LEDS
- //u32t_lcd_led0_period = u32t_led0_period; you will set the LCD period for each of the LEDS

- //******************** E S O S  T I M E R S ***********************************
- // ESOS_USER_TIMER(led0)- led3 this will toggle toggle each of the LEDS that correspond to the timer
- //ESOS_USER_TIMER(commandMode) command modes for the timers and the swicthes corresponding to them

- //******************** I N I T  F U N C T I O N S *****************************
- //void hw_init(void) : setup for the RCC for buttons and the LEDs
- // define the leds for each of the leds on the board and correspond their ports 
- //NUCELO_LED2.u32_userData1 = NUCLEO_LED2_Port;
- //NUCELO_LED2.u32_userData2 = NUCLEO_LED2_Pin;
- //EDUB_LED3.u32_userData1 = EDUB_LED3_PORT;
- //EDUB_LED3.u32_userData2 = EDUB_LED3_PIN;
- //EDUB_LED2.u32_userData1 = EDUB_LED2_PORT;
- //EDUB_LED2.u32_userData2 = EDUB_LED2_PIN;
- //EDUB_LED1.u32_userData1 = EDUB_LED1_PORT;
- //EDUB_LED1.u32_userData2 = EDUB_LED1_PIN;
- //EDUB_LED0.u32_userData1 = EDUB_LED0_PORT;
- //EDUB_LED0.u32_userData2 = EDUB_LED0_PIN;

- // define the switches for each of the leds on the board and correspond their ports 
- //NUCLEO_SW1.u32_userData1 = NUCLEO_BUTTON_PORT;
- //NUCLEO_SW1.u32_userData2 = NUCLEO_BUTTON_PIN;
- // EDUB_SW2.u32_userData1 = EDUB_SW2_PORT;
- //EDUB_SW2.u32_userData2 = EDUB_SW2_PIN;
- //EDUB_SW3.u32_userData1 = EDUB_SW3_PORT;
- //EDUB_SW3.u32_userData2 = EDUB_SW3_PIN;
- //EDUB_SW4.u32_userData1 = EDUB_SW4_PORT;
- //EDUB_SW4.u32_userData2 = EDUB_SW4_PIN;
- //EDUB_SW5.u32_userData1 = EDUB_SW5_PORT;
- //EDUB_SW5.u32_userData2 = EDUB_SW5_PIN;

- // Register LEDs
- //h_LED0 = esos_sui_registerLED(EDUB_LED0.u32_userData1, EDUB_LED0.u32_userData2);
- // h_LED1 = esos_sui_registerLED(EDUB_LED1.u32_userData1, EDUB_LED1.u32_userData2);
- //h_LED2 = esos_sui_registerLED(EDUB_LED2.u32_userData1, EDUB_LED2.u32_userData2);
- // h_LED3 = esos_sui_registerLED(EDUB_LED3.u32_userData1, EDUB_LED3.u32_userData2);
- // h_LED4 = esos_sui_registerLED(NUCELO_LED2.u32_userData1, NUCELO_LED2.u32_userData2);

- /*// Register Buttons
-     h_SW1 = esos_sui_registerSwitch(NUCLEO_SW1.u32_userData1, NUCLEO_SW1.u32_userData2);
-     h_SW2 = esos_sui_registerSwitch(EDUB_SW2.u32_userData1, EDUB_SW2.u32_userData2);
-     h_SW3 = esos_sui_registerSwitch(EDUB_SW3.u32_userData1, EDUB_SW3.u32_userData2);
-     h_SW4 = esos_sui_registerSwitch(EDUB_SW4.u32_userData1, EDUB_SW4.u32_userData2);
-     h_SW5 = esos_sui_registerSwitch(EDUB_SW5.u32_userData1, EDUB_SW5.u32_userData2);*/

-     /*// Config LEDs
-     esos_hw_sui_configLED(h_LED0);
-     esos_hw_sui_configLED(h_LED1);
-     esos_hw_sui_configLED(h_LED2);
-     esos_hw_sui_configLED(h_LED3);
-     esos_hw_sui_configLED(h_LED4);*/

-    /*// Eduboard Button Setup
-     EDUB_KEYPAD_ROW0_SETUP();
-     EDUB_KEYPAD_ROW1_SETUP();
-     EDUB_KEYPAD_ROW2_SETUP();
-     EDUB_KEYPAD_ROW3_SETUP();
-     EDUB_KEYPAD_COL0_SETUP();
-     EDUB_KEYPAD_COL1_SETUP();
-     EDUB_KEYPAD_COL2_SETUP();
-     EDUB_KEYPAD_COL3_SETUP();*/ 

-     /*Set all Columns Low (possible fix for button / keypad dual reads)
-     EDUB_KEYPAD_COL0_CLEAR();
-     EDUB_KEYPAD_COL1_CLEAR();
-     EDUB_KEYPAD_COL2_CLEAR();
-     EDUB_KEYPAD_COL3_CLEAR();
- */
-    /*Config Buttons
-     esos_hw_sui_configSwitch(h_SW1);
-     esos_hw_sui_configSwitch(h_SW2);
-     esos_hw_sui_configSwitch(h_SW3);
-     esos_hw_sui_configSwitch(h_SW4);
-     esos_hw_sui_configSwitch(h_SW5);*/

-     /*Setup LCD
-     esos_lcd44780_configDisplay();
-     __esos_lcd44780_init();
-     // Turn off cursor
-     esos_lcd44780_setCursorDisplay(false);
-     // Default
-     initDisplay();*/

-    //void user_init(void)
-  // hw_init(); this will initalize the hardware
-  /*Initialize Software Structures
-     initBuffer(&cb_recieve, u8t_bufferRecieve, CB_SIZE);
-     initBuffer(&cb_send, u8t_bufferSend, CB_SIZE);
-     fnst_opmodeInit(&opmode);
- */
- /*Register ESOS Timers
-     tmr_handle_LED0 = esos_RegisterTimer(led0, u32t_led0_period);
-     tmr_handle_LED1 = esos_RegisterTimer(led1, u32t_led1_period);
-     tmr_handle_LED2 = esos_RegisterTimer(led2, u32t_led2_period);
-     tmr_handle_LED3 = esos_RegisterTimer(led3, u32t_led3_period);
-     tmr_handle_nucleoLED2 = esos_RegisterTimer(nucleoLED2, u32t_nucleoLED2_period);*/