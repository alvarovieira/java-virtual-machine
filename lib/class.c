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
    int offset = 0;
    Class* class = (Class*) malloc(sizeof(Class));

    class->magic = readU4(fp, offset);
    offset += 4;

    class->minorVersion = smallEndianToBigEndian2Bytes(readU2(fp, offset));
    offset += 2;

    class->majorVersion = smallEndianToBigEndian2Bytes(readU2(fp, offset));
    offset += 2;

    class->constantPoolCount = smallEndianToBigEndian2Bytes(readU2(fp, offset));
    offset += 2;

    class->constantPool = readConstantPool(fp, &offset, class->constantPoolCount - 1);

    class->accessFlags = smallEndianToBigEndian2Bytes(readU2(fp, offset));
    offset += 2;

    class->thisClass = smallEndianToBigEndian2Bytes(readU2(fp, offset));
    offset += 2;

    class->superClass = smallEndianToBigEndian2Bytes(readU2(fp, offset));
    offset += 2;

    class->interfacesCount = smallEndianToBigEndian2Bytes(readU2(fp, offset));
    offset += 2;

    class->interfaces = readInterfaces(fp, &offset, class->interfacesCount);

    class->fieldsCount = smallEndianToBigEndian2Bytes(readU2(fp, offset));
    offset += 2;

    return class;
}

ConstPoolInfo* readConstantPool(FILE* fp, int* offset, u2 cpCount) {
    int cpIndex;

    // Allocate space for the costant pool
    ConstPoolInfo* cpInfo = (ConstPoolInfo*) malloc(cpCount * sizeof(ConstPoolInfo));

    for (cpIndex = 0; cpIndex < cpCount; cpIndex++) {

        // Read tag
        cpInfo[cpIndex].tag = readU1(fp, (*offset));
        (*offset)++;

        // Read cpInfo
        switch(cpInfo[cpIndex].tag) {
            case UTF8:
                cpInfo[cpIndex].utf8Const.length = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
                (*offset) += 2;
                cpInfo[cpIndex].utf8Const.bytes = (u1*) malloc((cpInfo[cpIndex].utf8Const.length) * sizeof(u1));
                for (int utf8Index = 0; utf8Index < (cpInfo[cpIndex].utf8Const.length); utf8Index++) {
                    cpInfo[cpIndex].utf8Const.bytes[utf8Index] = smallEndianToBigEndian1Byte(readU1(fp, (*offset)));
                    (*offset)++;
                }
                break;

            case INTEGER:
                cpInfo[cpIndex].integerConst.bytes = smallEndianToBigEndian4Bytes(readU4(fp, (*offset)));
                (*offset) += 4;
                break;

            case FLOAT:
                cpInfo[cpIndex].floatConst.bytes = smallEndianToBigEndian4Bytes(readU4(fp, (*offset)));
                (*offset) += 4;
                break;

            case LONG:
                cpInfo[cpIndex].longConst.highBytes = smallEndianToBigEndian4Bytes(readU4(fp, (*offset)));
                (*offset) += 4;
                cpInfo[cpIndex].longConst.lowBytes = smallEndianToBigEndian4Bytes(readU4(fp, (*offset)));
                (*offset) += 4;
                break;

            case DOUBLE:
                cpInfo[cpIndex].doubleConst.highBytes = smallEndianToBigEndian4Bytes(readU4(fp, (*offset)));
                (*offset) += 4;
                cpInfo[cpIndex].doubleConst.lowBytes = smallEndianToBigEndian4Bytes(readU4(fp, (*offset)));
                (*offset) += 4;
                break;

            case CLASS:
                cpInfo[cpIndex].classConst.nameIndex = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
                (*offset) += 2;
                break;

            case STRING:
                cpInfo[cpIndex].stringConst.stringIndex = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
                (*offset) += 2;
                break;

            case FIELD_REF:
                cpInfo[cpIndex].fieldRefConst.classIndex = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
                (*offset) += 2;
                cpInfo[cpIndex].fieldRefConst.nameAndTypeIndex = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
                (*offset) += 2;
                break;

            case METHOD_REF:
                cpInfo[cpIndex].methodRefConst.classIndex = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
                (*offset) += 2;
                cpInfo[cpIndex].methodRefConst.nameAndTypeIndex = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
                (*offset) += 2;
                break;

            case INTERFACE_METHOD_REF:
                cpInfo[cpIndex].interfaceMethodRefConst.classIndex = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
                (*offset) += 2;
                cpInfo[cpIndex].interfaceMethodRefConst.nameAndTypeIndex = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
                (*offset) += 2;
                break;

            case NAME_AND_TYPE:
                cpInfo[cpIndex].nameAndTypeConst.nameIndex = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
                (*offset) += 2;
                cpInfo[cpIndex].nameAndTypeConst.descriptorIndex = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
                (*offset) += 2;
                break;

            default:
                printf("Error while reading classfile");
        }

    }

    return cpInfo;
}

u2* readInterfaces(FILE* fp, int* offset, u2 interfacesCount) {
    int interfacesIndex;

    u2* interfaces = (u2*) malloc(interfacesCount * sizeof(u2));

    for (interfacesIndex = 0; interfacesIndex < interfacesCount; interfacesIndex++) {
        interfaces[interfacesIndex] = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
        (*offset) += 2;
    }

    return interfaces;
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