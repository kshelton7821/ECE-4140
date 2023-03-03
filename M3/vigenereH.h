#ifndef __vigenereH_H
#define __vigenereH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void encrypt(char* text, char* key, char* cipher);
void encryptBoard(uint8_t* pch_text, char* pch_key, uint16_t* pu8t_keyTracker);
void decrypt(char* text, char* key, char* cipher);
void decryptBoard(uint8_t* pch_text, char* pch_key, uint16_t* pu8t_keyTracker);


#endif