/*
Original Author: Dr. J.W Bruce
Modified by: Keaton Shelton
Abstract:
   This is a simple program to blink an LED on the STM32L4 Discovery Board.


Questions:
1. What is the period of the LED blink? How do we know?
Ans: The period is 1 second. We know this for sure because we measured it with an Analog Discovery 2 Oscilloscope.
   We were able to then predict the period using the classic equation of Time = IC / Freq. However we did have to modify this equation
   to get accurate results. If plugging in for IC we get 400000 cycles and for Freq we get 4MHz. This gives us 100ms. However, we know that the
   true period is 1 second. With this in mind we solved for Time(1s) = IC(400000) / Freq(4Mhz)*x. This gives us x = 0.1. Or more accurately 1/10.
   Essentially reducing the frequency by a factor of 10. This is why we had to modify the equation to get accurate results.

2. What is the frequency of the main system clock? How do we know? How could we physically verify that?
Ans: The frequency of the main system clock is 4MHz. We know this because the startup clock speed is stated on P.34 of the STM32L452RE Data Sheet. 
   We could verify this by measuring the frequency of the clock with an Analog Discovery 2 Oscilloscope.

3. Examine the listing17 file (m1a.lst) created when m1a.c is compiled. Explain how to
find the exact period of the blink from the listing file contents before you every flash the
program to hardware and run it.
Ans: We can see in the .lst file that the delay cycle is loaded as a word. This word is our delay interval or cucle count.
   We can then calculate our period by using our modified equation of Time(x) = IC(400000) / Freq(4Mhz)*(1/10). With x = 1s.

4. Now, explain how to change the value in delay_loop() to get a LED flash period of exactly 1/7 second. Make the change and verify your effort.
Ans: We know that a delay of 400000 cycles is 1 second. We want 1/7 of a second so we need to divide 400000 by 7. This gives us 57143 cycles.
   We can see this in the .lst file. Using our modified equation of Time(x) = IC(57143) / Freq(4Mhz)*(1/10). With x = 0.142858 seconds.
   This was then verified by measuring the period with an Analog Discovery 2 Oscilloscope.

Revisions:
01ks 2-2-2023 Add commments about clock speed and NOP cycle time.
02ks 2-6-2023 Change Period to 1/7 of a second and add values.
03ks 2-13-2023 Add comments about delay_loop() and change period to 1/7 of a second.
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
   //Enable GPIOA Clock
    rcc_periph_clock_enable(RCC_GPIOA);
    //Setup Ports for LED2
    gpio_mode_setup(LED2_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, LED2_Pin);
    while(1)
    {
      //Toggle GPIOA5
       gpio_toggle(LED2_GPIO_Port, LED2_Pin);
       //Original Value = 400000
       //Original Period = 1s, 1/7 of a second = 57143
       delay_loop(57143);
    }
}