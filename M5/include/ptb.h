/*
* Author: Keaton Shelton
* Date: 4/3/2023
* 
* Abstract: This file contains the macros needed for EduBase board
*
*
*
* Revisions:
* 01ks - 4/3/2023 - Initial file
* 02ks, 01eb - 4/5/2023 - Finalize
*/
#ifndef PTB_H
#define PTB_H


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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
/* Private defines -----------------------------------------------------------*/
//Bus Defines
#define RCC_AHB 80e6
#define RCC_APB1 80e6
#define RCC_APB2 80e6

//PLL Val Defines
#define PLLM_Val 4 //PLLM Divider Only vals 1-8
#define PLLN_Val 40 //PLLN Multiplier Only vals 8-86

//********************************** N U C L E O **********************************
//LED2
#define NUCLEO_LED2_Pin         GPIO5
#define NUCLEO_LED2_Port        GPIOA
#define NUCLEO_LED2_SETUP()     gpio_mode_setup(NUCLEO_LED2_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, NUCLEO_LED2_Pin)
#define NUCLEO_LED2_ON()        gpio_set(NUCLEO_LED2_Port, NUCLEO_LED2_Pin)
#define NUCLEO_LED2_OFF()       gpio_clear(NUCLEO_LED2_Port, NUCLEO_LED2_Pin)
#define NUCLEO_LED2_TOGGLE()    gpio_toggle(NUCLEO_LED2_Port, NUCLEO_LED2_Pin)
#define NUCLEO_LED2_GET()       gpio_get(NUCLEO_LED2_Port, NUCLEO_LED2_Pin)

//Button B1
#define NUCLEO_BUTTON_PORT      GPIOC
#define NUCLEO_BUTTON_PIN       GPIO13
#define NUCLEO_BUTTON_PORT_RCC  GPIOC
#define NUCLEO_BUTTON_SETUP()   gpio_mode_setup(NUCLEO_BUTTON_PORT,GPIO_MODE_INPUT,GPIO_PUPD_NONE,NUCLEO_BUTTON_PIN)
#define NUCLEO_BUTTON_PUSHED()  !gpio_get(NUCLEO_BUTTON_PORT,NUCLEO_BUTTON_PIN)


//USART Defines
#define USART2_TX_Pin           GPIO2
#define USART2_RX_Pin           GPIO3
#define USART2_TX_GPIO_Port     GPIOA
#define USART2_RX_GPIO_Port     GPIOA
#define USART2_AF               GPIO_AF7

//********************************** E D U B A S E **********************************
//LEDs
#define EDUB_LED0_PORT          GPIOA
#define EDUB_LED0_PIN           GPIO1
#define EDUB_LED1_PORT          GPIOA
#define EDUB_LED1_PIN           GPIO0
#define EDUB_LED2_PORT          GPIOC
#define EDUB_LED2_PIN           GPIO7
#define EDUB_LED3_PORT          GPIOC
#define EDUB_LED3_PIN           GPIO8

//LED Macros
#define EDUB_LED0_SETUP()        gpio_mode_setup(EDUB_LED0_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, EDUB_LED0_PIN)
#define EDUB_LED0_TOGGLE()       gpio_toggle(EDUB_LED0_PORT,EDUB_LED0_PIN)
#define EDUB_LED0_SET()          gpio_set(EDUB_LED0_PORT, EDUB_LED0_PIN)
#define EDUB_LED0_CLEAR()        gpio_clear(EDUB_LED0_PORT, EDUB_LED0_PIN)
#define EDUB_LED0_GETVAL()       gpio_get(EDUB_LED0_PORT, EDUB_LED0_PIN)
#define EDUB_LED1_SETUP()        gpio_mode_setup(EDUB_LED1_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, EDUB_LED1_PIN)
#define EDUB_LED1_TOGGLE()       gpio_toggle(EDUB_LED1_PORT,EDUB_LED1_PIN)
#define EDUB_LED1_SET()          gpio_set(EDUB_LED1_PORT, EDUB_LED1_PIN)
#define EDUB_LED1_CLEAR()        gpio_clear(EDUB_LED1_PORT, EDUB_LED1_PIN)
#define EDUB_LED1_GETVAL()       gpio_get(EDUB_LED1_PORT, EDUB_LED1_PIN)
#define EDUB_LED2_SETUP()        gpio_mode_setup(EDUB_LED2_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, EDUB_LED2_PIN)
#define EDUB_LED2_TOGGLE()       gpio_toggle(EDUB_LED2_PORT,EDUB_LED2_PIN)
#define EDUB_LED2_SET()          gpio_set(EDUB_LED2_PORT, EDUB_LED2_PIN)
#define EDUB_LED2_CLEAR()        gpio_clear(EDUB_LED2_PORT, EDUB_LED2_PIN)
#define EDUB_LED2_GETVAL()       gpio_get(EDUB_LED2_PORT, EDUB_LED2_PIN)
#define EDUB_LED3_SETUP()        gpio_mode_setup(EDUB_LED3_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, EDUB_LED3_PIN)
#define EDUB_LED3_TOGGLE()       gpio_toggle(EDUB_LED3_PORT,EDUB_LED3_PIN)
#define EDUB_LED3_SET()          gpio_set(EDUB_LED3_PORT, EDUB_LED3_PIN)
#define EDUB_LED3_CLEAR()        gpio_clear(EDUB_LED3_PORT, EDUB_LED3_PIN)

