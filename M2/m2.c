/*
Original Author: Dr. J.W Bruce
Modified by: Keaton Shelton
Abstract:
   This is a simple program to use the UART system to send a message to the PC.


Questions:


Revisions:
01ks 2-15-2023: Original
*/
//************** I N C L U D E S *****************
#include "embsysS20.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

//************** G L O B A L S *****************


//********* I N I T I A L I Z A T I O N *****************
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
    rcc_ahb_frequency = 40e6;
    rcc_apb1_frequency = 40e6;
    rcc_apb2_frequency = 40e6;
}


static void button_setup(void)
{
    //Enable the clock for the GPIOC port
    rcc_periph_clock_enable(RCC_GPIOC);
    //Setup the button pin as an input
    gpio_mode_setup(B1_GPIO_Port, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, B1_Pin);
}

static void led_setup(void)
{
   	/* Enable clocks for the ports we need */
	rcc_periph_clock_enable(RCC_GPIOA);
    //Setup the LED pin as an output
    gpio_mode_setup(LED2_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, LED2_Pin);
}
// YOU NEED TO FINISH EACH STATEMENT BELOW, AND POSSIBLY
// ADD ADDITIIONAL STATEMENTS.
//
// YOU MUST PROVIDE ADEQUATE COMMENTS FOR EACH STATEMENT AND
// USE THE LIBOPENCM3 HAL DEFINES FOR ANY MAGIC NUMBERS
// TO MAKE THE CODE MORE READABLE

int main(void)  {
   // setup software structures to manage hardware
   
   // setup software structures need for application
   
   // initialize the hardware
   clock_setup();
   button_setup();
   led_setup();
   //usart_setup(); 
   //timer_setup();

   // turn on everything (IRQs, etc.)

  while(1) {
    //Test Button and LED Macros
    if(IS_B1_PRESSED())
    {
        TURN_ON_LD2();
    }
    else
    {
        TURN_OFF_LD2();
    }


    // see if TIMER has expired. If so, toggle LED.
    
    //    YOUR TIMER CHECK AND PROCESSING CODE GOES HERE!!

    // see if UART needs us to do anything
	/* check RXNE. */
    /*
	if (?) 
	{
		// DO THE MINIMUM WORK TO MAKE THE UART HAPPY
	}
    */
	/* Check TXE */
    /*
	if (?) 
	{
		// DO THE MINIMUM WORK TO MAKE THE UART HAPPY
	}
    */
    // read and main() hardware and update hardware data structures
    
    // based on the newly updated hardware structures,
    //    "clock" any application FSMs and
    //    update application data structures
    
    // apply new states from data structures to hardware.
        
    // tidy up and prepare whatever possible for next iteration
    //    through while() loop
    
    // OPTIONAL:  setup any time delay mechanism to have while()
    //    loop iterations run at specified times.
    
  }
  return 0;    // NEVER EXECUTES
} 