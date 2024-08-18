# pragma once

typedef struct node_t node_t;
typedef struct node_t
{
    char symbol;
    node_t *next;
}node_t;

/**
 * @brief A stack structure made to store a derivation tree from a Context Free Grammar
 * 
 */
typedef struct
{
    unsigned int lenght;
    node_t *top;
}stack_t;


// create a stack structure with zero elements and return its adress.
stack_t *stack_create(void);

// inserts a symbol at the top of the stack.
int stack_push(stack_t* stack, char symbol);

// inserts all symbols at the stack, starting from left. It stops to add symbols when finding symbol '\0'
int stack_push_sequence(stack_t* stack, char *string);

/**
 * @brief remove the top symbol from stack.
 * 
 * @param stack 
 * @return 0 is sucess, -1 if stack is already empty and -2 if stack pointer is NULL.
 */
int stack_pull(stack_t* stack);

// check the top symbol from the stack without removing it. If the stack is empty, the symbol "@" is returned in its place.
char stack_check(stack_t* stack);

// free all allocated memory nodes from stack.
int stack_pull_all(stack_t* stack);