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
       asm("nop");
       loops--;
    }
}
 
int main(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(LED2_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, LED2_Pin);
    while(1)
    {
       gpio_toggle(LED2_GPIO_Port, LED2_Pin);
       delay_loop(400000);
    }
}