/**
 * @file convert.c
 * @brief Convertion operations library source.
 * @authors Ismael Coelho Medeiros (14/0083162)
 *
 * This file contains all the function source codes which has the
 * signatures declared on the convert.h file.
 */
#include <stdio.h>
#include <stdint.h>
#include "mem-manager.h"

uint16_t smallEndianToBigEndian2Bytes(uint16_t src) {
    uint16_t aux = src & 0xFF00;
    return (src << 8) | (aux >> 8);
}

uint32_t smallEndianToBigEndian4Bytes(uint32_t src) {
    uint32_t low = smallEndianToBigEndian2Bytes( (uint16_t)( ( src & 0xFFFF0000 ) >> 16 ) );
    uint32_t high = smallEndianToBigEndian2Bytes( (uint16_t)( src & 0x0000FFFF ) );

    return (high << 16) | low;
}

char* utf8ToString(uint8_t* src, uint16_t length)  {

    // Verify how many characters the string has
    int i, count;
    for (i = 0, count = 0; i < length; i++) {
        if (src[i] >> 7 == 0x0) {
            count++;
        } else if (src[i] >> 5 == 0x6) {
            count++;
            // Jump one extra-byte
            i++;
        } else if (src[i] >> 4 == 0xC) {
            count++;
            // Jump two extra-byte
            i = i + 2;
        } else {
            printf("Occured some error on decoding UTF-8 string\n");
        }
    }

    // Allocate the space of memory for the string
    char* string  = (char*) allocate((count + 1) * sizeof(char));

    // Read each byte of the string
    int j;
    for (i = 0, j = 0; i < count && j < length; i++, j++) {
        if (src[i] >> 7 == 0x0) {
            string[i] = (char) src[j];
        } else if (src[i] >> 5 == 0x6) {
            uint8_t x = src[j++];
            uint8_t y = src[j];
            string[i] = (char) ( ( ( x & 0x1F ) << 6 ) | ( y & 0x3F ) );
        } else if (src[i] >> 4 == 0xC) {
            uint8_t x = src[j++];
            uint8_t y = src[j++];
            uint8_t z = src[j];
            string[i] = (char) ( ( ( x & 0xF ) << 12 ) | ( ( y & 0x3F ) << 6 ) | ( z & 0x3F ) );
        } else {
            printf("Occured some error on decoding UTF-8 string\n");
        }
    }

    string[count] = '\0';
    return string;
}