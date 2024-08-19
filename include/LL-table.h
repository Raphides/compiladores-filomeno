#pragma once
#include "hash_table.h"
#include "glc.h"

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

/**
 * @brief List all first terminal symbols on all productions with a specific right side symbol. FIRST(A)
 * 
 * @param grammar Corresponding grammar with all productions
 * @param symbol right-side symbol from productions you want to list
 * @return list of first terminal symbols (char*)
 */
char* first_set_lookup(cfg_t* grammar, char symbol);

/**
 * @brief calculate FIRST(Z), as Z is a sequence of symbols.
 * 
 * @param grammar 
 * @param symbol_sequence 
 * @return FIRST(symbol_sequence) set as char*
 */
char* multiple_first_set_lookup(cfg_t* grammar, char*symbol_sequence);


/**
 * @brief FOLLOW(D) algorithm extract the first terminal after symbol D in right side of a production. FOLLOW(D) goes through every production trying it.
 * 
 * @param grammar 
 * @param symbol 
 * @return list of first terminals after a symbol. If
 */
char* follow_set_lookup(cfg_t* grammar, char symbol);

/**
 * @brief Using FIRST and FOLLOW algorithms, this function fill the LL Table.
 * 
 * @param table 
 * @param grammar 
 * @return 0 in success, 1 in fail.
 */
int predictive_insert(hash_table_t *table, cfg_t* grammar);