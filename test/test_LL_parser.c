#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stack.h"
#include "LL-parser.h"

int test_reverse_string(void)
{
    assert((strcmp(reverse_string("AB1aB2"), "2Ba1BA")) == 0);
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
    if (test_reverse_string() == 0)
        printf("reverse_string is okay");
    if (test_ll_parse() == 0)
        printf("ll_parse is okay");
    printf("Sucess\n");
    return 0;
}
