# Como executar os testes

## test_stack.c
```bash
gcc -Iinclude/ src/stack.c test/test_stack.c -o bin/test_stack.o
```

## test_LL_table.c


## test_LL_parser_with_LL_table_as_vector.c
É o teste da implementação do LL Parser, mas:
* sem a implementação do algorítmo da LL Table 
* sem a struct e funções de tabela/dicionário da LL Table. Ao invés disso, usa-se um vetor `char ***`.

Para isso, parte da função ll_parse foi alterada. Por isso, no arquivo de teste, há novamente a definição do ll_parse.

Para compilá-lo via linha de comando:
```bash
gcc -Iinclude/ src/stack.c test/test_LL_parser_with_LL_table_as_vector.c
```

Para executá-lo via Debug do VSCODE:
1. vá nas primeiras linhas do código, troque `#include "stack.h"` por `#include "stack.c"`;
2. Vá no arquivo `test/test_LL_parser_with_LL_table_as_vector.c` e clique em "Depurar Arquivo C/C++".


## test_LL_parser.c



