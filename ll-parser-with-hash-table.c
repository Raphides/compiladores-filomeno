#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
unsigned int hash(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % HASH_TABLE_SIZE;
}

// Cria uma nova tabela hash
hash_table_t *create_hash_table() {
    hash_table_t *new_table = (hash_table_t *)malloc(sizeof(hash_table_t));
    new_table->table = (hash_entry_t **)malloc(sizeof(hash_entry_t *) * HASH_TABLE_SIZE);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        new_table->table[i] = NULL;
    }
    return new_table;
}

// Insere uma nova entrada na tabela hash
void hash_table_insert(hash_table_t *table, const char *key, const char *value) {
    unsigned int index = hash(key);
    hash_entry_t *new_entry = (hash_entry_t *)malloc(sizeof(hash_entry_t));
    new_entry->key = strdup(key);
    new_entry->value = strdup(value);
    new_entry->next = table->table[index];
    table->table[index] = new_entry;
}

// Busca um valor na tabela hash
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

// Libera a memória da tabela hash
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

typedef struct node_t {
    char symbol;
    struct node_t *next;
} node_t;

typedef struct {
    unsigned int length;
    node_t *top;
} stack_t;

stack_t *stack_create(void);
void stack_push(stack_t* stack, char symbol);
void stack_push_sequence(stack_t* stack, char *string);
int stack_pull(stack_t* stack);
char stack_check(stack_t* stack);
void free_all_stack(stack_t* stack);

stack_t *stack_create(void) {
    stack_t *new_stack = (stack_t*) malloc(sizeof(stack_t));
    new_stack->length = 0;
    new_stack->top = NULL;
    return new_stack;
}

void stack_push(stack_t* stack, char symbol) {
    node_t *new_node = (node_t*) malloc(sizeof(node_t));
    new_node->symbol = symbol;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->length++;
}

void stack_push_sequence(stack_t* stack, char *string) {
    int index = 0;
    while (string[index] != '\0') {
        stack_push(stack, string[index]);
        index++;
    }
}

int stack_pull(stack_t* stack) {
    if (stack->length <= 0) {
        return 1;
    } else {
        node_t* temp = stack->top->next;
        free(stack->top);
        stack->top = temp;
        stack->length--;
        return 0;
    }
}

char stack_check(stack_t* stack) {
    if (stack->top == NULL) {
        return '@';
    } else {
        return stack->top->symbol;
    }
}

void free_all_stack(stack_t* stack) {
    node_t *to_be_free, *temp;
    to_be_free = stack->top;
    while (to_be_free != NULL) {
        temp = to_be_free->next;
        free(to_be_free);
        to_be_free = temp;
    }
    free(stack);
}

char * reverse_string(char * original_string) {
    int str_index = 0;
    stack_t* string_stack = stack_create();
    while (original_string[str_index] != '\0') {
        stack_push(string_stack, original_string[str_index]);
        str_index++;
    }
    char *new_string = (char*) malloc((sizeof(char) * str_index) + 1);
    int new_string_index = 0;
    for (size_t i = 0; i < str_index; i++) {
        new_string[i] = stack_check(string_stack);
        stack_pull(string_stack);
    }
    new_string[str_index] = '\0';
    free_all_stack(string_stack);
    return new_string;
}

int ll_parser_algorithm(char const *input_string, hash_table_t *table) {
    int input_len = strlen(input_string);

    stack_t* derivation_tree_stack = stack_create();
    stack_push(derivation_tree_stack, 'S'); 

    char top_symbol; 
    char analysed_input_symbol; 
    int analysed_input_index = 0; 

    while (derivation_tree_stack->length != 0 || derivation_tree_stack->top != NULL) {
        analysed_input_symbol = input_string[analysed_input_index];
        top_symbol = stack_check(derivation_tree_stack);

        if (analysed_input_symbol == top_symbol) {
            analysed_input_index++;
            stack_pull(derivation_tree_stack);
            continue;
        } else {
            char key[4];
            snprintf(key, sizeof(key), "%c%c", top_symbol, analysed_input_symbol);

            char *production_to_be_added = hash_table_lookup(table, key);

            if (production_to_be_added == NULL) {
                return 1; 
            }
            
            stack_pull(derivation_tree_stack); 
            stack_push_sequence(derivation_tree_stack, reverse_string(production_to_be_added)); 
        }
    }
    return analysed_input_index == input_len ? 0 : 1;
}

int main(int argc, char const *argv[]) {
    hash_table_t *ll_table = create_hash_table();

    char non_terminal, terminal;
    char production[100];

    while (1) {
        printf("Digite a produção (ou 'fim' para encerrar):\n");
        printf("Símbolo não-terminal: ");
        scanf(" %c", &non_terminal);
        if (non_terminal == 'f') {
            // Verifica a próxima entrada para confirmar que o usuário deseja terminar
            char next_char;
            scanf(" %c", &next_char);
            if (next_char == 'i') { // Se o próximo caractere for 'i', assume que é "fim"
                break;
            }
        }
        
        printf("Símbolo terminal: ");
        scanf(" %c", &terminal);
        
        printf("Produção: ");
        scanf(" %s", production);
        
        char key[4];
        snprintf(key, sizeof(key), "%c%c", non_terminal, terminal);
        hash_table_insert(ll_table, key, production);
    }

    char input_string1[] = "(a+a)";
    if (ll_parser_algorithm(input_string1, ll_table) == 0) {
        printf("Input '%s' string valida.\n", input_string1);
    } else {
        printf("Input '%s' string invalida.\n", input_string1);
    }

    free_hash_table(ll_table);

    return 0;
}
