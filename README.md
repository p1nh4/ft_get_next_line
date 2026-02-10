*Este projeto foi criado como parte do currículo da 42 por davidos-*

## Description
Uma implementação de função que lê uma linha de um file descriptor.

<p align="center">
  <img src="https://biriukov.dev/docs/fd-pipe-session-terminal/images/file-descriptor-open-file-description.png" alt="File Descriptor Diagram" width="600"/>
</p>

**get_next_line** é um projeto do currículo da Escola 42 que implementa uma função capaz de ler
uma linha de cada vez de um file descriptor. O objetivo é compreender conceitos de leitura de
ficheiros, gestão de memória dinâmica e variáveis estáticas em C.

O projeto está dividido em duas partes:
- **Obrigatória**: Implementa leitura básica linha a linha de um único file descriptor
- **Bonus**: Adiciona suporte para múltiplos file descriptors simultaneamente

O principal desafio deste projeto foi a gestão de memória, especialmente ao lidar com leituras
parciais e buffers e processar múltiplos file descriptors e diferentes tamanhos de BUFFER_SIZE.

## Instructions

### Compilação
```bash
git clone git@github.com:p1nh4/ft_get_next_line.git
cd get_next_line
make          # Compila mandatory
make bonus    # Compila com bonus
```

Outras regras:
- `make clean` - Remove ficheiros objeto
- `make fclean` - Remove objetos e biblioteca
- `make re` - Recompila do zero

### Uso

Usar no seu projeto:
```c
#include "get_next_line.h"
// Para bonus:
#include "get_next_line_bonus.h"
```
Compilar:
```bash
# Mandatory
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl

# Bonus
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

### Testes

**Usando Makefile:**
```bash
make test          # Executa teste mandatory
make test_bonus    # Executa teste bonus
```

**Compilação manual:**
```bash
# Mandatory
cc -D BUFFER_SIZE=42 -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c testes/test_main.c -o test_gnl
./test_gnl testes/multiple_lines.txt   # ou qualquer ficheiro.txt

# Bonus
cc -D BUFFER_SIZE=42 -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c testes/test_bonus.c -o test_bonus
./test_bonus testes/empty.txt testes/long_line.txt   # ou múltiplos ficheiros
```

Ver implementação completa em `testes/test_main.c` e `testes/test_bonus.c`.

O projeto pode ser testado com vários BUFFER_SIZE:
```bash
cc -D BUFFER_SIZE=<valor> ...
```

Ficheiros de teste incluídos:
O projeto inclui diversos ficheiros de teste em `testes/*.txt`.

**Testers externos:**
- [gnlTester](https://github.com/Tripouille/gnlTester)
- [gnl-station-tester](https://github.com/kodpe/gnl-station-tester)
- [42TESTERS-GNL](https://github.com/Mazoise/42TESTERS-GNL)

## Resources

### Documentação

Recursos de referência disponíveis em `/docs/resources.md`:

### Uso de IA

AI foi usado como assistente de aprendizagem para:
- Explicar o funcionamento de conceitos e exemplos da documentacao
- Debugging de memory leaks com Valgrind (double frees, invalid reads)
- Compreender edge cases (EOF sem newline, ficheiros vazios, BUFFER_SIZE = 1)
- Validação de conformidade com a norminette e testes

## Features

### Funções Obrigatórias
`get_next_line(int fd)` - Retorna próxima linha (com `\n`) ou `NULL` em EOF/erro.
Usa buffer estático para preservar estado entre chamadas, independente do BUFFER_SIZE.

### Funcionalidades Bonus
Suporta múltiplos file descriptors simultaneamente via array `buffer[OPEN_MAX]`,
permitindo alternar entre ficheiros sem perder progresso.

## Algorithm and Data Structure

### Algoritmo Principal

A implementação usa **variáveis estáticas** e um **ciclo de leitura incremental**:

1. **Validação** (`get_next_line`) - Verifica `fd >= 0` e `BUFFER_SIZE > 0`.
Buffer estático preserva dados entre chamadas (array `buffer[OPEN_MAX]` no bonus para múltiplos fd).

2. **Leitura** (`ft_read_file`) - Loop de `read()` em blocos de `BUFFER_SIZE`,
concatenando ao buffer até encontrar `\n` ou EOF. Liberta memória temporária a cada iteração.

3. **Extração** (`ft_get_line`) - Copia do buffer até `\n` (inclusive) ou fim da string
para nova linha alocada.

4. **Atualização** (`ft_update_buff`) - Localiza `\n` no buffer, cria novo buffer
apenas com conteúdo após o `\n`, liberta buffer antigo. Retorna `NULL` se não restar conteúdo.

### Estrutura de Dados

**Versão Mandatory:**
```c
static char *buffer;  // Preserva conteúdo entre chamadas
```

**Versão Bonus:**
```c
static char *buffer[OPEN_MAX];  // Um buffer por file descriptor
```

**Justificação das Escolhas:**

- **Variável estática** - Preserva dados residuais entre chamadas, permitindo continuar
de onde parou sem estruturas externas.

- **Array estático (bonus)** - Cada índice `buffer[fd]` corresponde a um file descriptor,
permitindo gestão independente de múltiplos ficheiros (até `OPEN_MAX` simultâneos).

- **Leitura incremental** - `BUFFER_SIZE` configurável evita carregar ficheiros inteiros
na memória (funciona de 1 byte até valores grandes).

- **Libertação progressiva** - `ft_join_and_free` liberta buffer antigo após concatenação,
`ft_update_buff` liberta buffer após extrair linha. Previne memory leaks em leituras longas.

- **Edge cases** - EOF sem `\n` retorna última linha, ficheiros vazios retornam `NULL`,
erros de `read()` libertam memória e retornam `NULL`, `BUFFER_SIZE = 1` funciona
(leitura byte a byte).

## Project Structure
```
get_next_line/
├── get_next_line.h              # Header mandatory
├── get_next_line_bonus.h        # Header bonus (com OPEN_MAX)
├── get_next_line.c              # Implementação mandatory
├── get_next_line_bonus.c        # Implementação bonus (array de buffers)
├── get_next_line_utils.c        # Funções auxiliares mandatory
├── get_next_line_utils_bonus.c  # Funções auxiliares bonus
├── docs/
│   └── resources.md             # Documentação e recursos de referência
├── testes/
│   ├── test_main.c              # Programa de teste mandatory
│   ├── test_bonus.c             # Programa de teste bonus
│   └── *.txt                    # Diversos ficheiros de teste
├── Makefile                     # Compilação (all, bonus, clean, fclean, re)
└── README.md
```

## Norm Compliance

Segue a [Norma 42](https://github.com/42School/norminette):
- ≤25 linhas/função, ≤5 funções/ficheiro
- Apenas funções autorizadas: `read`, `malloc`, `free`
- Gestão adequada de memória (sem leaks)
- Uma única variável estática por função
- Tratamento de erros (fd inválido, malloc failure, read error)

## Bom Código!
```c
#include <unistd.h>

int main(void)
{
    char *autor = "@p1nh4";
    write(1, autor, 6);
    return (0);
}
```
