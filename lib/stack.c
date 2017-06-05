/**
 * @file stack.c
 * @brief Stack operations library source.
 * @authors Ismael Coelho Medeiros (14/0083162)
 *
 * This file contains all the function source codes which has the
 * signatures declared on the stack.h file.
 */

#include <stdlib.h>
#include "mem-manager.h"
#include "stack.h"

Stack* stkInit(void* firstElemRef) {
    Stack* stackRef = (Stack*) allocate(sizeof(Stack));
    stackRef->elemRef = firstElemRef;
    stackRef->next = NULL;
    return stackRef;
}

void stkPush(Stack** stackRef, void* elemRef) {
    Stack* newHeadRef = (Stack*) allocate(sizeof(Stack));
    newHeadRef->elemRef = elemRef;
    newHeadRef->next = (*stackRef);
    (*stackRef) = newHeadRef;
}

Stack* stkPop(Stack** stackRef) {
    Stack* headRef = (*stackRef);
    (*stackRef) = (*stackRef)->next;
    headRef->next = NULL;
    return headRef;
}

void stkDelete(Stack** stackRef) {
    free(stackRef);
    stackRef = NULL;
}

void* stkHead(Stack* stackRef) {
    return stackRef->elemRef;
}