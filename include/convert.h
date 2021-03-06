/**
 * @file convert.h
 * @brief Convertion operations library header.
 * @authors Ismael Coelho Medeiros (14/0083162)
 *
 * @todo Description
 */

#ifndef _CONVERT_H
#define _CONVERT_H

#include <stdint.h>

/**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
uint16_t smallEndianToBigEndian2Bytes(uint16_t src);

/**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
uint32_t smallEndianToBigEndian4Bytes(uint32_t src);

/**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
char* utf8ToString(uint8_t* src, uint16_t length);

#endif //_CONVERT_H