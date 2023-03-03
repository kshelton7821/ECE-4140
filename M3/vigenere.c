/*
* Author: Keaton Shelton
* Date: 2/22/2023
*
* Abstract: This program is a implementation of the Vigenere Cipher. 
*    The Vigenere Cipher is a polyalphabetic substitution cipher that uses a series of Caesar Ciphers based on the letters of a keyword. 
*    This program will encrypt and decrypt a message using the Vigenere Cipher. Contains small test program. Some functions are not used in
*    deployment, these do not meet naming conventions.
*
* Revisions:
* 01ks - 2/21/2023 - Initial Creation
* 02ks - 2/22/2023 - Finalization
*/
#include "vigenereH.h"

//Test Vigenere Cipher
void encrypt(char* pch_text, char* pch_key, char* pch_cipher)
{
    //Get Key and Text Lengths, and create iterators
    size_t st_textLength = strlen(pch_text);
    size_t st_keyLength = strlen(pch_key);
    uint16_t i16t_iteratorText, i16t_iteratorKey;
    char ch_tempKey[st_textLength];

    //Create key size same as text size
    for(i16t_iteratorKey = 0, i16t_iteratorText = 0; i16t_iteratorText < st_textLength; ++i16t_iteratorText, ++i16t_iteratorKey)
    {
        //Reset the key iterator if it reaches the end of the key
        if(i16t_iteratorKey == st_keyLength)
        {
            i16t_iteratorKey = 0;
        }
        ch_tempKey[i16t_iteratorText] = pch_key[i16t_iteratorKey];
    }
    //Add the null terminator at end of the key
    ch_tempKey[i16t_iteratorText] = '\0';

    //Encrypt the text
    for(i16t_iteratorText = 0; i16t_iteratorText < st_textLength; ++i16t_iteratorText)
    {
        pch_cipher[i16t_iteratorText] = ((pch_text[i16t_iteratorText] + ch_tempKey[i16t_iteratorText]) % 26) + 'A';
    }
    //Add the null terminator at end of the cipher
    pch_cipher[i16t_iteratorText] = '\0';
}
//Deployment of Vigenere Cipher encryption
void encryptBoard(uint8_t* pch_text, char* pch_key, uint16_t* pu16t_keyTracker)
{
    size_t st_keyLength = strlen(pch_key);

    //Reset the key tracker
    if(st_keyLength == *pu16t_keyTracker)
    {
        pu16t_keyTracker = 0;
    }
    //Encrypt the character
    *pch_text = ((*pch_text + pch_key[*pu16t_keyTracker]) % 26) + 'A';
    //Increment the key tracker
    (*pu16t_keyTracker)++;
}
//Decrypt Vigenere Cipher Test
void decrypt(char* text, char* key, char* cipher)
{
    size_t st_cipherLength = strlen(cipher);
    size_t st_keyLength = strlen(key);
    uint16_t i16t_iteratorCipher, i16t_iteratorKey;
    char ch_tempKey[st_cipherLength];

    //Create key size same as text size
    for(i16t_iteratorKey = 0, i16t_iteratorCipher = 0; i16t_iteratorCipher< st_cipherLength; ++i16t_iteratorCipher, ++i16t_iteratorKey)
    {
        //Reset the key iterator if it reaches the end of the key
        if(i16t_iteratorKey == st_keyLength)
        {
            i16t_iteratorKey = 0;
        }
        ch_tempKey[i16t_iteratorCipher] = key[i16t_iteratorKey];
    }
    //Add the null terminator at end of the key
    ch_tempKey[i16t_iteratorCipher] = '\0';

    //Decrypt the text
    for(i16t_iteratorCipher = 0; i16t_iteratorCipher < st_cipherLength; ++i16t_iteratorCipher)
    {
        text[i16t_iteratorCipher] = ((cipher[i16t_iteratorCipher] - ch_tempKey[i16t_iteratorCipher] + 26) % 26) + 'A';
    }
    //Add the null terminator at end of the cipher
    text[i16t_iteratorCipher] = '\0';
}
//Deployment of Vigenere Cipher decryption
void decryptBoard(uint8_t* pch_text, char* pch_key, uint16_t* pu16t_keyTracker)
{
    size_t st_keyLength = strlen(pch_key);

    //Reset the key tracker
    if(st_keyLength == *pu16t_keyTracker)
    {
        pu16t_keyTracker = 0;
    }
    //Decrypt the character
    *pch_text = ((*pch_text - pch_key[*pu16t_keyTracker] + 26) % 26) + 'A';
    //Increment the key tracker
    (*pu16t_keyTracker)++;
}
/*
int main()
{
    char plaintext[100], key[100], ciphertext[100], decyptedText[100];
    printf("Enter the plaintext: ");
    fgets(plaintext, 100, stdin);
    printf("Enter the key: ");
    fgets(key, 100, stdin);

    //Remove the new line character from the end of the string
    plaintext[strcspn(plaintext, "\n")] = 0;
    key[strcspn(key, "\n")] = 0;

    encrypt(plaintext, key, ciphertext);
    printf("The ciphertext is: %s\n", ciphertext);

    decrypt(decyptedText, key, ciphertext);
    printf("The decrypted text is: %s\n", decyptedText);


    return 0;
}
*/