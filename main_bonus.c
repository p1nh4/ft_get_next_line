/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidos- <davidos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 22:43:07 by davidos-          #+#    #+#             */
/*   Updated: 2026/02/08 22:43:09 by davidos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		*fds;
	char	*line;
	int		i;
	int		files_left;

	if (argc < 2)
	{
		printf("Uso: ./gnl_bonus ficheiro1.txt ficheiro2.txt ...\n");
		return (1);
	}

	// Aloca array de file descriptors
	fds = malloc(sizeof(int) * (argc - 1));
	if (!fds)
		return (1);

	// Abre todos os ficheiros
	i = 0;
	while (i < argc - 1)
	{
		fds[i] = open(argv[i + 1], O_RDONLY);
		if (fds[i] < 0)
		{
			printf("Erro ao abrir %s\n", argv[i + 1]);
			free(fds);
			return (1);
		}
		i++;
	}

	// Lê de todos os ficheiros alternadamente
	files_left = argc - 1;
	while (files_left > 0)
	{
		i = 0;
		while (i < argc - 1)
		{
			if (fds[i] >= 0)
			{
				line = get_next_line(fds[i]);
				if (line != ((void *)0))
				{
					printf("%s", line);
					free(line);
				}
				else
				{
					close(fds[i]);
					fds[i] = -1;
					files_left--;
				}
			}
			i++;
		}
	}

	free(fds);
	return (0);
}
