#include <stdio.h>

#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "stack.h" // to debug on VSCODE, change to "stack.c"

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

int ll_parse(char const *input_string, char ***lltable)
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
            // with LL Table implemented with a vector (char ***), there should be a extra process to translate labels to table positions. The referred procedure is down there:
            // Extra procedure - start
            int top_index = (top_symbol == 'S') ? 0 : (top_symbol == 'F') ? 1 : -1;
            int input_index = (analysed_input_symbol == '(') ? 0 : (analysed_input_symbol == ')') ? 1 :
                                (analysed_input_symbol == 'a') ? 2 : (analysed_input_symbol == '+') ? 3 :
                                (analysed_input_symbol == '$') ? 4 : -1;

            if (input_index == -1 || lltable[top_index][input_index] == NULL)
            {
                return 1; // Parsing error
            }            
            // extra procedure - end

            production_to_be_added = lltable[top_index][input_index];

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

int test_ll_parse(void)
{
    // testing based on grammar and string at https://en.wikipedia.org/wiki/LL_parser#Set_up
    
    
    int row = 2; //number of non terminal symbols
    int column = 5; //number of terminal symbols
    
    char ***lltable = (char ***) malloc(row * sizeof(char **));


    for (int i = 0; i < row; i++)
    {
        lltable[i] = (char **) malloc(column * sizeof(char *));
        for (int j = 0; j < column; j++)
        {
            lltable[i][j] = NULL;
        }
    }
    // S -> ( S + F )
    lltable[0][0] = strdup("(S+F)");

    // S -> F
    lltable[0][2] = strdup("F");

    // F -> a
    lltable[1][2] = strdup("a");

    // string to be parsed
    return ll_parse("(a+a)", lltable);
}

int main(int argc, char const *argv[])
{
    if (test_ll_parse() == 0)
        printf("ll_parse is okay\n");
    printf("Sucess\n");
    return 0;
}