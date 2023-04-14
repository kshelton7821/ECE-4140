/*
* Author: Josh White
* Date: 4/11/2023
*
* Abstract: This file contains the function declarations for the ESOS SUI
*
*
*
* Revisions:
* 01jw - 4/11/2023 - Initial version
* 02ks - 4/13/2023 - Cleanup
*/
// Use template provided in generic_hwxxxx files.


#ifndef ESOS_STM32L4_PTB_SUI_H
#define ESOS_STM32L4_PTB_SUI_H

#include "ptb.h"
// *************** D E F I N E S ***************
//LED Info
//User Data 1: LED Port
//User Data 2: LED Pin

//EXAMPLES FOR DECLARING AN ESOS_SUI_LED_HANDLE
//ESOS_SUI_LED_HANDLE ESOS_NUCLEO_LED4 = esos_sui_registerLED(NUCLEO_LED2_Port, NUCLEO_LED2_Pin);
//ESOS_SUI_LED_HANDLE ESOS_EDUB_LED3 = esos_sui_registerLED(EDUB_LED3_PORT, EDUB_LED3_PIN);
//ESOS_SUI_LED_HANDLE ESOS_EDUB_LED2 = esos_sui_registerLED(EDUB_LED2_PORT, EDUB_LED2_PIN);
//ESOS_SUI_LED_HANDLE ESOS_EDUB_LED1 = esos_sui_registerLED(EDUB_LED1_PORT, EDUB_LED1_PIN);
//ESOS_SUI_LED_HANDLE ESOS_EDUB_LED0 = esos_sui_registerLED(EDUB_LED0_PORT, EDUB_LED0_PIN);


//Switch Info
//User Data 1: Switch Port
//User Data 2: Switch Pin

//EXAMPLES FOR DECLARING AN ESOS_SUI_SWITCH_HANDLE
//ESOS_SUI_SWITCH_HANDLE ESOS_NUCLEO_SW1 = esos_sui_registerSwitch(NUCLEO_SW1_Port, NUCLEO_SW1_Pin);



// *************** F U N C T I O N  D E C L A R A T I O N S ***************
void esos_hw_sui_configLED          ( ESOS_SUI_LED_HANDLE h_LED ) ;
void esos_hw_sui_turnLEDOn          ( ESOS_SUI_LED_HANDLE h_LED ) ;
void esos_hw_sui_turnLEDOff         ( ESOS_SUI_LED_HANDLE h_LED ) ;
void esos_hw_sui_toggleLED          ( ESOS_SUI_LED_HANDLE h_LED ) ;
void esos_hw_sui_configSwitch       ( ESOS_SUI_SWITCH_HANDLE h_Switch ) ;
BOOL esos_hw_sui_isSwitchPressed    ( ESOS_SUI_SWITCH_HANDLE h_Switch ) ;
BOOL esos_hw_sui_isSwitchReleased   ( ESOS_SUI_SWITCH_HANDLE h_Switch ) ;




#endif   // ESOS_STM32L4_PTB_SUI_H