//Button Defines
#define EDUB_SW2_PORT           GPIOB
#define EDUB_SW2_PIN            GPIO11
#define EDUB_SW3_PORT           GPIOB
#define EDUB_SW3_PIN            GPIO10
#define EDUB_SW4_PORT           GPIOB
#define EDUB_SW4_PIN            GPIO9
#define EDUB_SW5_PORT           GPIOB
#define EDUB_SW5_PIN            GPIO8

//Button Setups
#define EDUB_SW2_SETUP()        gpio_mode_setup(EDUB_SW2_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE, EDUB_SW2_PIN)
#define EDUB_SW3_SETUP()        gpio_mode_setup(EDUB_SW3_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE, EDUB_SW3_PIN)
#define EDUB_SW4_SETUP()        gpio_mode_setup(EDUB_SW4_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE, EDUB_SW4_PIN)
#define EDUB_SW5_SETUP()        gpio_mode_setup(EDUB_SW5_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE, EDUB_SW5_PIN)

//Button Macros
#define EDUB_SW2_ENABLE()      gpio_mode_setup(EDUB_SW2_PORT,GPIO_MODE_INPUT,GPIO_PUPD_NONE,EDUB_SW2_PIN)
#define EDUB_SW2_PUSHED()      gpio_get(EDUB_SW2_PORT,EDUB_SW2_PIN)
#define EDUB_SW3_ENABLE()      gpio_mode_setup(EDUB_SW3_PORT,GPIO_MODE_INPUT,GPIO_PUPD_NONE,EDUB_SW3_PIN)
#define EDUB_SW3_PUSHED()      gpio_get(EDUB_SW3_PORT,EDUB_SW3_PIN)
#define EDUB_SW4_ENABLE()      gpio_mode_setup(EDUB_SW4_PORT,GPIO_MODE_INPUT,GPIO_PUPD_NONE,EDUB_SW4_PIN)
#define EDUB_SW4_PUSHED()      gpio_get(EDUB_SW4_PORT,EDUB_SW4_PIN)
#define EDUB_SW5_ENABLE()      gpio_mode_setup(EDUB_SW5_PORT,GPIO_MODE_INPUT,GPIO_PUPD_NONE,EDUB_SW5_PIN)
#define EDUB_SW5_PUSHED()      gpio_get(EDUB_SW5_PORT,EDUB_SW5_PIN)

//Keypad Defines
#define EDUB_KEYPAD_ROW0_PORT   GPIOB
#define EDUB_KEYPAD_ROW0_PIN    GPIO8
#define EDUB_KEYPAD_ROW1_PORT   GPIOB
#define EDUB_KEYPAD_ROW1_PIN    GPIO9
#define EDUB_KEYPAD_ROW2_PORT   GPIOB
#define EDUB_KEYPAD_ROW2_PIN    GPIO10
#define EDUB_KEYPAD_ROW3_PORT   GPIOB
#define EDUB_KEYPAD_ROW3_PIN    GPIO11
#define EDUB_KEYPAD_COL0_PORT   GPIOB
#define EDUB_KEYPAD_COL0_PIN    GPIO1
#define EDUB_KEYPAD_COL1_PORT   GPIOB
#define EDUB_KEYPAD_COL1_PIN    GPIO2
#define EDUB_KEYPAD_COL2_PORT   GPIOB
#define EDUB_KEYPAD_COL2_PIN    GPIO3
#define EDUB_KEYPAD_COL3_PORT   GPIOB
#define EDUB_KEYPAD_COL3_PIN    GPIO4

