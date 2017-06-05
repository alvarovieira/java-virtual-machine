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
#include "mem-manager.h"
#include "file.h"

FILE* openFile(char filename[255], char* mode) {
    /* somente para agilizar os testes */
    FILE* fp = fopen("/Users/victorguedes/Documents/UnB/sb/java-virtual-machine/etc/HelloWorld.class", mode);
    //FILE* fp = fopen(filename, mode);
    if (fp == NULL) {
        printf("An error occurr while trying to open the file\n");
    }
    return fp;
}

uint8_t* read(FILE* fp, int offset, int bytes) {
    uint8_t* content;

    // Alocate with file size
    content = (uint8_t*) allocate(sizeof(uint8_t) * bytes);

    // Read file
    fseek(fp, offset, SEEK_SET);
    fread(content, sizeof(uint8_t), bytes, fp);

    return content;
}

uint8_t readByte(FILE* fp, int offset) {
    uint8_t byte;

    // Read byte
    fseek(fp, offset, SEEK_SET);
    fread(&byte, sizeof(uint8_t), 1, fp);

    return byte;
}

uint16_t readWord(FILE* fp, int offset) {
    uint16_t word;

    // Read word
    fseek(fp, offset, SEEK_SET);
    fread(&word, sizeof(uint16_t), 1, fp);

    return word;
}

uint32_t readDoubleWord(FILE* fp, int offset) {
    uint32_t doubleWord;

    // Read double word
    fseek(fp, offset, SEEK_SET);
    fread(&doubleWord, sizeof(uint32_t), 1, fp);

    return doubleWord;
}

int fileSize(FILE* fp) {
    fseek(fp, 0, SEEK_END);
    return ftell(fp);
}

void closeFile(FILE** fp) {
    fclose((*fp));
    (*fp) = NULL;
}