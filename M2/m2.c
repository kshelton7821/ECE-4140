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
*/
//************** I N C L U D E S *****************
#include "embsysS20.h"
#include "circbufferH.h"
#include "vigenereH.h"

#define CB_SIZE 256 //Buffer Size


//************** I N I T I A L I Z A T I O N *****************
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
	// 16Mhz / 4 * 20 / 2 = 40Mhz. RCC_PLLCFGR_PLLP_DIV7 disables the PLLP output through no enable bit and RCC_PLLCFGR_PLLQ_DIV2 disables the PLLQ output through no enable bit.
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


static void button_setup(void)
{
    //Enable the clock for the GPIOC
    rcc_periph_clock_enable(RCC_GPIOC);
    //Setup the button pin as an input
    gpio_mode_setup(B1_GPIO_Port, GPIO_MODE_INPUT, GPIO_PUPD_NONE, B1_Pin);
}

static void led_setup(void)
{
    //Setup the LED pin as an output
    gpio_mode_setup(LED2_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, LED2_Pin);
    //Test Functions
    TURN_ON_LD2();
}

static void usart_setup(void)
{
   /* DO NOT USE INTERRUPTS IN THIS DESIGN */

    // Setup GPIO pins for USART
    
    rcc_periph_clock_enable(RCC_USART2);
    //RX
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
	usart_set_databits(USART2, 9);  // For 8/0/1 mode, 9 data bits, parity one. Parity uses a data bit so in effect 8/0/1
	usart_set_stopbits(USART2, USART_STOPBITS_1);
	usart_set_mode(USART2, USART_MODE_TX_RX);
	usart_set_parity(USART2, USART_PARITY_ODD);
	usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
    usart_enable(USART2);
    //Fix Wierd Bug with sending extra byte on reset
    usart_send_blocking(USART2, '\b');
    usart_send_blocking(USART2, ' ');
}

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
    //Reset TIM2 peripheral
    rcc_periph_reset_pulse(RST_TIM2);
    //Setup Timer2 with no divider, aligned edge, direction up
    timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    //Prescale Clock by 8000 to get 5KHz
    timer_set_prescaler(TIM2, 8000);
    //Set Timer Period
    timer_set_period(TIM2, 255);
    //Start Timer
    timer_enable_counter(TIM2);
	//gpio_mode_setup();
   	//gpio_mode_setup();
   	//gpio_set_output_options();
	
   /* If you go the AF route, then don't figure to configure AF. */
	//gpio_set_af();   

   /* Setup timer parameters. */

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

int main(void)  
{
    // setup software structures to manage hardware
    //Time = 2500/5000 = 0.5s
    uint16_t volatile u16t_period = 2500;
    // setup software structures need for application
    //Variables for Circular Buffer
    uint8_t u8t_buffer[CB_SIZE], u8t_dataOut, u8t_status, u8t_dataIN;
    uint16_t u16t_keyTracker = 0;
    circular_buffer_t volatile cb_buffer;
    bool bl_encrypt = true, bl_decrypt = false;
    char* pch_key = "BOLDFEARLESSCONFIDENT";
    char* pch_encryptMessage = "\nEncypting Mode Active\n";
    char* pch_decryptMessage = "\nDecrypting Mode Active\n";
    // initialize the hardware
    clock_setup();
    button_setup();
    led_setup();
    timer_setup();
    usart_setup(); 

    //Initialize Circular Buffer
    initBuffer(&cb_buffer, u8t_buffer, CB_SIZE);

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
        //Test Timer = 1000/5000 = 0.2s
        u16t_period = 1000;
        timer_set_period(TIM2, u16t_period);
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
        u16t_period = 2500;
        timer_set_period(TIM2, u16t_period);
        bl_encrypt = true;
        bl_decrypt = false;
    }

    // see if timer has expired
    if(timer_get_counter(TIM2) >= u16t_period)
    {
        timer_set_counter(TIM2, 0);
        gpio_toggle(LED2_GPIO_Port, LED2_Pin);
    }

    // see if UART needs us to do anything
	// check RXNE.
	if (usart_get_flag(USART2, USART_ISR_RXNE))
    {
		// Indicate that we got data.
		// Retrieve the data from the peripheral.
        u8t_dataIN = usart_recv(USART2);
        if(isalpha(u8t_dataIN))
        {
            u8t_dataIN = toupper(u8t_dataIN);
            pushBuffer(&cb_buffer, u8t_dataIN);
        }
        //Check for Enter Key
        else if(u8t_dataIN == '\r')
        {
            pushBuffer(&cb_buffer, '\r');
            pushBuffer(&cb_buffer, '\n');
        }
        //Space Key
        else if(u8t_dataIN == ' ')
        {
            pushBuffer(&cb_buffer, ' ');
        }
        //Backspace Key
        else if(u8t_dataIN == '\b')
        {
            pushBuffer(&cb_buffer, '\b');
        }
        else
        {
            pushBuffer(&cb_buffer, u8t_dataIN);
        }
	}
    
    //Vigenere Encryption
    //Pull Data from Circular Buffer
    u8t_status = popBuffer(&cb_buffer, &u8t_dataOut);
    if(u8t_status == 0 && isalpha(u8t_dataOut) && bl_encrypt == true)
    {
        encryptBoard(&u8t_dataOut, pch_key, &u16t_keyTracker);
    }
    else if(u8t_status == 0 && isalpha(u8t_dataOut) && bl_encrypt == false)
    {
        decryptBoard(&u8t_dataOut, pch_key, &u16t_keyTracker);
    }
    
	/* Check TXE */
    if (usart_get_flag(USART2, USART_ISR_TXE) && u8t_status == 0)
    {
    //Put data into the transmit register. 
    usart_send(USART2, u8t_dataOut);
    } 
  }
  return 0;    // NEVER EXECUTES
}