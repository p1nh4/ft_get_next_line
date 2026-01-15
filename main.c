/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidos- <davidos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:33:43 by davidos-          #+#    #+#             */
/*   Updated: 2026/01/15 12:46:34 by davidos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (1);
		line = get_next_line(fd);
		while (line != ((void *)0))
		{
			printf("%s", line);
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
		return (0);
	}
}
