/**
 * @file class.h
 * @brief Classfile operations and types library header.
 * @authors Ismael Coelho Medeiros (14/0083162)
 * 
 * @todo Description
 */
#ifndef _CLASS_H
#define _CLASS_H

#include "common.h"

/**
 * @todo Brief
 * @todo Description
 */
struct _const_pool_info {
    u1 tag;
    union {
        struct {
            u2 nameIndex;
        } classConst;
        struct {
            u2 classIndex;
            u2 nameAndTypeIndex;
        } fieldRefConst;
        struct {
            u2 nameIndex;
            u2 descriptorIndex;
        } nameAndTypeConst;
        struct {
            u2 length;
            u1* bytes;
        } utf8Const;
        struct {
            u2 classIndex;
            u2 nameAndTypeIndex;
        } methodRefConst;
        struct {
            u2 classIndex;
            u2 nameAndTypeIndex;
        } interfaceMethodRefConst;
        struct {
            u2 stringIndex;
        } stringConst;
        struct {
            u4 bytes;
        } integerConst;
        struct {
            u4 bytes;
        } floatConst;
        struct {
            u4 highBytes;
            u4 lowBytes;
        } longConst;
        struct {
            u4 highBytes;
            u4 lowBytes;
        } doubleConst;
    };
};

/**
 * @todo Brief
 * @todo Description
 */
typedef struct _const_pool_info ConstPoolInfo;

/**
 * @brief Classfile structure.
 * 
 * @todo Description
 */
struct _class {
    u4 magic;
    u2 majorVersion;
    u2 minorVersion;
    u2 constantPoolCount;
    ConstPoolInfo* constantPool;
    u2 accessFlags;
    u2 thisClass;
    u2 superClass;
    u2 interfacesCount;
};

/**
 * @brief Class type definition.
 * 
 * @todo Description
 */
typedef struct _class Class;

/**
 * @todo Brief
 * @todo Description
 */
enum {
    UTF8 = 1,
    INTEGER = 3,
    FLOAT = 4,
    LONG = 5,
    DOUBLE = 6,
    CLASS = 7,
    STRING = 8,
    FIELD_REF = 9,
    METHOD_REF = 10,
    INTERFACE_METHOD_REF = 11,
    NAME_AND_TYPE = 12
} Contants;

/**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
ConstPoolInfo* readConstantPool(FILE* fp, int* offset, u2 cpCount);

/**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
Class* readClassfile(FILE* fp);

/**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
u1 readU1(FILE* fp, int offset);

/**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
u2 readU2(FILE* fp, int offset);

/**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
u4 readU4(FILE* fp, int offset);

#endif //_CLASS_H