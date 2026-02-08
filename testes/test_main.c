/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidos- <davidos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 22:48:56 by davidos-          #+#    #+#             */
/*   Updated: 2026/02/08 22:53:45 by davidos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void	test_file(char *filename)
{
	int		fd;
	char	*line;
	int		line_num;

	printf("\n--- Testando: %s ---\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("ERRO: Não consegui abrir o ficheiro\n");
		return ;
	}

	line_num = 1;
	line = get_next_line(fd);
	while (line != ((void *)0))
	{
		printf("Linha %d: %s", line_num, line);
		if (line[0] != '\n')
			printf("\n");
		free(line);
		line = get_next_line(fd);
		line_num++;
	}

	if (line_num == 1)
		printf("(ficheiro vazio ou só 1 linha sem newline)\n");

	close(fd);
	printf("OK: Ficheiro lido com sucesso\n");
}

void	test_invalid_fd(void)
{
	char	*line;

	printf("\n--- Testando: FD inválido ---\n");
	line = get_next_line(-1);
	if (line == ((void *)0))
		printf("OK: FD -1 retornou NULL\n");
	else
		printf("ERRO: FD -1 devia retornar NULL\n");

	line = get_next_line(9999);
	if (line == ((void *)0))
		printf("OK: FD 9999 retornou NULL\n");
	else
		printf("ERRO: FD 9999 devia retornar NULL\n");
}

int	main(void)
{
	printf("==============================================\n");
	printf("     TESTES GET_NEXT_LINE\n");
	printf("     BUFFER_SIZE = %d\n", BUFFER_SIZE);
	printf("==============================================\n");

	// Testa FDs inválidos
	test_invalid_fd();

	// Testa cada ficheiro
	test_file("testes/empty.txt");
	test_file("testes/single_line.txt");
	test_file("testes/single_line_nl.txt");
	test_file("testes/multiple_lines.txt");
	test_file("testes/long_line.txt");
	test_file("testes/only_nl.txt");
	test_file("testes/mixed.txt");
	test_file("testes/special_chars.txt");

	printf("\n==============================================\n");
	printf("TESTES CONCLUÍDOS!\n");
	printf("Verifica memory leaks:\n");
	printf("  valgrind --leak-check=full ./test_gnl\n");
	printf("==============================================\n\n");

	return (0);
}
