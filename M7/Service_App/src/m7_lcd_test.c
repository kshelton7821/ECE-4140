//*** I N C L U D E S *********************************************************/
#include "ptb.h"

// HARDWARE INDEPENDENCE LIBS:
#include "esos_stm32l4_edub.h"

#ifdef __linux
#include "esos_pc.h"
#include "esos_pc_stdio.h"
#else
#include "esos_stm32l4.h"
#include "esos_stm32l4_rs232.h"
#endif


//******* S U P P O R T    F U N C T I O N    P R O T O T Y P E S ************
void __user_init_hw(void);

//*** G L O B A L S ***********************************************************/
#define  LD2_PERIOD     0
#define  LED0_PERIOD    1
#define  LED1_PERIOD    2
#define  LED2_PERIOD    3
#define  LED3_PERIOD    4
#define  NUM_LEDS       5
uint32_t au32_LEDPeriods_Ticks[NUM_LEDS] = {1000,1000,1000,1000,1000};
ESOS_SUI_LED_HANDLE LD2;
ESOS_SUI_LED_HANDLE h_LED0;
ESOS_SUI_LED_HANDLE h_LED1;
ESOS_SUI_LED_HANDLE h_LED2;
ESOS_SUI_LED_HANDLE h_LED3;

ESOS_USER_TASK(test_thread){//tests all ESOS LCD functions
    uint8_t ui8t_1string[] = {'T','e','s','t','i','n','g',' ','d','o','n','t'};
    uint8_t ui8t_2string[] = {'w','r','i','t','e','B','u','f','f','e','r',' ',
                             'p','r','i','n','t'};
    char* char_3string  = "Testing";
    char* char_4string  = "writeString";
    char* char_5string  = "Cursor blink";
    char* char_6string  = "No blink";
    char* char_7string  = "Cursor off";
    char* char_8string  = "Does not print";
    char* char_9string  = "Display Visible";

    ESOS_TASK_BEGIN();
    while(TRUE) {
        esos_lcd44780_clearScreen();//testing screen clear
        esos_lcd44780_setCursorDisplay(false);
        ESOS_TASK_WAIT_TICKS(2000);

        esos_lcd44780_writeChar(0, 0, 'c');//tests writeChar with charwrite success
        esos_lcd44780_writeChar(0, 1, 'h');
        esos_lcd44780_writeChar(0, 2, 'a');
        esos_lcd44780_writeChar(0, 3, 'r');
        esos_lcd44780_writeChar(0, 4, 'w');
        esos_lcd44780_writeChar(0, 5, 'r');
        esos_lcd44780_writeChar(0, 6, 'i');
        esos_lcd44780_writeChar(0, 7, 't');
        esos_lcd44780_writeChar(0, 8, 'e');
        esos_lcd44780_writeChar(1, 1, 's');
        esos_lcd44780_writeChar(1, 2, 'u');
        esos_lcd44780_writeChar(1, 3, 'c');
        esos_lcd44780_writeChar(1, 4, 'c');
        esos_lcd44780_writeChar(1, 5, 'e');
        esos_lcd44780_writeChar(1, 6, 's');
        esos_lcd44780_writeChar(1, 7, 's');
        ESOS_TASK_WAIT_TICKS(4000);

        esos_lcd44780_clearScreen();//tests the buffer write
        esos_lcd44780_writeBuffer(0, 2, ui8t_1string, 7);
        esos_lcd44780_writeBuffer(1, 0, ui8t_2string, 11);
        ESOS_TASK_WAIT_TICKS(4000);

        esos_lcd44780_clearScreen();//tests the string writes
        esos_lcd44780_writeString(0, 6, char_3string);
        esos_lcd44780_writeString(1, 4, char_4string);
        ESOS_TASK_WAIT_TICKS(4000);

        esos_lcd44780_clearScreen();//tests cursorDisplay and cursor blink with rotation between cursor blinking, no blink, and no cursor
        esos_lcd44780_setCursorDisplay(true);
        esos_lcd44780_setCursorBlink(true);
        esos_lcd44780_setCursorHome();
        esos_lcd44780_writeString(1, 0, char_5string);
        ESOS_TASK_WAIT_TICKS(4000);
        esos_lcd44780_clearScreen();
        esos_lcd44780_setCursorBlink(false);
        esos_lcd44780_writeString(1, 0, char_6string);
        ESOS_TASK_WAIT_TICKS(4000);
        esos_lcd44780_setCursorDisplay(false);
        esos_lcd44780_writeString(1, 0, char_7string);
        ESOS_TASK_WAIT_TICKS(4000);

        esos_lcd44780_clearScreen();//restarts display to test display setDisplayVisible
        esos_lcd44780_setDisplayVisible(false);
        esos_lcd44780_writeString(0, 0, char_8string);
        ESOS_TASK_WAIT_TICKS(4000);
        esos_lcd44780_setDisplayVisible(true);
        esos_lcd44780_clearScreen();
        esos_lcd44780_writeString(0, 0, char_9string);
        ESOS_TASK_WAIT_TICKS(4000);
    }
    ESOS_TASK_END();
}

/*
Initializes the hardware used in this application
 */
void __user_init_hw(void)
{

  esos_lcd44780_configDisplay();
  __esos_lcd44780_init();
  esos_lcd44780_clearScreen();

  LD2 = esos_sui_registerLED(NUCLEO_LED2_Port,NUCLEO_LED2_Pin);
  h_LED0 = esos_sui_registerLED(EDUB_LED0_PORT, EDUB_LED0_PIN);
  h_LED1 = esos_sui_registerLED(EDUB_LED1_PORT, EDUB_LED1_PIN);
  h_LED2 = esos_sui_registerLED(EDUB_LED2_PORT,EDUB_LED2_PIN);
  h_LED3 = esos_sui_registerLED(EDUB_LED3_PORT, EDUB_LED3_PIN);

  esos_sui_flashLED(LD2, au32_LEDPeriods_Ticks[LD2_PERIOD]);
  esos_sui_flashLED(h_LED0, au32_LEDPeriods_Ticks[LED0_PERIOD]);
  esos_sui_flashLED(h_LED1, au32_LEDPeriods_Ticks[LED1_PERIOD]);
  esos_sui_flashLED(h_LED2, au32_LEDPeriods_Ticks[LED2_PERIOD]);
  esos_sui_flashLED(h_LED3, au32_LEDPeriods_Ticks[LED3_PERIOD]);
}

void user_init(void)
{
  // Initializes hardware
  __user_init_hw();

  // Drive the UART directly to print the HELLO_MSG
  __esos_unsafe_PutString(HELLO_MSG);

  esos_RegisterTask(test_thread);
  __esos_InitSUI();

}
