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
// Use the templates provided in generic_hwxxxx.
// Use template provided in generic_hwxxxx files.


#ifndef ESOS_STM32L4_PTB_SUI_H
#define ESOS_STM32L4_PTB_SUI_H

#include "ptb.h"


// *************** F U N C T I O N  D E C L A R A T I O N S ***************
void esos_hw_sui_configLED          ( ESOS_SUI_LED_HANDLE h_LED ) ;
void esos_hw_sui_turnLEDOn          ( ESOS_SUI_LED_HANDLE h_LED ) ;
void esos_hw_sui_turnLEDOff         ( ESOS_SUI_LED_HANDLE h_LED ) ;
void esos_hw_sui_toggleLED          ( ESOS_SUI_LED_HANDLE h_LED ) ;
void esos_hw_sui_configSwitch       ( ESOS_SUI_SWITCH_HANDLE h_Switch ) ;
BOOL esos_hw_sui_isSwitchPressed    ( ESOS_SUI_SWITCH_HANDLE h_Switch ) ;
BOOL esos_hw_sui_isSwitchReleased   ( ESOS_SUI_SWITCH_HANDLE h_Switch ) ;




#endif   // ESOS_STM32L4_PTB_SUI_H