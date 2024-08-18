#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

int test_stack_create(void)
{
    stack_t *stack = stack_create();
    assert(stack != NULL);
    assert(sizeof(*stack) == sizeof(stack_t));
    assert(stack->lenght == 0);
    assert(stack->top == NULL);
    free(stack);
    return 0;
}

int test_stack_push(void)
{
    stack_t *stack = NULL;

    assert(stack_push(stack, 'N') == 1); // NULL stack
    
    stack = stack_create();
    stack_push(stack, 'A');
    stack_push(stack, 'B');
    stack_push(stack, 'C');
    assert(stack->lenght == 3);
    assert(stack->top->symbol == 'C');
    assert(stack->top->next->symbol == 'B');
    assert(stack->top->next->next->symbol == 'A');
    assert(stack->top->next->next->next == NULL);
    free(stack->top->next->next);
    free(stack->top->next);
    free(stack->top);
    free(stack);
    return 0;
}

int test_stack_push_sequence(void)
{
    stack_t *stack = NULL;

    assert(stack_push_sequence(stack, "NULL") == 1); // NULL stack
    
    stack = stack_create();
    stack_push_sequence(stack, "ABC");
    assert(stack->lenght == 3);
    assert(stack->top->symbol == 'C');
    assert(stack->top->next->symbol == 'B');
    assert(stack->top->next->next->symbol == 'A');
    assert(stack->top->next->next->next == NULL);
    free(stack->top->next->next);
    free(stack->top->next);
    free(stack->top);
    free(stack);
    return 0;
}

int test_stack_pull(void)
{
    stack_t *stack = NULL;

    assert(stack_pull(stack) == -2); // NULL stack
    
    stack = stack_create();
    stack_push_sequence(stack, "ABC");
    
    assert(stack_pull(stack) == 0);
    
    assert(stack_pull(stack) == 0);
    assert(stack->lenght == 1);
    assert(stack->top->symbol == 'A');
    assert(stack->top->next == NULL);

    assert(stack_pull(stack) == 0);
    assert(stack->lenght == 0);
    assert(stack->top == NULL);

    assert(stack_pull(stack) == -1);
    return 0;
}

int test_stack_check(void)
{
    stack_t *stack = NULL;

    assert(stack_check(stack) == '@'); // NULL stack
    
    stack = stack_create();
    stack_push(stack, 'A');
    assert(stack_check(stack) == 'A');
    assert(stack->lenght == 1);
    assert(stack->top->symbol == 'A');
    assert(stack->top->next == NULL);

    stack_pull(stack);
    assert(stack_check(stack) == '@');
    return 0;
}

int test_stack_pull_all(void)
{
    stack_t *stack = NULL;

    assert(stack_pull_all(stack) == 1); // NULL stack

    stack = stack_create();
    stack_push_sequence(stack, "FREE");
    assert(stack_pull_all(stack) == 0);
    assert(stack->lenght == 0);
    assert(stack->top == NULL);
    return 0;
}

int main(int argc, char const *argv[])
{
    if(test_stack_create() == 0)
        printf("stack_create is okay\n");
    if(test_stack_push() == 0)
        printf("stack_push is okay\n");
    if(test_stack_push_sequence() == 0)
        printf("stack_push_sequence is okay\n");
    if(test_stack_pull() == 0)
        printf("stack_pull is okay\n");
    if(test_stack_check() == 0)
        printf("stack_check is okay\n");
    if(test_stack_pull_all() == 0)
        printf("stack_pull_all is okay\n");
    printf("sucess\n");
    return 0;
}
