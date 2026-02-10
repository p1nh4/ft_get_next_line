Resources & References

---

System & OS Concepts

-File descriptors
- [What are file descriptors - Stack Overflow](https://stackoverflow.com/questions/5256599/what-are-file-descriptors-explained-in-simple-terms)
- [What is special about /dev/tty](https://stackoverflow.com/questions/8514735/what-is-special-about-dev-tty)
- [Handling a file by its descriptor in C](https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/)
- [File descriptor - Stack Overflow](https://stackoverflow.com/questions/40864527/what-is-file-descriptor)

-System calls
- [I/O System Calls in C - GeeksforGeeks](https://www.geeksforgeeks.org/c/input-output-system-calls-c-create-open-close-read-write/)
- [Read - br-c.org](https://www.br-c.org/doku.php?id=read)

-Limits & Configuration
- [Limits on number of file descriptors](https://unix.stackexchange.com/questions/84227/limits-on-the-number-of-file-descriptors)
- [Aumentando limite de file descriptors](https://www.sartori.eti.br/2011/03/aumentando-o-limite-de-file-descriptors.html)

---

Memory management

-stack vs heap
- [Heap memoria - Google Search](https://www.google.com/search?q=heap+memoria&client=ubuntu-sn&hs=oop&sca_esv=b9caa2c9e6274683&channel=fs&sxsrf=ANbL-n5awZ3WPUc9N5lBsRTJ1WaKLeua9g%3A1768335641841&ei=GalmaamJM7bni-gP7PzHwQQ&oq=heap&gs_lp=Egxnd3Mtd2l6LXNlcnAiBGhlYXAqAggAMgcQIxiwAxgnMgoQABiwAxjWBBhHMgoQABiwAxjWBBhHMgoQABiwAxjWBBhHMgoQABiwAxjWBBhHMgoQABiwAxjWBBhHMgoQABiwAxjWBBhHMgoQABiwAxjWBBhHMgoQABiwAxjWBBhHMg0QABiABBiwAxhDGIoFSLENUABYAHACeAGQAQCYAQCgAQCqAQC4AQPIAQCYAgKgAiaYAwCIBgGQBgqSBwEyoAcAsgcAuAcAwgcDMy0yyAcdgAgA&sclient=gws-wiz-serp)
- [Stack memoria - Google Search](https://www.google.com/search?q=stack+memoria&client=ubuntu-sn&hs=H9U&sca_esv=b9caa2c9e6274683&channel=fs&sxsrf=ANbL-n7uoonYZeW8OZTvZDRSa6sGIIutpQ%3A1768335627450&ei=C6lmae6aG8zsi-gPkqqegAs&ved=0ahUKEwiuzKvHq4mSAxVM9gIHHRKVB7AQ4dUDCBE&uact=5&oq=stack+memoria&gs_lp=Egxnd3Mtd2l6LXNlcnAaAhgCIg1zdGFjayBtZW1vcmlhMgUQABiABDIGEAAYFhgeMgYQABgWGB4yBhAAGBYYHjIGEAAYFhgeMggQABgWGAoYHjIIEAAYFhgKGB4yBhAAGBYYHjIGEAAYFhgeMgYQABgWGB5I6w5QigJY8g1wAXgBkAEAmAG7AaAB0weqAQMxLje4AQPIAQD4AQGYAgmgAo4JwgINECMY8AUYsAMYJxjJAsICChAAGLADGNYEGEfCAg0QABiABBiwAxhDGIoFwgIcECMY8AUYgAQYpgMYJxj4BRioAxjJAhiKBRiLA8ICChAAGIAEGEMYigXCAhcQLhiABBjRAxjSAxjHARioAxjLARiLA8ICCBAAGIAEGMsBwgIJEAAYgAQYChgLmAMAiAYBkAYKkgcFMS43LjGgB74xsgcFMC43LjG4B_UIwgcFMy04LjHIB40BgAgA&sclient=gws-wiz-serp)

-static variables
- [Variáveis estáticas - UFPR](https://www.inf.ufpr.br/hexsel/ci067/10_aloc.html)
- [Static variables explained - YouTube](https://www.youtube.com/watch?v=ji1dq8cklyU)

**Conceito:** Variáveis locais podem ser criadas como estáticas adicionando `static` na declaração.
Têm escopo local (visíveis apenas na função), mas são alocadas no início do programa e liberadas apenas no final.
O conteúdo é preservado entre chamadas de funções.

-malloc & buffers
- [char buf malloc vs array](https://stackoverflow.com/questions/9510794/char-buf-mallocsizeof-char-16-vs-char-buf-sizeof-char-16)
- [sizeof with malloc buffer](https://stackoverflow.com/questions/40140104/how-to-utilize-sizeof-to-return-the-size-of-malloc-buffer-allocation)
- [Buffer initialization buffer[100] = {0}](https://stackoverflow.com/questions/16141991/how-does-the-initialization-using-buffer100-0-work-in-c-language)
- [Why malloc(1) works for 4-byte integers](https://stackoverflow.com/questions/41822904/why-does-malloc1-work-for-storing-4-byte-integers)

---

Build Tools

Makefile
- [Variable flavors in Makefile](https://www.gnu.org/software/make/manual/html_node/Flavors.html#Flavors)

**Notas:**
= (recursively expanded) - expande toda vez que é usada, lê sempre os valores mais recentes.
Permite redefinir e usar ifeq para modificar valores

:= (simply expanded) - expande uma vez na atribuição, mais rápida.
A ordem das variáveis importa (se inverteres pode dar erro porque variável ainda não existe)

---

Compilation
**Exemplo de compilação:**
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl_test
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c -o gnl_bonus
```

Testes
 - `empty.txt` - Ficheiro vazio
- `single_line.txt` - Uma linha sem newline
- `single_line_nl.txt` - Uma linha com newline
- `multiple_lines.txt` - Múltiplas linhas
- `only_nl.txt` - Apenas newlines
- `long_line.txt` - Linha muito longa
- `mixed.txt` - Linhas mistas (com/sem newline)
- `special_chars.txt` - Caracteres especiais

---

I/O Operations

-read & file operations
- [Read file and print buffer](https://stackoverflow.com/questions/34099377/c-read-file-and-print-buffer)
- [Handling files by descriptor](https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/)

-getLine & streams (fluxos)
- [getline man page](https://man7.org/linux/man-pages/man3/getline.3.html)
- [getline string C++](https://www.geeksforgeeks.org/cpp/getline-string-c/)
- [Stream programming](https://www.google.com/search?q=stream+programming&sxsrf=ANbL-n4RP5hlnHRQN6_XttkXkM68pRtDgA%3A1768081908867)
- [W3C getline.c implementation](https://www.w3.org/Library/src/vms/getline.c)
- [digilus getline implementation](https://github.com/digilus/getline/blob/master/getline.c)

-general I/O
- [Detecting newline in C](https://stackoverflow.com/questions/46598518/detecting-new-line-in-c)
- [Get next line from file](https://stackoverflow.com/questions/6216292/how-do-i-get-the-next-line-from-a-file)
- [Read next line every function call](https://stackoverflow.com/questions/26267449/read-the-next-line-of-a-file-every-time-a-function-is-called)
- [Read next line in text file](https://stackoverflow.com/questions/65028904/how-to-read-the-next-line-in-a-text-file-in-c)
- [Implementing getchar issue](https://stackoverflow.com/questions/38211270/implementing-getchar-issue-in-c)

---

Project References GNL

-Implementações de Referência
- [Medium - GNL tutorial](https://medium.com/@lannur-s/gnl-c3cff1ee552b)
- [hector.dev.br - GNL tutorial](https://hector.dev.br/2021/08/27/GNL-get-next-line-42/)
- [jareste/get_next_line](https://github.com/jareste/get_next_line/blob/main/get_next_line.c)
- [devhector/42_GNL](https://github.com/devhector/42_GNL/blob/master/get_next_line.c)
- [clementvidon/get_next_line](https://github.com/clementvidon/get_next_line/blob/main/get_next_line.c)

-Stack Overflow Discussions
- [GNL implementation in C](https://stackoverflow.com/questions/58938219/get-next-line-implementation-in-c)
- [Creating a get_next_line function](https://stackoverflow.com/questions/35758649/creating-a-get-next-line-function-in-c)
- [GNL - read file and use array](https://stackoverflow.com/questions/56934840/my-question-is-about-get-next-line-function-l-am-supposed-to-read-a-file-and-us)
- [Writing getline function in C](https://stackoverflow.com/questions/31891095/writing-getline-function-in-c-language)




