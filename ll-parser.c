/**
 * @file ll-parser.c
 * @author Raphael Mendes da Silva, Gabrielly Assunsão, Vitor
 * @brief LL(1) Parser Implementation
 * @version 0.1
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Index
*  1. Stack
*  2. LL Table
*  3. LL(1) Parser
*/


// #############################################
// 1. Stack - Declaration
// #############################################

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
void stack_push(stack_t* stack, char symbol);

// inserts all symbols at the stack, starting from left. It stops to add symbols when finding symbol '\0'
void stack_push_sequence(stack_t* stack, char *string);

// remove the top symbol from stack.
int stack_pull(stack_t* stack);

// check the top symbol from the stack without removing it. If the stack is empty, the symbol "@" is returned in its place.
char stack_check(stack_t* stack);

// free all allocated memory blocks from stack.
void free_all_stack(stack_t* stack);



// #############################################
// 1. Stack - Implementation
// #############################################

stack_t *stack_create(void)
{
    stack_t *new_stack = (stack_t*) malloc(sizeof(stack_t));
    new_stack->lenght = 0;
    new_stack->top = NULL;
    return new_stack;
}

void stack_push(stack_t* stack, char symbol)
{
    node_t *new_node = (node_t*) malloc(sizeof(node_t));
    new_node->symbol = symbol;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->lenght++;
}


void stack_push_sequence(stack_t* stack, char *string)
{
    int index = 0;
    while (string[index] != '$')
    {
        stack_push(stack, string[index]);
    }
}

int stack_pull(stack_t* stack)
{
    if (stack->lenght <= 0)
    {
        return 1;
    }
    else
    {
        node_t* temp = stack->top->next;
        free(stack->top);
        stack->top = temp;
        stack->lenght--;
        return 0;
    }
}

char stack_check(stack_t* stack)
{
    if (stack->top == NULL)
    {
        return '@';
    }
    else
    {
        return stack->top->symbol;
    }
}

void free_all_stack(stack_t* stack)
{
    node_t *to_be_free, *temp;
    to_be_free = stack->top;
    while (to_be_free != NULL)
    {
        temp = to_be_free->next;
        free(to_be_free);
        to_be_free = temp;
    }
    free(stack);
}



// #############################################
// 2. LL Table - Declaration
// #############################################

char ***create_ll_table();

char first();

char follow();

// #############################################
// 2. LL Table - Implementation
// #############################################



// #############################################
// 3. LL(1) Parser algorithm - Declaration
// #############################################

/**
 * @brief LL parser algorithm
 * 
 * @param input_string string to be parsed.
 * @param lltable a table with its rows as non-terminal symbols, its columns as terminal symbols and its cells with strings representing the right side of producions.
 * @return int | returns 0 if the input string is part of the language represented by the LL Table. Return 1 if not.
 */
int ll_parser_algorithm(char const *input_string, int ***lltable);


// #############################################
// 3. LL(1) Parser algorithm - Implementation
// #############################################


// extra function to reverse the order of string characters based on stack structure.
char * reverse_string(char * original_string)
{
    int str_index = 0;
    stack_t* string_stack = stack_create();
    while (original_string[str_index] != '\0')
    {
        stack_push(string_stack, original_string[str_index]);
        str_index++;
    }
    char *new_string = (char*) malloc((sizeof(char) * str_index) + 1);
    int new_string_index = 0;
    for (size_t i = 0; i < str_index; i++)
    {
        new_string[i] = stack_check(string_stack);
        stack_pull(string_stack);
    }
    new_string[str_index] = '\0';
    return new_string;
}

int ll_parser_algorithm(char const *input_string, int ***lltable)
{
    int input_len = strlen(input_string);

    stack_t* derivation_tree_stack = stack_create();
    stack_push(derivation_tree_stack, 'S'); 

    char top_symbol; // top symbol on derivation tree stack
    char analysed_input_symbol; // symbol analysed now from the input.
    int analysed_input_index = 0; // index of the symbol analysed now.

    char* production_to_be_added = (char*) malloc (100);

    while (derivation_tree_stack->lenght != 0 || derivation_tree_stack->top != NULL)
    {
        // update symbol analysed from input and top symbol from stack.
        analysed_input_symbol = input_string[analysed_input_index];
        top_symbol = stack_check(derivation_tree_stack);

        if (analysed_input_symbol == top_symbol)
        {
            analysed_input_index++;
            stack_pull(derivation_tree_stack);
            continue;
        }
        else
        {
            production_to_be_added = lltable[top_symbol][analysed_input_symbol];

            if (production_to_be_added == NULL)
            {
                return 1;
            }
            else
            {
                stack_pull(derivation_tree_stack); // remove variable to be replaced from stack
                stack_push_sequence(derivation_tree_stack, reverse_string(production_to_be_added)); // add the production result to stack.
                continue;
            }
        }
    }
    return 0;

}

// #############################################
int main(int argc, char const *argv[])
{

// Stack Test
/*     stack_t* pilha = stack_create();
    stack_push(pilha, 'C');
    stack_push(pilha, 'B');
    stack_push(pilha, 'A');

    printf("%d\n", stack_pull(pilha));
    printf("%c\n\n", stack_check(pilha));
    
    printf("%d\n", stack_pull(pilha));
    printf("%c\n\n", stack_check(pilha));

    printf("%d\n", stack_pull(pilha));
    printf("%c\n\n", stack_check(pilha));

    free_all_stack(pilha); */

    return 0;
}
