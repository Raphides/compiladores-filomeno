#include <stdlib.h>
#include "stack.h"
#include "LL-table.h"

char * reverse_string(char * original_string)
{
    if (original_string == NULL)
    {
        return NULL;
    }
    stack_t* string_stack = stack_create();
    int str_index = 0;
    for (;original_string[str_index] != '\0';str_index++)
    {
        stack_push(string_stack, original_string[str_index]);
    }

    char *new_string = (char*) malloc((sizeof(char) * str_index) + 1);
    new_string[str_index] = '\0';

    for (size_t i = 0; i < str_index; i++)
    {
        new_string[i] = stack_check(string_stack);
        stack_pull(string_stack);
    }
    return new_string;
}

int ll_parse(char const *input_string, hash_table_t *table)
{
    stack_t* derivation_tree_stack = stack_create();
    stack_push(derivation_tree_stack, 'S'); 

    char top_symbol; // top symbol on derivation tree stack
    char analysed_input_symbol; // symbol analysed now from the input.
    int analysed_input_index = 0; // index of the symbol analysed now.

    char* production_to_be_added = (char*) malloc(100);
    
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
            char key[4];
            snprintf(key, sizeof(key), "%c%c", top_symbol, analysed_input_symbol);

            production_to_be_added = hash_table_lookup(table, key);
            
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
