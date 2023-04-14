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
* 03ks - 4/13/2023 - Cleanup
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
    bool b_SW1, b_SW2, b_SW3, b_SW4, b_SW5;
} st_opmode;

void fnst_opmodeUpdate(st_opmode volatile *pst_opmode, bool b_SW1, bool b_SW2, bool b_SW3, bool b_SW4, bool b_SW5);
void fnst_opmodeInit(st_opmode volatile *pst_opmode);
uint8_t fnst_opmodePriority(st_opmode volatile *pst_opmode);

#endif