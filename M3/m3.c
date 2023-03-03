/*
Original Author: Dr. J.W Bruce
Modified by: Keaton Shelton
Abstract:
   This is a simple program to use the UART system to send a message to the PC.


Questions:


Revisions:
01ks 2/15/2023: Original
02ks 2/22/2023: Working, needs parity changed to odd and small changes to usart setup
03ks 2/23/2023: Final version with odd parity
04ks 3/1/2023: Enable interrupts for USART2
05ks 3/2/2023: Enable interrupts for TIM2 and logic for setting period
*/
//************** I N C L U D E S *****************
#include "embsysS20.h"
#include "circbufferH.h"
#include "vigenereH.h"

#define CB_SIZE 256 //Buffer Size

//************** G L O B A L S *****************
//Circular Buffers
circular_buffer_t volatile cb_bufferRecieve, cb_bufferSend;
//Buffers
uint8_t u8t_bufferRecieve[CB_SIZE], u8t_bufferSend[CB_SIZE];
//Time period for multiplication and entry
uint16_t u16t_timPeriod = 1000;
//Time period for print to screen
char chArr_timPeriod[4] = {'1','0','0','0'};

//************** I N I T I A L I Z A T I O N *****************
//Clock Setup Function
static void clock_setup(void)
{

    //  setup the RCC and clocks for any needed peripherals
    // USE THE HSI16
	rcc_osc_on(RCC_HSI16);
	
	//Enable the prefetch buffer and set flash wait states to 4
	flash_prefetch_enable();
	flash_set_ws(4);
	flash_dcache_enable();
	flash_icache_enable();
	/* setup for 80MHz main pll  */
	// 16Mhz / 4 * 40 / 2 = 80Mhz. RCC_PLLCFGR_PLLP_DIV7 disables the PLLP output through no enable bit and RCC_PLLCFGR_PLLQ_DIV2 disables the PLLQ output through no enable bit.
	rcc_set_main_pll(RCC_PLLCFGR_PLLSRC_HSI16, PLLM_Val, PLLN_Val, RCC_PLLCFGR_PLLP_DIV7, RCC_PLLCFGR_PLLQ_DIV2, RCC_PLLCFGR_PLLR_DIV2);
	rcc_osc_on(RCC_PLL);
	
    //Enable the clock for the GPIOA peripherals and RCC
    rcc_periph_clock_enable(RCC_GPIOA);
    /* either rcc_wait_for_osc_ready() or do other things */
	rcc_wait_for_osc_ready(RCC_PLL);
    // set the clock source to the PLL
	rcc_set_sysclk_source(RCC_CFGR_SW_PLL);
	rcc_wait_for_sysclk_status(RCC_PLL);
	
	// These three global variables must be set to contain
	// the respective frequencies of the ARM-Cortex busses.
	// The libOpenCM3 library uses these variables in a variety
	// of places to calculate register values to control chip
	// timing.  If you do not set these variables correctly,
	// you will see weird behavior, erroneous behavior, or failures.
	//
	// MAGIC NUMBERS ARE EVIL!!!
    rcc_ahb_frequency = RCC_AHB;
    rcc_apb1_frequency = RCC_APB1;
    rcc_apb2_frequency = RCC_APB2;
}

//Button Setup Function
static void button_setup(void)
{
    //Enable the clock for the GPIOC
    rcc_periph_clock_enable(RCC_GPIOC);
    //Setup the button pin as an input
    gpio_mode_setup(B1_GPIO_Port, GPIO_MODE_INPUT, GPIO_PUPD_NONE, B1_Pin);
}

//LED Setup Function
static void led_setup(void)
{
    //Setup the LED pin as an output
    gpio_mode_setup(LED2_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, LED2_Pin);
    //Test Functions
    TURN_ON_LD2();
}

