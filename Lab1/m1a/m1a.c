/*
Original Author: Dr. J.W Bruce
Abstract:
   This is a simple program to blink an LED on the STM32L4 Discovery Board.

Revisions:
01ks 1-2-2023 Add commments about clock speed and NOP cycle time.
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
#include <libopencm3/cm3/common.h>
 
static void delay_loop(int32_t loops)
{
    while(loops > 0)
    {
      //Per STM32L4 Programming Manual, NOP is 1 cycle P.188
       asm("nop");
       loops--;
    }
}
 
int main(void)
{
   //Per STM32L452RE Data Sheet, Default Clock is 4MHz P.34
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(LED2_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, LED2_Pin);
    while(1)
    {
       gpio_toggle(LED2_GPIO_Port, LED2_Pin);
       delay_loop(400000);
    }
}