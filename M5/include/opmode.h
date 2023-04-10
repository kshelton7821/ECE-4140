/*
* Author: Josh White
* Date: 4/5/2023
*
* Abstract: This file contains the function header for the defintions for the opmode
*    selection system.
*
*
*
* Revisions:
* 01jw - 4/5/2023 - Initial version
* 02ks - 4/5/2023 - Add fnst_opmodeInit
*/
#ifndef OPMODE_H
#define OPMODE_H

#include "ptb.h"

#define OPMODE_KEYBOARD 1
#define OPMODE_RM_NON_ALPHA 2
#define OPMODE_TO_UPPER 3
#define OPMODE_ENCRYPT 4
#define OPMODE_DECRYPT 5
#define OPMODE_ECHO 6


typedef struct {
    uint8_t u8_SW1;
    uint8_t u8_SW2;
    uint8_t u8_SW3;
    uint8_t u8_SW4;
    uint8_t u8_SW5;
} st_opmode;

void fnst_opmodeUpdate(st_opmode volatile *pst_opmode, uint8_t SW1, uint8_t SW2, uint8_t SW3, uint8_t SW4, uint8_t SW5);
void fnst_opmodeInit(st_opmode volatile *pst_opmode);
uint8_t fnst_opmodePriority(st_opmode volatile *pst_opmode);

#endif