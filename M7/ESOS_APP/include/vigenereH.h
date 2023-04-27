/*
* Author: Keaton Shelton
* Date: 2/22/2023
*
* Abstract: This program is the header file for a implementation of the Vigenere Cipher. 
*    The Vigenere Cipher is a polyalphabetic substitution cipher that uses a series of Caesar Ciphers based on the letters of a keyword. 
*    This program will encrypt and decrypt a message using the Vigenere Cipher. Contains small test program. Some functions are not used in
*    deployment, these do not meet naming conventions.
*
* Revisions:
* 01ks - 2/21/2023 - Initial Creation
* 02ks - 2/22/2023 - Finalization
*/
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