//USART Setup Function
static void usart_setup(void)
{
   /* DO NOT USE INTERRUPTS IN THIS DESIGN */

    // Setup GPIO pins for USART
    
    rcc_periph_clock_enable(RCC_USART2);
    //RX
    //Enable USART2 Interrupts
    nvic_enable_irq(NVIC_USART2_IRQ);
    //Set Interrupt Priority
    nvic_set_priority(NVIC_USART2_IRQ, 0);
    //GPIO Setup
	gpio_mode_setup(USART2_RX_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, USART2_RX_Pin);
    //TX
   	gpio_mode_setup(USART2_TX_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, USART2_TX_Pin);
   	gpio_set_output_options(USART2_RX_GPIO_Port, GPIO_OTYPE_OD, GPIO_OSPEED_25MHZ, USART2_RX_Pin);
	
    //Setup USART pins as alternate function. 
	gpio_set_af(USART2_RX_GPIO_Port, USART2_AF, USART2_RX_Pin);   // you did set any peripherals using
    gpio_set_af(USART2_RX_GPIO_Port, USART2_AF, USART2_TX_Pin);   // an external pin to be AF, right?
    
    //Fix Wierd Bug with sending extra byte on reset

	// Setup UART parameters.
	usart_set_baudrate(USART2, 57600);
	usart_set_databits(USART2, 8);  // For 8/N/1
	usart_set_stopbits(USART2, USART_STOPBITS_1);
	usart_set_mode(USART2, USART_MODE_TX_RX);
	usart_set_parity(USART2, USART_PARITY_NONE);
	usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
    //Enable Receive Interrupt
    usart_enable_rx_interrupt(USART2);
    usart_enable(USART2);
    //Fix Wierd Bug with sending extra byte on reset
    usart_send_blocking(USART2, '\b');
    usart_send_blocking(USART2, ' ');
}

//Timer Setup Function
static void timer_setup(void)
{
   /* DO NOT USE INTERRUPTS IN THIS DESIGN */

   /* Setup GPIO pins associated with timer functionality */
   // You can maniuplate the pins as GPIO directly on timer
   //   expiration. It may be possible to use an alternate
   //   function pin depending on which pin is connected to
   //   your external hardware.
    //Enable the clock for TIM2
    rcc_periph_clock_enable(RCC_TIM2);
    //Enable the interrupt for TIM2
    nvic_enable_irq(NVIC_TIM2_IRQ);
    //Set Interrupt Priority
    nvic_set_priority(NVIC_TIM2_IRQ, 1);
    //Reset TIM2 peripheral
    rcc_periph_reset_pulse(RST_TIM2);
    //Setup Timer2 with no divider, aligned edge, direction up
    timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    //Prescale Clock by 16000 to get 5KHz
    timer_set_prescaler(TIM2, 16000);
    //Continuous Mode
    timer_continuous_mode(TIM2);
    //Set Timer Period Max 50000 / 5000 = 10s
    timer_set_period(TIM2, 5000);
    //Set Output Compare Value
    timer_set_oc_value(TIM2, TIM_OC1, 5000);
    //Start Timer
    timer_enable_counter(TIM2);
    //Enable Channel 1 Interrupt
    timer_enable_irq(TIM2, TIM_DIER_CC1IE);

}

//************** S U P P O R T   F U N C T I O N S ****************
//Shoutout to Dr. Bruce for this one
static void usart_send_string(char* pch_string)
{
    for (uint32_t u32_i = 0; u32_i < strlen(pch_string); u32_i++)
    {
        if (pch_string[u32_i] == '\n')
        {
            //\r\n for new line
            usart_send_blocking(USART2, '\r');
        }
        usart_send_blocking(USART2, pch_string[u32_i]);
    }
}

//Modified version of usart_send_string for char arrays
static void usart_send_charArr(char ch_Arr[])
{
    for (uint32_t u32_i = 0; u32_i < sizeof(ch_Arr); u32_i++)
    {
        if (ch_Arr[u32_i] == '\n')
        {
            //\r\n for new line
            usart_send_blocking(USART2, '\r');
        }
        usart_send_blocking(USART2, ch_Arr[u32_i]);
    }
}


//************** I N T E R R U P T   S E R V I C E   R O U T I N E S ****************
//TIM2 Interrupt Service Routine
void tim2_isr(void)
{
    if (timer_get_flag(TIM2, TIM_SR_CC1IF))
    {
        //Clear the interrupt flag
        timer_clear_flag(TIM2, TIM_SR_CC1IF);
        //Toggle the LED
        TOGGLE_LD2();
    }
}

