/**
 * @file class.c
 * @brief Classfile operations library source
 * @authors Ismael Coelho Medeiros (14/0083162)
 *
 * This file contains all the function source codes which has the
 * signatures declared on the class.h file.
 */

#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "convert.h"
#include "class.h"

Class* readClassfile(FILE* fp) {
    Class* classRef = (Class*) malloc(sizeof(Class));

    classRef->magic = readU4(fp, 0);
    classRef->minorVersion = smallEndianToBigEndian2Bytes(readU2(fp, 4));
    classRef->majorVersion = smallEndianToBigEndian2Bytes(readU2(fp, 6));

    return classRef;
}

u1 readU1(FILE* fp, int offset) {
    return readByte(fp, offset);
}

u2 readU2(FILE* fp, int offset) {
    return readWord(fp, offset);
}

u4 readU4(FILE* fp, int offset) {
    return readDoubleWord(fp, offset);
}