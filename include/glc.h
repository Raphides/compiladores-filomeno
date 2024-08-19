#pragma once

/**
 * @brief Context Free Grammar Productions
 * 
 */
typedef struct cfg_production cfg_production_t;

typedef struct cfg_production
{
    char *right_side; //with no spaces, please
    char left_side;
    cfg_production_t *next_production;
}cfg_production_t;


// Context Free Grammar Type
typedef struct
{
    char *terminals; // Terminal symbols
    char *non_terminals; // Non Terminal symbols
    char start_symbol; // Non terminal start symbol
    cfg_production_t *first_production; // array of productions
} cfg_t;