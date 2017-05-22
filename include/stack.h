/** @file stack.h
 *
 * @brief Stack operations library.
 */

#ifndef _STACK_H
#define _STACK_H

/** 
 * @struct
 */
struct _stack {
    void* elemRef;
    struct _stack* next;
};
typedef struct _stack Stack;

/** 
 * @fn Stack* init(void* firstElemRef)
 * @brief Initialize a stack.
 *
 * Creates a stack with the first element, received as parameter. And returns 
 * the reference of this stack.
 */
Stack* init(void* firstElemRef);

/**
 * @fn void push(Stack ** stackRef, void* elemRef)
 * @brief Push operation on the stack.
 * 
 * Adds a new head to the stack, passed by reference, with the element, 
 * reiceved as parameter.
 */
void push(Stack** stackRef, void* elemRef);

/**
 * @fn Stack* pop(Stack** stackRef)
 * @brief Pop operation on the stack.
 *
 * Removes the head of the stack, passed by reference, and updates the stack 
 * referece to point the new stack without the old head. And returns the 
 * reference of the old head. This method doesn't free the pointer to the old
 * head, so it's responsability of the caller to dealocate this space.
 */
Stack* pop(Stack** stackRef);

/**
 * @fn void delete(Stack** stackRef);
 * @brief Dealocate Stack reference.
 * 
 * Dealocates stack reference. Is responsability of the caller to dealocate the
 * memory used by the element of this stack reference.
 */
void delete(Stack** stackRef);

/**
 * @fn void* head(Stack* stackRef)
 * @brief Get head's element of the stack.
 *
 * Returns the reference of the head's element.
 */
void* head(Stack* stackRef);

#endif