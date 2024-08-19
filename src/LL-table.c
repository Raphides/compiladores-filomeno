#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

#include "hash_table.h"
#include "LL-table.h"


void __first_set_lookup_aux(cfg_t* grammar, char symbol, bool *has_empty_adress, char* dst)
{
    // if symbol is terminal
    if (strchr(grammar->terminals, symbol) != NULL)
    {
        char * result = "\0\0";
        result[0] = symbol;
        strcat(dst, result); 
        return;
    }
    else if (symbol == '#') //else if symbol is empty
    {
        *has_empty_adress = true;
        return;
    }
    
    cfg_production_t *actual_production = grammar->first_production;
    // symbol is not terminal
    do {
        if (actual_production->left_side == symbol)
        {
            // for each production as symbol -> rest:
            // FIRST(first_symbol of rest)
            strcat(dst, first_set_lookup(grammar, actual_production->right_side[0]));
        }
        actual_production = actual_production->next_production;
    } while (actual_production != NULL);
    
    return;
}

char* first_set_lookup(cfg_t* grammar, char symbol)
{
    char *result_array = (char*) calloc(50, sizeof(char));
    bool *has_empty = (bool*) malloc(sizeof(bool));
    *has_empty = false;

    __first_set_lookup_aux(grammar, symbol, has_empty, result_array);
    
    if (*has_empty == true)
    {
        strcat(result_array, "#");
    }
    free(has_empty);
    return result_array;
}

void __multiple_first_set_lookup_aux(cfg_t* grammar, char*symbol_sequence, int *empty_counter, char* dst)
{
    for (size_t k = 0; k < strlen(symbol_sequence); k++)
    {
        char *first_results = first_set_lookup(grammar, symbol_sequence[k]);

        if (strrchr(first_results, '#') != NULL)
        {
            *empty_counter = *empty_counter + 1;
        }
        strcat(dst, first_results);
        free(first_results);
    }
}

char* multiple_first_set_lookup(cfg_t* grammar, char*symbol_sequence)
{
    char *result_array = (char*) calloc(200, sizeof(char));
    int *empty_counter = (int*) malloc(sizeof(int));
    *empty_counter = 0;

    __multiple_first_set_lookup_aux(grammar, symbol_sequence, empty_counter, result_array);
    
    if (*empty_counter == strlen(symbol_sequence))
    {
        strcat(result_array, "#");
    }
    free(empty_counter);
    return result_array;
}


int __follow_aux(cfg_t* grammar, char symbol, cfg_production_t *actual_production, char *match, char* dst)
{
    // match = parcial string, starting from the symbol, ignoring what came before.
    if (match == NULL)
    {
        return 1;
    } 
    else
    {
        // FOLLOW(empty or EOF) = FOLLOW(left_side)
        if (match[1] == '#' || match[1] == '$')
        {
            char *tmp_follow_set = follow_set_lookup(grammar, actual_production->left_side);
            strcat(dst, tmp_follow_set);
            free(tmp_follow_set);
        }
        else
        {   // A -> BXC
            // FOLLOW(X) = FIRST(C)
            
            char *tmp_first_set = first_set_lookup(grammar, match[1]);
            strcat(dst, tmp_first_set);
            free(tmp_first_set);
        }
        __follow_aux(grammar, symbol, actual_production, strchr(match+1, symbol), dst); // returnables 0 or 1 are expected. 
        return 0;
    }
}

char* follow_set_lookup(cfg_t* grammar, char symbol)
{
    char *result_array = "";
    cfg_production_t *actual_production = grammar->first_production;
    do
    {
        __follow_aux(grammar, symbol, actual_production, strchr(actual_production->right_side, symbol),result_array);
        actual_production = actual_production->next_production;
    } while (actual_production != NULL);
    return result_array;
}


void __predictive_insert_aux(hash_table_t *table, cfg_t* grammar, cfg_production_t* selected_production)
{
    // consider B->A
    // FOLLOW(B)

    char *follow_set = follow_set_lookup(grammar, selected_production->left_side);
    
    // for each t in FOLLOW(B), insert production at [B, t]

    for (size_t follow_i = 0; follow_i < strlen(follow_set); follow_i++)
    {
        char key[4];
        snprintf(key, sizeof(key), "%c%c", selected_production->left_side, follow_set[follow_i]);

        hash_table_insert(table, key, selected_production->right_side);        
    }  
}

int predictive_insert(hash_table_t *table, cfg_t* grammar)
{
    if (grammar->first_production == NULL)
    {
        return 1;
    }

    // vars before loop
    
    cfg_production_t **productions_with_empty = (cfg_production_t**) malloc(sizeof(cfg_production_t*)*50);
    int productions_with_empty_i = 0;
    
    // for each production
    
    for (cfg_production_t* production = grammar->first_production; production->next_production != NULL; production = production->next_production)
    {
        // FIRST(right_side)
        
        char * first_set = multiple_first_set_lookup(grammar, production->right_side);
        
        // consider A = right_side and t = terminal
        // for each t at FIRST(A), insert production at table[A, t]
        
        for (size_t j = 0; j < strlen(first_set); j++)
        {
            // if terminal is empty(#), store production for later.
        
            if (first_set[j] == '#')
            {
                productions_with_empty[productions_with_empty_i] = production;
                productions_with_empty_i++;
            }
        
            // inserts at table[A, t] = production
        
            char key[4];
            snprintf(key, sizeof(key), "%c%c", production->left_side, first_set[j]);

            hash_table_insert(table, key, production->right_side);
        }
        
        // after all FIRSTs: for each t as empty, call auxiliary function
        
        for (size_t l = 0; l < productions_with_empty_i;l++)
        {
            __predictive_insert_aux(table, grammar, productions_with_empty[l]);
        }
        free(productions_with_empty);
        free(first_set);
        return 0;
    }
}