/**
 * @file convert.c
 * @brief Convertion operations library source.
 * @authors Ismael Coelho Medeiros (14/0083162)
 *
 * This file contains all the function source codes which has the
 * signatures declared on the convert.h file.
 */
#include "stdint.h"

uint8_t smallEndianToBigEndian1Byte(uint8_t src) {
    uint8_t aux = src & 0xF0;
    return (src << 4) | (aux >> 4);
}

uint16_t smallEndianToBigEndian2Bytes(uint16_t src) {
    uint16_t aux = src & 0xFF00;
    return (src << 8) | (aux >> 8);
}

uint32_t smallEndianToBigEndian4Bytes(uint32_t src) {
    uint8_t aux = src & 0xFFFF0000;
    return (src << 16) | (aux >> 16);
}