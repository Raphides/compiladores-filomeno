# pragma once


// extra function to reverse the order of string characters based on stack structure.
char * reverse_string(char * original_string);

/**
 * @brief LL parser algorithm
 * 
 * @param input_string string to be parsed.
 * @param lltable a table with its rows as non-terminal symbols, its columns as terminal symbols and its cells with strings representing the right side of producions.
 * @return int | returns 0 if the input string is part of the language represented by the LL Table. Return 1 if not.
 */
int ll_parse(char const *input_string, char ***lltable);