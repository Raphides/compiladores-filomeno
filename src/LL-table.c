#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "LL-table.h"


unsigned int hash(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % HASH_TABLE_SIZE;
}

hash_table_t *create_hash_table(void) {
    hash_table_t *new_table = (hash_table_t *)malloc(sizeof(hash_table_t));
    new_table->table = (hash_entry_t **)malloc(sizeof(hash_entry_t *) * HASH_TABLE_SIZE);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        new_table->table[i] = NULL;
    }
    return new_table;
}

void hash_table_insert(hash_table_t *table, const char *key, const char *value) {
    unsigned int index = hash(key);
    hash_entry_t *new_entry = (hash_entry_t *)malloc(sizeof(hash_entry_t));
    new_entry->key = strdup(key);
    new_entry->value = strdup(value);
    new_entry->next = table->table[index];
    table->table[index] = new_entry;
}

char *hash_table_lookup(hash_table_t *table, const char *key) {
    unsigned int index = hash(key);
    hash_entry_t *entry = table->table[index];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

void free_hash_table(hash_table_t *table) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hash_entry_t *entry = table->table[i];
        while (entry != NULL) {
            hash_entry_t *prev = entry;
            entry = entry->next;
            free(prev->key);
            free(prev->value);
            free(prev);
        }
    }
    free(table->table);
    free(table);
}

char* first_set_lookup(cfg_t* grammar, char symbol)
{
    char *result_array = "";

    if (strchr(grammar->terminals, symbol) || (symbol == '$'))
    {
        result_array = "\0\0";
        result_array[0] = symbol; 
        return result_array;
    }
    
    cfg_production_t *actual_production = grammar->first_production;
    
    do {
        if (actual_production->left_side == symbol)
        {
            strcat(result_array, first_set_lookup(grammar, actual_production));
        }
        actual_production = actual_production->next_production;
    } while (actual_production == NULL);
    
    return result_array;
}

char* follow_set_lookup(cfg_t* grammar, char symbol);