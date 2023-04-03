/*
 * "Copyright (c) 2023 J. W. Bruce & Keaton Shelton"
 * All rights reserved.
 * (J. W. Bruce, jwbruce_AT_tntech.edu, Tennessee Tech University)
 * (Keaton Shelton, kmshelton42@tntech.edu, Tennessee Tech University)
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the authors appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE "AUTHORS" BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE "AUTHORS"
 * HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE "AUTHORS" SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE "AUTHORS" HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Please maintain this header in its entirety when copying/modifying
 * these files.
 *
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __embsysS20_H
#define __embsysS20_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef STM32L4
    #define STM32L4
#endif

/* Includes ------------------------------------------------------------------*/
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/timer.h>

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>


/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/

//Bus Defines
#define RCC_AHB 80e6
#define RCC_APB1 80e6
#define RCC_APB2 80e6

//LED Defines
#define LED2_Pin GPIO5
#define LED2_GPIO_Port GPIOA

//PLL Val Defines
#define PLLM_Val 4 //PLLM Divider Only vals 1-8
#define PLLN_Val 40 //PLLN Multiplier Only vals 8-86

//Button Defines
//From Nucleo UM1724 Section 6.5
#define B1_Pin GPIO13
#define B1_GPIO_Port GPIOC

//USART Defines
//From STM32L4 Datasheet P.71, AF on P.76
#define USART2_TX_Pin GPIO2
#define USART2_RX_Pin GPIO3
#define USART2_TX_GPIO_Port GPIOA
#define USART2_RX_GPIO_Port GPIOA
#define USART2_AF GPIO_AF7

//Macro Defines --------------------------------------------------------------
//LD2 Defines
#define TURN_ON_LD2() gpio_set(LED2_GPIO_Port, LED2_Pin)
#define TURN_OFF_LD2() gpio_clear(LED2_GPIO_Port, LED2_Pin)
#define TOGGLE_LD2() gpio_toggle(LED2_GPIO_Port, LED2_Pin)
#define IS_LD2_SET() gpio_get(LED2_GPIO_Port, LED2_Pin)
#define IS_LD2_RESET() !gpio_get(LED2_GPIO_Port, LED2_Pin)

//Button Defines
#define IS_B1_PRESSED() !gpio_get(B1_GPIO_Port, B1_Pin)
#define IS_B1_RELEASED() gpio_get(B1_GPIO_Port, B1_Pin)


#ifdef __cplusplus
}
#endif

#endif /* __embsysS20_H */