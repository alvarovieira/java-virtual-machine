/**
 * @file class.h
 * @brief Classfile operations and types library header.
 * @authors Ismael Coelho Medeiros (14/0083162)
 * @autorhs Álvaro Torres Vieira (14/0079661)
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

 struct _attribute_info {
        u2 attributeNameIndex;
        u4 attributeLength;
        u1 *fieldInfo;
 };

 /**
 * @brief Classfile structure.
 * 
 * @todo Description
 */

 typedef struct _attribute_info attributeInfo;

 /**
 * @brief Classfile structure.
 * 
 * @todo Description
 */


struct _method_info {
    u2 accessFlags;
    u2 nameIndex;
    u2 descriptorIndex;
    u2 attributesCount;
    attributeInfo *attributes;
};

/**
 * @brief Classfile structure.
 * 
 * @todo Description
 */

typedef struct _method_info methodInfo;

/**
 * @brief Classfile structure.
 * 
 * @todo Description
 */

 struct _field_info {
    u2 accessFlags;
    u2 nameIndex;
    u2 descriptorIndex;
    u2 attributesCount;
    attributeInfo *attributes;
};

/**
 * @brief Classfile structure.
 * 
 * @todo Description
 */
typedef struct _field_info fieldInfo;

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
    u2 *interfaces;
    
    u2 fieldsCount;
    fieldInfo *fields;
    u2 methodsCount;
    methodInfo *methods;
    u2 attributesCount;
    attributeInfo *attributes;
};

/**
 * @brief Class type definition.
 * 
 * @todo Description
 */

typedef struct _class Class;


/**
 * @brief Classfile structure.
 * 
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

/*
enum {
    ACC_PUBLIC 
    ACC_PRIVATE
    ACC_PROTECTED
    ACC_STATIC
    ACC_FINAL
    ACC_SYNCHRONIZED
    ACC_NATIVE
    ACC_ABSTRACT
    ACC_STRICT

} methodAccessFlags;
*/

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

fieldInfo * readFields (FILE* fp, int* offset, u2 fieldCount);
 /**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */

methodInfo* readMethods (FILE* fp, int* offset, u2 methodsCount);
 /**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */

attributeInfo* readAttributes (FILE* fp, int* offset, u2 attributesCount);
 
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