//USART2 Interrupt Service Routine
void usart2_isr(void)
{
    uint8_t u8t_dataIN, u8t_dataOUT;
    if ((usart_get_flag(USART2, USART_ISR_RXNE)) && (USART_CR1(USART2) & USART_CR1_RXNEIE) != 0)
    {
		// Indicate that we got data.
		// Retrieve the data from the peripheral.
        u8t_dataIN = usart_recv(USART2);
        if(isalpha(u8t_dataIN))
        {
            u8t_dataIN = toupper(u8t_dataIN);
            pushBuffer(&cb_bufferRecieve, u8t_dataIN);
        }
        //Check for Enter Key
        else if(u8t_dataIN == '\r')
        {
            pushBuffer(&cb_bufferRecieve, '\r');
            pushBuffer(&cb_bufferRecieve, '\n');
        }
        //Space Key
        else if(u8t_dataIN == ' ')
        {
            pushBuffer(&cb_bufferRecieve, ' ');
        }
        //Backspace Key
        else if(u8t_dataIN == '\b')
        {
            pushBuffer(&cb_bufferRecieve, '\b');
        }
        else
        {
            pushBuffer(&cb_bufferRecieve, u8t_dataIN);
        }
	}

    /* Check TXE */
    if (usart_get_flag(USART2, USART_ISR_TXE) && (USART_CR1(USART2) & USART_CR1_TXEIE) != 0)
    {
        popBuffer(&cb_bufferSend, &u8t_dataOUT);
        //Put data into the transmit register. 
        usart_send(USART2, u8t_dataOUT);
        //Disable TXE interrupt
        usart_disable_tx_interrupt(USART2);
    } 
}

