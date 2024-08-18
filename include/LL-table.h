#pragma once

#define HASH_TABLE_SIZE 100

/**
 * @brief Context Free Grammar Productions
 * 
 */
typedef struct cfg_production cfg_production_t;

typedef struct cfg_production
{
    char right_side;
    char *left_side; //with no spaces, please
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

typedef struct hash_entry {
    char *key; // A chave é uma combinação de símbolo não-terminal e terminal
    char *value; // Valor é a produção associada
    struct hash_entry *next; // tratamento de colisões
} hash_entry_t;

typedef struct {
    hash_entry_t **table; // Tabela hash
} hash_table_t;

/**
 * @brief List all first terminal symbols on all productions with a specific right side symbol.
 * 
 * @param grammar Corresponding grammar with all productions
 * @param symbol right-side symbol from productions you want to list
 * @return list of first terminal symbols (char*)
 */
char* first_set_lookup(cfg_t* grammar, char symbol);

char* follow_set_lookup(cfg_t* grammar, char symbol);

// Função de hash 
unsigned int hash(const char *key);

// Cria uma nova tabela hash
hash_table_t *create_hash_table(void);

// Insere uma nova entrada na tabela hash
void hash_table_insert(hash_table_t *table, const char *key, const char *value);

// Busca um valor na tabela hash
char *hash_table_lookup(hash_table_t *table, const char *key);

// Libera a memória da tabela hash
void free_hash_table(hash_table_t *table);

/**
 * @brief Using FIRST and FOLLOW algorithms, this function fill the LL Table.
 * 
 * @param table 
 */
void predictive_insert(hash_table_t *table);