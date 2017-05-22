/** 
 * @file stack.h
 * @brief Stack operations and types library.
 * @authors Ismael Coelho Medeiros (14/0083162)
 *
 * @todo Description
 */

#ifndef _STACK_H
#define _STACK_H

/** 
 * @brief Stack structure definition.
 *
 * @todo Description
 */
struct _stack {
    /**
     * @brief Reference to the stack's head element.
     *
     * @todo Description
     */
    void* elemRef;
    /**
     * @brief Reference to the next stack below the head.
     *
     * @todo Description
     */
    struct _stack* next;
};

/**
 * @brief Stack type definition.
 *
 * @todo Description
 */
typedef struct _stack Stack;

/** 
 * @brief Initialize a stack.
 *
 * Creates a stack with the first element, received as parameter. And returns 
 * the reference of this stack.
 *
 * @todo Parameters
 * @todo Return
 */
Stack* init(void* firstElemRef);

/**
 * @brief Push operation on the stack.
 * 
 * Adds a new head to the stack, passed by reference, with the element, 
 * reiceved as parameter.
 *
 * @todo Parameters
 */
void push(Stack** stackRef, void* elemRef);

/**
 * @brief Pop operation on the stack.
 *
 * Removes the head of the stack, passed by reference, and updates the stack 
 * referece to point the new stack without the old head. And returns the 
 * reference of the old head. This method doesn't free the pointer to the old
 * head, so it's responsability of the caller to dealocate this space.
 *
 * @todo Parameters
 * @todo Return
 */
Stack* pop(Stack** stackRef);

/**
 * @brief Dealocate Stack reference.
 * 
 * Dealocates stack reference. Is responsability of the caller to dealocate the
 * memory used by the element of this stack reference.
 *
 * @todo Parameters
 */
void delete(Stack** stackRef);

/**
 * @brief Get head's element of the stack.
 *
 * Returns the reference of the head's element.
 *
 * @todo Parameters
 * @todo Return
 */
void* head(Stack* stackRef);

#endif