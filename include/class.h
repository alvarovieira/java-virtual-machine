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
    /**
     * @todo Brief
     * @todo Description
     */
    u1 tag;
    /**
     * @todo Brief
     * @todo Description
     */
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
            union {
                u4 bytes;
                float value;
            };
        } floatConst;
        struct {
            union {
                struct {
                    u4 lowBytes;
                    u4 highBytes;
                } bytes;
                long int value;
            };
        } longConst;
        struct {
            union {
                struct {
                    u4 lowBytes;
                    u4 highBytes;
                } bytes;
                double value;
            };
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
    /**
     * @todo Brief
     * @todo Description
     */
    u4 magic;
    /**
     * @todo Brief
     * @todo Description
     */
    u2 majorVersion;
    /**
     * @todo Brief
     * @todo Description
     */
    u2 minorVersion;
    /**
     * @todo Brief
     * @todo Description
     */
    u2 constantPoolCount;
    /**
     * @todo Brief
     * @todo Description
     */
    ConstPoolInfo* constantPool;
    /**
     * @todo Brief
     * @todo Description
     */
    u2 accessFlags;
    /**
     * @todo Brief
     * @todo Description
     */
    u2 thisClass;
    /**
     * @todo Brief
     * @todo Description
     */
    u2 superClass;
    /**
     * @todo Brief
     * @todo Description
     */
    u2 interfacesCount;
    /**
     * @todo Brief
     * @todo Description
     */
    u2* interfaces;
    /**
     * @todo Brief
     * @todo Description
     */
    u2 fieldsCount;
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
    LARGE_NUMERIC_CONTINUED = 0,
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
u2* readInterfaces(FILE* fp, int* offset, u2 interfacesCount);

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