//Keypad Macros
//Keypad Init
#define EDUB_KEYPAD_ROW0_SETUP()   gpio_mode_setup(EDUB_KEYPAD_ROW0_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, EDUB_KEYPAD_ROW0_PIN)
#define EDUB_KEYPAD_ROW1_SETUP()   gpio_mode_setup(EDUB_KEYPAD_ROW1_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, EDUB_KEYPAD_ROW1_PIN)
#define EDUB_KEYPAD_ROW2_SETUP()   gpio_mode_setup(EDUB_KEYPAD_ROW2_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, EDUB_KEYPAD_ROW2_PIN)
#define EDUB_KEYPAD_ROW3_SETUP()   gpio_mode_setup(EDUB_KEYPAD_ROW3_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, EDUB_KEYPAD_ROW3_PIN)
#define EDUB_KEYPAD_COL0_SETUP()   gpio_mode_setup(EDUB_KEYPAD_COL0_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN, EDUB_KEYPAD_COL0_PIN)
#define EDUB_KEYPAD_COL1_SETUP()   gpio_mode_setup(EDUB_KEYPAD_COL1_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN, EDUB_KEYPAD_COL1_PIN)
#define EDUB_KEYPAD_COL2_SETUP()   gpio_mode_setup(EDUB_KEYPAD_COL2_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN, EDUB_KEYPAD_COL2_PIN)
#define EDUB_KEYPAD_COL3_SETUP()   gpio_mode_setup(EDUB_KEYPAD_COL3_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN, EDUB_KEYPAD_COL3_PIN)
//Keypad Marcros
#define EDUB_KEYPAD_COL0_SET()     gpio_set(EDUB_KEYPAD_COL0_PORT, EDUB_KEYPAD_COL0_PIN)
#define EDUB_KEYPAD_COL0_CLEAR()   gpio_clear(EDUB_KEYPAD_COL0_PORT, EDUB_KEYPAD_COL0_PIN)
#define EDUB_KEYPAD_COL1_SET()     gpio_set(EDUB_KEYPAD_COL1_PORT, EDUB_KEYPAD_COL1_PIN)
#define EDUB_KEYPAD_COL1_CLEAR()   gpio_clear(EDUB_KEYPAD_COL1_PORT, EDUB_KEYPAD_COL1_PIN)
#define EDUB_KEYPAD_COL2_SET()     gpio_set(EDUB_KEYPAD_COL2_PORT, EDUB_KEYPAD_COL2_PIN)
#define EDUB_KEYPAD_COL2_CLEAR()   gpio_clear(EDUB_KEYPAD_COL2_PORT, EDUB_KEYPAD_COL2_PIN)
#define EDUB_KEYPAD_COL3_SET()     gpio_set(EDUB_KEYPAD_COL3_PORT, EDUB_KEYPAD_COL3_PIN)
#define EDUB_KEYPAD_COL3_CLEAR()   gpio_clear(EDUB_KEYPAD_COL3_PORT, EDUB_KEYPAD_COL3_PIN)
#define EDUB_KEY0_GETVAL()         gpio_get(EDUB_KEYPAD_ROW3_PORT, EDUB_KEYPAD_ROW3_PIN)
#define EDUB_KEY1_GETVAL()         gpio_get(EDUB_KEYPAD_ROW0_PORT, EDUB_KEYPAD_ROW0_PIN)
#define EDUB_KEY2_GETVAL()         gpio_get(EDUB_KEYPAD_ROW0_PORT, EDUB_KEYPAD_ROW0_PIN)
#define EDUB_KEY3_GETVAL()         gpio_get(EDUB_KEYPAD_ROW0_PORT, EDUB_KEYPAD_ROW0_PIN)
#define EDUB_KEY4_GETVAL()         gpio_get(EDUB_KEYPAD_ROW1_PORT, EDUB_KEYPAD_ROW1_PIN)
#define EDUB_KEY5_GETVAL()         gpio_get(EDUB_KEYPAD_ROW1_PORT, EDUB_KEYPAD_ROW1_PIN)
#define EDUB_KEY6_GETVAL()         gpio_get(EDUB_KEYPAD_ROW1_PORT, EDUB_KEYPAD_ROW1_PIN)
#define EDUB_KEY7_GETVAL()         gpio_get(EDUB_KEYPAD_ROW2_PORT, EDUB_KEYPAD_ROW2_PIN)
#define EDUB_KEY8_GETVAL()         gpio_get(EDUB_KEYPAD_ROW2_PORT, EDUB_KEYPAD_ROW2_PIN)
#define EDUB_KEY9_GETVAL()         gpio_get(EDUB_KEYPAD_ROW2_PORT, EDUB_KEYPAD_ROW2_PIN)
#define EDUB_KEYA_GETVAL()         gpio_get(EDUB_KEYPAD_ROW0_PORT, EDUB_KEYPAD_ROW0_PIN)
#define EDUB_KEYB_GETVAL()         gpio_get(EDUB_KEYPAD_ROW1_PORT, EDUB_KEYPAD_ROW1_PIN)
#define EDUB_KEYC_GETVAL()         gpio_get(EDUB_KEYPAD_ROW2_PORT, EDUB_KEYPAD_ROW2_PIN)
#define EDUB_KEYD_GETVAL()         gpio_get(EDUB_KEYPAD_ROW3_PORT, EDUB_KEYPAD_ROW3_PIN)
#define EDUB_KEYSTAR_GETVAL()      gpio_get(EDUB_KEYPAD_ROW3_PORT, EDUB_KEYPAD_ROW3_PIN)
#define EDUB_KEYPOUND_GETVAL()     gpio_get(EDUB_KEYPAD_ROW3_PORT, EDUB_KEYPAD_ROW3_PIN)


#endif /* PTB_H */