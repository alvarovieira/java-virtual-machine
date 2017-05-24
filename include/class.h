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
 * @brief Classfile structure.
 * 
 * @todo Description
 */
struct _class {
    u4 magic;
    u2 majorVersion;
    u2 minorVersion;
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