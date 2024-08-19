#pragma once

#define HASH_TABLE_SIZE 100

typedef struct hash_entry {
    char *key; // A chave é uma combinação de símbolo não-terminal e terminal
    char *value; // Valor é a produção associada
    struct hash_entry *next; // tratamento de colisões
} hash_entry_t;

typedef struct {
    hash_entry_t **table; // Tabela hash
} hash_table_t;



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
