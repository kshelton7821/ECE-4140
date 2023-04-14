/*
* Author: Josh White
* Date: 4/5/2023
*
* Abstract: This file contains the function defintions for the opmode
*    selection system.
*
*
*
* Revisions:
* 01jw - 4/5/2023 - Initial version
* 02ks - 4/5/2023 - Implement defines in fnst_opmodePriority
*/

#include "opmode.h"


// Updates the opmode struct values
void fnst_opmodeUpdate(st_opmode volatile *pst_opmode, uint16_t u16t_SW1, uint16_t u16t_SW2, uint16_t u16t_SW3, uint16_t u16t_SW4, uint16_t u16t_SW5) {
    // Read the switches via defines in main header file
    pst_opmode->u16t_SW1 = u16t_SW1;
    pst_opmode->u16t_SW2 = u16t_SW2;
    pst_opmode->u16t_SW3 = u16t_SW3;
    pst_opmode->u16t_SW4 = u16t_SW4;
    pst_opmode->u16t_SW5 = u16t_SW5;
}

// Initialize the opmode struct values
void fnst_opmodeInit(st_opmode volatile *pst_opmode) {
    pst_opmode->u16t_SW1 = 0;
    pst_opmode->u16t_SW2 = 0;
    pst_opmode->u16t_SW3 = 0;
    pst_opmode->u16t_SW4 = 0;
    pst_opmode->u16t_SW5 = 0;
}

// Return the highest priority operation.
uint8_t fnst_opmodePriority(st_opmode volatile *pst_opmode) {
    if      (pst_opmode->u16t_SW1 != 0)   return OPMODE_KEYBOARD; // priority via SW1
    else if (pst_opmode->u16t_SW2 != 0)   return OPMODE_RM_NON_ALPHA; // downwards
    else if (pst_opmode->u16t_SW3 != 0)   return OPMODE_TO_UPPER;
    else if (pst_opmode->u16t_SW4 != 0)   return OPMODE_ENCRYPT;
    else if (pst_opmode->u16t_SW5 != 0)   return OPMODE_DECRYPT;
    else                                return OPMODE_ECHO; // default
}