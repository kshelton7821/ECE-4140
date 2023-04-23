/*
* Author: Keaton Shelton
* Date: 4/19/2023
* 
* Abstract: This is the header file for the ESOS LCD service.
*
*
*
* Revisions:
* 01ks - 4/19/2023 - Initial version
*/
#ifndef ESOS_STM32L4_EDUB_H
#define ESOS_STM32L4_EDUB_H

//************ I N C L U D E S ************
//#include "ptb.h"


//************ D E F I N E S ************
//Pins
#define EDUB_LCDD4_PIN GPIO1
#define EDUB_LCDD5_PIN GPIO2
#define EDUB_LCDD6_PIN GPIO3
#define EDUB_LCDD7_PIN GPIO4
#define EDUB_LCDRS_PIN GPIO12
#define EDUB_LCDE_PIN GPIO10

//Ports
#define EDUB_LCDD4_PORT GPIOB
#define EDUB_LCDD5_PORT GPIOB
#define EDUB_LCDD6_PORT GPIOB
#define EDUB_LCDD7_PORT GPIOB
#define EDUB_LCDRS_PORT GPIOA
#define EDUB_LCDE_PORT GPIOA

//USE 4Bit
//#define ESOS_USE_LCD_4BIT 

//******************* L C D  R E L A T E D  S T R U C T S *******************
//LCD MODE
enum LCD_MODE {
STANDBY,
EDIT,
REPEAT
};

enum LED_SELECTED {
LED0,
LED1,
LED2,
LED3,
LED4,
};



#endif // ESOS_STM32L4_EDUB_H