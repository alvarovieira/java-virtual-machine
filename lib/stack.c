/**
 * @file stack.c
 * @brief Stack operations library source.
 * @authors Ismael Coelho Medeiros (14/0083162)
 *
 * This file contains all the function source codes which has the
 * signatures declared on the stack.h file.
 */

#include <stdlib.h>
#include "stack.h"

Stack* init(void* firstElemRef) {
    Stack* stackRef = (Stack*) malloc(sizeof(Stack));
    stackRef->elemRef = firstElemRef;
    stackRef->next = NULL;
    return stackRef;
}

void push(Stack** stackRef, void* elemRef) {
    Stack* newHeadRef = (Stack*) malloc(sizeof(Stack));
    newHeadRef->elemRef = elemRef;
    newHeadRef->next = (*stackRef);
    (*stackRef) = newHeadRef;
}

Stack* pop(Stack** stackRef) {
    Stack* headRef = (*stackRef);
    (*stackRef) = (*stackRef)->next;
    headRef->next = NULL;
    return headRef;
}

void delete(Stack** stackRef) {
    free(stackRef);
    stackRef = NULL;
}

void* head(Stack* stackRef) {
    return stackRef->elemRef;
}