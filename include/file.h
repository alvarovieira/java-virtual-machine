#ifndef _FILE_H
#define _FILE_H

#include <stdio.h>
#include <stdint.h>

/**
 *
 */
FILE* openFile(char[255], char*);

/**
 *
 */
uint8_t* read(FILE*, int, int);

/**
 *
 */
int fileSize(FILE*);

/**
 *
 */
void closeFile(FILE**);

#endif