/**
 * @file file.h
 * @brief File operations library header.
 * @authors Ismael Coelho Medeiros (14/0083162)
 *
 * @todo Description
 */

#ifndef _FILE_H
#define _FILE_H

#include <stdio.h>
#include <stdint.h>

/**
 * @brief Opens some file in a specific mode.
 *
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
FILE* openFile(char filename[255], char* mode);

/**
 * @brief Reads a specific amount of bytes in a specific offset of a file pointer.
 *
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
uint8_t* read(FILE* fp, int offset, int bytes);

/**
 * @brief Returns the size of some file.
 *
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
int fileSize(FILE* fp);

/**
 * @brief Closes a file pointer and removes the pointer reference.
 *
 * @todo Description
 * @todo Parameters
 */
void closeFile(FILE**);

#endif