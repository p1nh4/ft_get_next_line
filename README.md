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

O principal desafio deste projeto foi a **gestão de memória**, especialmente ao lidar com leituras
parciais e buffers residuais. Garantir que não existem memory leaks ao processar múltiplos file
descriptors e diferentes tamanhos de BUFFER_SIZE.

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

Compilar com get_next_line:
```bash
cc -D BUFFER_SIZE=42 seu_programa.c -L. -lget_next_line -o programa
# Bonus
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c -o gnl_bonus
```

**Exemplo de uso:**
```bash
# Ler um ficheiro
./gnl ficheiro.txt

# Ler múltiplos ficheiros (bonus)
./gnl_bonus ficheiro1.txt ficheiro2.txt ficheiro3.txt
```
Exemplo básico:
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Testes

**Usando Makefile:**
```bash
make test          # Executa teste mandatory
make test_bonus    # Executa teste bonus
```

**Compilação manual:**
```bash
# Teste mandatory com ficheiro específico
cc -D BUFFER_SIZE=42 -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c testes/test_main.c -o test_gnl
./test_gnl testes/multiple_lines.txt

# Teste bonus com múltiplos ficheiros
cc -D BUFFER_SIZE=42 -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c testes/test_bonus.c -o test_bonus
./test_bonus testes/empty.txt testes/long_line.txt
```

O projeto pode ser testado com vários BUFFER_SIZE:
```bash
cc -D BUFFER_SIZE=1 ...     # Teste stress (leitura byte a byte)
cc -D BUFFER_SIZE=42 ...    # Valor padrão
cc -D BUFFER_SIZE=9999 ...  # Buffer grande
```

Ficheiros de teste incluídos:
- `empty.txt` - Ficheiro vazio
- `single_line.txt` - Uma linha sem newline
- `single_line_nl.txt` - Uma linha com newline
- `multiple_lines.txt` - Múltiplas linhas
- `only_nl.txt` - Apenas newlines
- `long_line.txt` - Linha muito longa
- `mixed.txt` - Linhas mistas (com/sem newline)
- `special_chars.txt` - Caracteres especiais

**Testers externos:**
- OK [gnlTester](https://github.com/Tripouille/gnlTester)
- OK [gnl-station-tester](https://github.com/kodpe/gnl-station-tester)
- OK [42TESTERS-GNL](https://github.com/Mazoise/42TESTERS-GNL)

## Resources

### Documentação

Recursos de referência disponíveis em `/docs/resources.md`:

### Uso de IA

AI foi usado como assistente de aprendizagem para:
- Explicar o funcionamento de conceitos e exemplos da documentacao
- Debugging de memory leaks com Valgrind (double frees, invalid reads)
- Compreender edge cases (EOF sem newline, ficheiros vazios, BUFFER_SIZE = 1)
- Clarificação sobre gestão de múltiplos file descriptors no bonus
- Validação de conformidade com a norminette e testes

## Features

### Funções Obrigatórias
- `get_next_line(int fd)` - Retorna a próxima linha do file descriptor, incluindo o `\n`
  - Retorna `NULL` quando chega ao fim do ficheiro ou em caso de erro
  - Usa buffer estático para preservar dados entre chamadas
  - Funciona com qualquer BUFFER_SIZE definido em compilação

### Funcionalidades Bonus
- **Múltiplos file descriptors**: Suporta leitura simultânea de vários ficheiros
  - Usa array estático `buffer[OPEN_MAX]` para manter estado de cada fd
  - Cada file descriptor mantém o seu próprio buffer independente
  - Permite alternar entre ficheiros sem perder o progresso de leitura

## Algorithm and Data Structure

### Algoritmo Principal

A implementação usa **variáveis estáticas** e um **ciclo de leitura incremental**:

1. **Inicialização** (`get_next_line`):
   - Valida parâmetros (fd >= 0, BUFFER_SIZE > 0)
   - Buffer estático preserva conteúdo residual de chamadas anteriores
   - **Versão bonus**: Array estático `buffer[OPEN_MAX]` permite múltiplos fd

2. **Fase de Leitura** (`ft_read_file`):
   - Lê BUFFER_SIZE bytes de cada vez com `read()`
   - Concatena ao buffer existente usando `ft_strjoin`
   - **Condição de paragem**: Encontra `\n` OU `read()` retorna 0 (EOF)
   - Liberta memória temporária a cada iteração

3. **Extração de Linha** (`ft_get_line`):
   - Calcula tamanho até `\n` ou fim da string
   - Aloca espaço suficiente (tamanho + `\n` + `\0`)
   - Copia caracteres incluindo `\n` se presente

4. **Atualização de Buffer** (`ft_update_buff`):
   - Localiza posição do `\n` com `ft_strchr`
   - Cria novo buffer com conteúdo **após** o `\n`
   - Liberta buffer antigo
   - Retorna `NULL` se não houver conteúdo residual

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

- **Variável estática**:
  - Escolhida para preservar dados residuais entre chamadas sucessivas
  - Permite que cada chamada continue de onde a anterior parou
  - Mantém estado sem necessidade de estrutura externa

- **Array estático no bonus**:
  - Cada índice corresponde a um file descriptor (buffer[fd])
  - Permite gestão independente de múltiplos ficheiros
  - OPEN_MAX garante espaço para todos os fd possíveis no sistema

- **Leitura incremental (BUFFER_SIZE)**:
  - Evita carregar ficheiros inteiros na memória
  - Funciona com qualquer tamanho de ficheiro
  - Performance ajustável via BUFFER_SIZE em compilação

- **Libertação progressiva**:
  - `ft_join_and_free` liberta buffer antigo após concatenação
  - `ft_update_buff` liberta buffer após extrair linha
  - Previne memory leaks mesmo em leituras longas

- **Gestão de edge cases**:
  - EOF sem `\n` → Retorna última linha
  - Ficheiro vazio → Retorna `NULL`
  - Erro de `read()` → Liberta memória e retorna `NULL`
  - BUFFER_SIZE = 1 → Funciona (leitura byte a byte)

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
