/**
 * @file file.c
 * @brief File operations library source.
 * @authors Ismael Coelho Medeiros (14/0083162)
 *
 * This file contains all the function source codes which has the
 * signatures declared on the file.h file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "file.h"

FILE* openFile(char filename[255], char* mode) {
    FILE* fp = fopen(filename, mode);
    if (fp == NULL) {
        printf("An error occurr while trying to open the file\n");
    }
    return fp;
}

uint8_t* read(FILE* fp, int offset, int bytes) {
    uint8_t* content;

    // Alocate with file size
    content = (uint8_t*) malloc(sizeof(uint8_t) * bytes);

    // Read file
    fseek(fp, offset, SEEK_SET);
    fread(content, sizeof(uint8_t), bytes, fp);

    return content;
}

int fileSize(FILE* fp) {
    fseek(fp, 0, SEEK_END);
    return ftell(fp);
}

void closeFile(FILE** fp) {
    fclose((*fp));
    (*fp) = NULL;
}