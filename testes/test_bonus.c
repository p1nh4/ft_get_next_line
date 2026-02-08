/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidos- <davidos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 22:51:49 by davidos-          #+#    #+#             */
/*   Updated: 2026/02/08 22:54:41 by davidos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

void	test_two_files(void)
{
	int		fd1, fd2;
	char	*line1, *line2;

	printf("\n--- Teste 1: Dois ficheiros alternados ---\n");
	fd1 = open("testes/multiple_lines.txt", O_RDONLY);
	fd2 = open("testes/mixed.txt", O_RDONLY);

	if (fd1 < 0 || fd2 < 0)
	{
		printf("ERRO: Não consegui abrir ficheiros\n");
		return ;
	}

	// Lê alternadamente 3 vezes
	line1 = get_next_line(fd1);
	printf("FD1[1]: %s", line1);
	free(line1);

	line2 = get_next_line(fd2);
	printf("FD2[1]: %s", line2);
	free(line2);

	line1 = get_next_line(fd1);
	printf("FD1[2]: %s", line1);
	free(line1);

	line2 = get_next_line(fd2);
	printf("FD2[2]: %s", line2);
	free(line2);

	line1 = get_next_line(fd1);
	printf("FD1[3]: %s", line1);
	free(line1);

	line2 = get_next_line(fd2);
	printf("FD2[3]: %s", line2);
	free(line2);

	close(fd1);
	close(fd2);
	printf("OK: Conseguiu ler de 2 FDs alternadamente\n");
}

void	test_three_files(void)
{
	int		fd1, fd2, fd3;
	char	*line;

	printf("\n--- Teste 2: Três ficheiros ---\n");
	fd1 = open("testes/single_line.txt", O_RDONLY);
	fd2 = open("testes/single_line_nl.txt", O_RDONLY);
	fd3 = open("testes/multiple_lines.txt", O_RDONLY);

	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
	{
		printf("ERRO: Não consegui abrir ficheiros\n");
		return ;
	}

	// Lê de cada um
	line = get_next_line(fd1);
	printf("FD1: %s\n", line);
	free(line);

	line = get_next_line(fd2);
	printf("FD2: %s", line);
	free(line);

	line = get_next_line(fd3);
	printf("FD3: %s", line);
	free(line);

	// Segunda volta
	line = get_next_line(fd1);
	if (line == ((void *)0))
		printf("FD1: NULL (correto - ficheiro terminou)\n");

	line = get_next_line(fd2);
	if (line == ((void *)0))
		printf("FD2: NULL (correto - ficheiro terminou)\n");

	line = get_next_line(fd3);
	printf("FD3: %s", line);
	free(line);

	close(fd1);
	close(fd2);
	close(fd3);
	printf("OK: Conseguiu ler de 3 FDs\n");
}

void	test_many_fds(void)
{
	int		fds[5];
	char	*line;
	int		i;

	printf("\n--- Teste 3: Cinco ficheiros (stress test) ---\n");

	// Abre 5 vezes o mesmo ficheiro
	i = 0;
	while (i < 5)
	{
		fds[i] = open("testes/multiple_lines.txt", O_RDONLY);
		if (fds[i] < 0)
		{
			printf("ERRO: Não consegui abrir FD %d\n", i);
			return ;
		}
		i++;
	}

	// Lê primeira linha de cada um
	i = 0;
	while (i < 5)
	{
		line = get_next_line(fds[i]);
		printf("FD[%d]: %s", i, line);
		free(line);
		i++;
	}

	// Fecha todos
	i = 0;
	while (i < 5)
	{
		close(fds[i]);
		i++;
	}

	printf("OK: Conseguiu gerir 5 FDs simultaneamente\n");
}

int	main(void)
{
	printf("==============================================\n");
	printf("     TESTES GET_NEXT_LINE BONUS\n");
	printf("     (Múltiplos File Descriptors)\n");
	printf("     BUFFER_SIZE = %d\n", BUFFER_SIZE);
	printf("==============================================\n");

	test_two_files();
	test_three_files();
	test_many_fds();

	printf("\n==============================================\n");
	printf("TESTES BONUS CONCLUÍDOS!\n");
	printf("Se viste as linhas corretas, funciona!\n");
	printf("Verifica memory leaks:\n");
	printf("  valgrind --leak-check=full ./test_bonus\n");
	printf("==============================================\n\n");

	return (0);
}
