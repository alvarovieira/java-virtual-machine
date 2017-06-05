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
#include "mem-manager.h"
#include "file.h"
#include "convert.h"
#include "class.h"



Class* readClassfile(FILE* fp) {
    int offset = 0;
    Class* class = (Class*) allocate(sizeof(Class));

    class->magic = smallEndianToBigEndian4Bytes(readU4(fp, offset));
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

    class->fields = readFields(fp, &offset, class->fieldsCount);

    class->methodsCount = smallEndianToBigEndian2Bytes(readU2(fp, offset));
    offset += 2;

    class->methods = readMethods(fp, &offset, class->methodsCount);

    class->attributesCount = smallEndianToBigEndian2Bytes(readU2(fp, offset));
    offset += 2;

    class->attributes = readAttributes(fp, &offset, class->attributesCount);

    return class;
}

ConstPoolInfo* readConstantPool(FILE* fp, int* offset, u2 cpCount) {
    int cpIndex;

    // Allocate space for the costant pool
    ConstPoolInfo* cpInfo = (ConstPoolInfo*) allocate(cpCount * sizeof(ConstPoolInfo));

    for (cpIndex = 0; cpIndex < cpCount; cpIndex++) {

        // Read tag
        cpInfo[cpIndex].tag = readU1(fp, (*offset));
        (*offset)++;

        // Read cpInfo
        switch(cpInfo[cpIndex].tag) {
            case UTF8:
                cpInfo[cpIndex].utf8Const.length = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
                (*offset) += 2;
                cpInfo[cpIndex].utf8Const.bytes = (u1*) allocate((cpInfo[cpIndex].utf8Const.length) * sizeof(u1));
                for (int utf8Index = 0; utf8Index < (cpInfo[cpIndex].utf8Const.length); utf8Index++) {
                    cpInfo[cpIndex].utf8Const.bytes[utf8Index] = readU1(fp, (*offset));
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
                cpInfo[cpIndex].longConst.bytes.highBytes = smallEndianToBigEndian4Bytes(readU4(fp, (*offset)));
                (*offset) += 4;
                cpInfo[cpIndex].longConst.bytes.lowBytes = smallEndianToBigEndian4Bytes(readU4(fp, (*offset)));
                (*offset) += 4;
                // This field are stored in two indexes
                cpIndex++;
                cpInfo[cpIndex].tag = LARGE_NUMERIC_CONTINUED;
                break;

            case DOUBLE:
                cpInfo[cpIndex].doubleConst.bytes.highBytes = smallEndianToBigEndian4Bytes(readU4(fp, (*offset)));
                (*offset) += 4;
                cpInfo[cpIndex].doubleConst.bytes.lowBytes = smallEndianToBigEndian4Bytes(readU4(fp, (*offset)));
                (*offset) += 4;
                // This field are stored in two indexes
                cpIndex++;
                cpInfo[cpIndex].tag = LARGE_NUMERIC_CONTINUED;
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
                printf("Error while reading classfile on position: %ld\n", ftell(fp));
        }

    }

    return cpInfo;
}

u2* readInterfaces(FILE* fp, int* offset, u2 interfacesCount) {
    int interfacesIndex;

    u2* interfaces = (u2*) allocate(interfacesCount * sizeof(u2));

    for (interfacesIndex = 0; interfacesIndex < interfacesCount; interfacesIndex++) {
        interfaces[interfacesIndex] = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
        (*offset) += 2;
    }

    return interfaces;
}

fieldInfo* readFields (FILE* fp, int* offset, u2 fieldsCount){
/*  CAMPOS:
    u2 access_flags;  
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;   
    attribute_info attributes[attributes_count];
*/

    int count = 0;
    fieldInfo* field = ((fieldInfo *) calloc (fieldsCount, sizeof(fieldInfo)));

    for(count = 0; count < fieldsCount; count++)
    {

        field[count].accessFlags = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
            (*offset) +=2;
        field[count].nameIndex = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
            (*offset) +=2;
        field[count].descriptorIndex = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
            (*offset) +=2;
        field[count].attributesCount = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
            (*offset) +=2;
        field[count].attributes = readAttributes(fp, offset, field[count].attributesCount);
    }

    return field;

}

methodInfo* readMethods (FILE* fp, int* offset, u2 methodsCount) {
/*  CAMPOS:
    u2 access_flags; 
    u2 name_index;   
    u2 descriptor_index; 
    u2 attributes_count;  
    attribute_info attributes[attributes_count];
*/

    int count = 0;
    methodInfo* method = (methodInfo*) calloc(methodsCount, sizeof(methodInfo));

    for(count = 0; count < methodsCount; count++)
        {

            method[count].accessFlags = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
            printf("Access Flags: %d\n", method[count].accessFlags);
            (*offset) +=2;
            
            method[count].nameIndex = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
            printf("Name index: %d\n", method[count].nameIndex);
            (*offset) +=2;
            
            method[count].descriptorIndex = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
            printf("descriptorIndex: %d\n", method[count].descriptorIndex);
            (*offset) +=2;
            
            method[count].attributesCount = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
            (*offset) +=2;
            printf("attributesCount: %d\n", method[count].attributesCount);
            
            method[count].attributes = readAttributes(fp, offset, method[count].attributesCount);
            getchar();
        }


    return method;
}

attributeInfo* readAttributes (FILE* fp, int* offset, u2 attributesCount){
/*  CAMPOS:
    u2 attributeNameIndex;
    u4 attributeLength;
    u1 *filedInfo;
*/
    int count = 0;
    attributeInfo* attribute = (attributeInfo*) calloc(attributesCount, sizeof(attributeInfo));

    for(count = 0; count < attributesCount; count++)
        {
            
            attribute[count].attributeNameIndex = smallEndianToBigEndian2Bytes(readU2(fp, (*offset)));
                (*offset) +=2;
            attribute[count].attributeLength = smallEndianToBigEndian4Bytes(readU4(fp,(*offset)));
                (*offset) +=4;
            attribute[count].fieldInfo = smallEndianToBigEndian2Bytes(readU1(fp, (*offset)));
                (*offset) +=2;
            printf("---- ATTRIBUTE\n");
            printf("Name index: %d\n", attribute[count].attributeNameIndex);
            printf("attributeLength: %d\n", attribute[count].attributeLength);
            printf("fieldInfo: %d\n", attribute[count].fieldInfo);
            getchar();    
        }


    return attribute;
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