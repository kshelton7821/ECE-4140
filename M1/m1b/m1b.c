/*
Original Author: Dr. J.W Bruce
Modified by: Keaton Shelton
Abstract:
   This is a simple program to blink an LED on the STM32L4 Discovery Board.


Questions:
1. As before, examine the listing file produced when you get
your program working. Predict, then measure the LED blink period.
Ans: We can see in the .lst file that the delay cycle is loaded as a word. This word is our delay interval or cucle count.
   We can then calculate our period by using our modified equation of Time(x) = IC(400000) / Freq(80Mhz)*(1/10). With x = 0.05 seconds or 50ms.
   This was then verified by measuring the period with an Analog Discovery 2 Oscilloscope.

Revisions:
01ks 2-7-2023 Finish Main, Setup PLL and GPIO
*/
#ifndef STM32L4
   #define STM32L4
#endif

#include "user_app.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/flash.h>

#include <libopencm3/stm32/timer.h>
static void clock_setup(void)
{
	// USE THE HSI16
	rcc_osc_on(RCC_HSI16);
	
	//Enable the prefetch buffer and set flash wait states to 4
	flash_prefetch_enable();
	flash_set_ws(4);
	flash_dcache_enable();
	flash_icache_enable();
	/* setup for 80MHz main pll  */
	// 16Mhz / 4 * 40 / 2 = 80Mhz
	rcc_set_main_pll(RCC_PLLCFGR_PLLSRC_HSI16, 4, 40, 0, 0, RCC_PLLCFGR_PLLR_DIV2);
	rcc_osc_on(RCC_PLL);
	/* either rcc_wait_for_osc_ready() or do other things */
	rcc_wait_for_osc_ready(RCC_PLL);
	/* Enable clocks for the ports we need */
	rcc_periph_clock_enable(RCC_GPIOA);
   
	rcc_set_sysclk_source(RCC_CFGR_SW_PLL); /* careful with the param here! */
	rcc_wait_for_sysclk_status(RCC_PLL);
	
	// These three global variables must be set to contain
	// the respective frequencies of the ARM-Cortex busses.
	// The libOpenCM3 library uses these variables in a variety
	// of places to calculate register values to control chip
	// timing.  If you do not set these variables correctly,
	// you will see weird behavior, erroneous behavior, or failures.
	//
	// MAGIC NUMBERS ARE EVIL!!!
	rcc_ahb_frequency = 80e6;
	rcc_apb1_frequency = 80e6;
	rcc_apb2_frequency = 80e6;
} 
 
static void delay_loop(int32_t loops)
{
    while(loops > 0)
    {
       asm("nop");
       loops--;
    }
}
 
int main(void)
{
	// INSERT YOUR MAIN CODE HERE   
	//Clock Setup
	clock_setup();
	// Setup GPIO pins for the LED2 flashing
	gpio_mode_setup(LED2_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, LED2_Pin);
	//Main Loop
	while(1) 
	{
		//Toggle GPIOA5
		gpio_toggle(LED2_GPIO_Port, LED2_Pin);
		//Delay by 400000 cycles
		delay_loop(400000);
	}

    
}