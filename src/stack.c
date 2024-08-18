# include "stack.h"
# include <stdlib.h>

stack_t *stack_create(void)
{
    stack_t *new_stack = (stack_t*) malloc(sizeof(stack_t));
    new_stack->lenght = 0;
    new_stack->top = NULL;
    return new_stack;
}

int stack_push(stack_t* stack, char symbol)
{
    if (stack == NULL)
    {
        return 1;
    }
    else
    {
        node_t *new_node = (node_t*) malloc(sizeof(node_t));
        new_node->symbol = symbol;
        new_node->next = stack->top;
        stack->top = new_node;
        stack->lenght++;
        return 0;        
    }
}


int stack_push_sequence(stack_t* stack, char *string)
{
    if (stack == NULL)
    {
        return 1;
    }
    else
    {
        int index = 0;
        while (string[index] != '\0')
        {
            stack_push(stack, string[index]);
            index++;
        }
        return 0;
    }
}

int stack_pull(stack_t* stack)
{
    if (stack == NULL)
    {
        return -2;
    }
    else if (stack->lenght <= 0)
    {
        return -1;
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
    if (stack == NULL)
    {
        return '@';
    }
    else if (stack->top == NULL)
    {
        return '@';
    }
    else
    {
        return stack->top->symbol;
    }
}

int stack_pull_all(stack_t* stack)
{
    if (stack == NULL)
    {
        return 1;
    }
    else
    {
        while (stack_pull(stack) == 0);
        return 0;  
    }
}