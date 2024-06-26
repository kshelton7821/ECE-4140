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
* 02jv - 4/16/2023 - Add Documentation
*/
// Use the templates provided in generic_hwxxxx.



// Includes
#include "esos_stm32l4_ptb_sui.h"


// ESOS SUI Hardware config LED.
// h_LED is the handle to the LED
// ESOS_SUI_LED_HANDLE h_LED is the handle to the LED in ESOS.
// ESOS initializes a single registered LED. This is used in this case to initalize LEDs 0-4.
void esos_hw_sui_configLED ( ESOS_SUI_LED_HANDLE h_LED ) {
    gpio_mode_setup(esos_sui_getLEDUserData1(h_LED), GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, esos_sui_getLEDUserData2(h_LED));
}


// ESOS turns on a single LED. The LED must first be registered and initialized using esos_hw_sui_configLED.
void esos_hw_sui_turnLEDOn ( ESOS_SUI_LED_HANDLE h_LED ) {
    gpio_set(esos_sui_getLEDUserData1(h_LED), esos_sui_getLEDUserData2(h_LED));
}


// ESOS turns off a single LED. The LED must first be registered and initialized using esos_hw_sui_configLED.
void esos_hw_sui_turnLEDOff ( ESOS_SUI_LED_HANDLE h_LED ) {
    gpio_clear(esos_sui_getLEDUserData1(h_LED), esos_sui_getLEDUserData2(h_LED));
}


// ESOS toggles an LED to off/on. The LED must first be registered and initialized using esos_hw_sui_configLED.  
void esos_hw_sui_toggleLED ( ESOS_SUI_LED_HANDLE h_LED ) {
    gpio_toggle(esos_sui_getLEDUserData1(h_LED), esos_sui_getLEDUserData2(h_LED));
}


// ESOS initializes a single registered switch. This is used in this case to initialize SW 1-5.
void esos_hw_sui_configSwitch ( ESOS_SUI_SWITCH_HANDLE h_SWITCH ) {
    gpio_mode_setup(esos_sui_getSwitchUserData1(h_SWITCH), GPIO_MODE_INPUT, GPIO_PUPD_NONE, esos_sui_getSwitchUserData2(h_SWITCH));
}


// ESOS checks the current state of the switch. The switch must first be registered and initialized using esos_hw_sui_configSwitch.
// TRUE if switch is pressed, FALSE if switch is released
BOOL esos_hw_sui_isSwitchPressed ( ESOS_SUI_SWITCH_HANDLE h_SWITCH ) {
    if (gpio_get(esos_sui_getSwitchUserData1(h_SWITCH), esos_sui_getSwitchUserData2(h_SWITCH)))
        return TRUE;
    else
        return FALSE;
}



// ESOS checks the current state of the switch. The switch must first be registered and initialized using esos_hw_sui_configSwitch.
// TRUE if switch is released, FALSE if switch is pressed
BOOL esos_hw_sui_isSwitchReleased ( ESOS_SUI_SWITCH_HANDLE h_SWITCH ) {
    if (gpio_get(esos_sui_getSwitchUserData1(h_SWITCH), esos_sui_getSwitchUserData2(h_SWITCH)))
        return FALSE;
    else
        return TRUE;
}


// EOF