int main(void)  
{
    // setup software structures to manage hardware
    // setup software structures need for application
    //Variables for Circular Buffer
    uint8_t u8t_dataOut, u8t_status, u8t_commandTracker = 0, u8t_timArrTracker = 0;
    //Key Tracker
    uint16_t u16t_keyTracker = 0;
    //Various Booleans
    bool bl_encrypt = true, bl_decrypt = false, bl_commandMode = false, bl_commandMessageOut = false;
    //Message Arrays
    char* pch_key = "BOLDFEARLESSCONFIDENT";
    char* pch_encryptMessage = "\nEncypting Mode Active\n";
    char* pch_decryptMessage = "\nDecrypting Mode Active\n";
    char* pch_startMessage = "\nWelcome to Milestone 3, Vigenere Cipher Encryption/Decryption\n";
    char* pch_commandMessage = "\nCommand Mode Intiated, Please Enter L to List Period\nOr Enter S to Set Period\nOr Press ! to Exit Command Mode\n";
    char* pch_commandSetPeriod = "\nCommand Mode Set Period, Please Enter Period in nnnn format\n with (n) being an integer between 0 and 9\n";
    char* pch_commandExit = "\nExiting Command Mode\n";
    char* pch_commandSuccess = "\n Command Mode Success, Exiting Command Mode\nTimer Set To: ";
    char* pch_commandMS = " ms\n";
    char* pch_periodValue = "\nPeriod Value: ";

    // initialize the hardware
    clock_setup();
    button_setup();
    led_setup();
    usart_setup(); 
    timer_setup();

    //Initialize Circular Buffer Recieve
    initBuffer(&cb_bufferRecieve, u8t_bufferRecieve, CB_SIZE);
    //Initialize Circular Buffer Transmit
    initBuffer(&cb_bufferSend, u8t_bufferSend, CB_SIZE);

    //Send Start Message
    usart_send_string(pch_startMessage);
    //Initiale Encrypt Message
    usart_send_string(pch_encryptMessage);

   while(1) 
   {
    //Check if Button is Pressed
    if(IS_B1_PRESSED())
    {
        if(bl_encrypt)
        {
            u16t_keyTracker = 0;
            //Decrypt Message
            usart_send_string(pch_decryptMessage);
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
            usart_send_string(pch_encryptMessage);
        }
        //Test Timer = 2500/5000 = 0.5s
        bl_encrypt = true;
        bl_decrypt = false;
    }

    //Check if in Command Mode
    if(u8t_commandTracker == 3 && bl_commandMessageOut)
    {
        //Send Command Message
        usart_send_string(pch_commandMessage);
        bl_commandMessageOut = false;
    }
 
    //Vigenere Encryption or Command Interpreter
    //Pull Data from Circular Buffer
    u8t_status = popBuffer(&cb_bufferRecieve, &u8t_dataOut);
    if(u8t_status == 0 && isalpha(u8t_dataOut) && bl_encrypt == true && u8t_commandTracker != 3)
    {
        //Do Encryption
        encryptBoard(&u8t_dataOut, pch_key, &u16t_keyTracker);
        pushBuffer(&cb_bufferSend, u8t_dataOut);
        //Reset Command Tracker
        u8t_commandTracker = 0;
        //Command Error
        /*if(bl_commandMode)
        {
            usart_send_string(pch_commandExit);
            bl_commandMode = false;
        }
        */
        //Enable TXE Interrupt
        usart_enable_tx_interrupt(USART2);
    }
    else if(u8t_status == 0 && isalpha(u8t_dataOut) && bl_encrypt == false && u8t_commandTracker != 3)
    {
        //Do Decryption
        decryptBoard(&u8t_dataOut, pch_key, &u16t_keyTracker);
        pushBuffer(&cb_bufferSend, u8t_dataOut);
        //Reset Command Tracker
        u8t_commandTracker = 0;
        //Command Error
        /*if(bl_commandMode)
        {
            usart_send_string(pch_commandExit);
            bl_commandMode = false;
        }
        */
        //Enable TXE Interrupt
        usart_enable_tx_interrupt(USART2);
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
            usart_send_string(pch_commandExit);
            bl_commandMode = false;
        }
        //Enable TXE Interrupt
        usart_enable_tx_interrupt(USART2);
    }
    //Command Character
    else if(u8t_status == 0 && u8t_dataOut == '!')
    {
        pushBuffer(&cb_bufferSend, u8t_dataOut);
        u8t_commandTracker++;
        //Enable TXE Interrupt
        usart_enable_tx_interrupt(USART2);
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
                usart_send_string(pch_commandExit);
                bl_commandMode = false;
            }
        }
    }
    //Print Period Mode
    else if(u8t_status == 0 && u8t_dataOut == 'L' && u8t_commandTracker == 3)
    {
        pushBuffer(&cb_bufferSend, u8t_dataOut);
        //Enable TXE Interrupt
        usart_enable_tx_interrupt(USART2);
        //Reset Command Tracker
        u8t_commandTracker = 0;
        //Reset Command Mode
        bl_commandMode = false;
        //Print Period
        usart_send_string(pch_periodValue);
        usart_send_charArr(chArr_timPeriod);
        usart_send_string(pch_commandMS);
    }
    //Set Period Mode
    else if(u8t_status == 0 && u8t_dataOut == 'S' && u8t_commandTracker == 3)
    {
        pushBuffer(&cb_bufferSend, u8t_dataOut);
        //Enable TXE Interrupt
        usart_enable_tx_interrupt(USART2);
        //Send Period Message
        usart_send_string(pch_commandSetPeriod);
    }
    //Set Period Input
    else if(u8t_status == 0 && isdigit(u8t_dataOut) && u8t_commandTracker == 3)
    {
        pushBuffer(&cb_bufferSend, u8t_dataOut);
        //Get Digits
        chArr_timPeriod[u8t_timArrTracker] = u8t_dataOut;
        //Increment Tracker
        u8t_timArrTracker++;
        //Enable TXE Interrupt
        usart_enable_tx_interrupt(USART2);
        //Set Period
        if(u8t_timArrTracker == 4)
        {
            //Turn Into Unsigned Int
            u16t_timPeriod = atoi(chArr_timPeriod);
            //Scale to 5000Hz Clock Rate
            u16t_timPeriod = u16t_timPeriod * 5;
            //Reset Tracker
            u8t_timArrTracker = 0;
            //Reset Command Tracker
            u8t_commandTracker = 0;
            //Disable Command Mode
            bl_commandMode = false;
            //Set Period and reset counter, this refused to work unless everything
            //was set to the period it needed to be
            timer_set_oc_value(TIM2, TIM_OC1, u16t_timPeriod);
            timer_set_period(TIM2, u16t_timPeriod);
            timer_set_counter(TIM2, 0);
            //Send Success Message
            usart_send_string(pch_commandSuccess);
            usart_send_charArr(chArr_timPeriod);
            usart_send_string(pch_commandMS);
        }
    }
  }
  return 0;    // NEVER EXECUTES
}