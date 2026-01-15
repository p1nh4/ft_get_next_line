/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidos- <davidos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:20:56 by davidos-          #+#    #+#             */
/*   Updated: 2026/01/15 14:52:05 by davidos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_read_file(int fd, char *buffer);
char	*get_next_line(int fd);
char	*ft_get_line(char *buffer);

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return ((void *)0);
	buffer = ft_read_file(fd, buffer);
	if (!buffer)
		return ((void *)0);
	line = ft_get_line(buffer);
	return (line);
}

char	*ft_read_file(int fd, char *buffer)
{
	int		nb_read;	//number bytes read of file descriptor
	char	*temp;
	char	*ptr_buff;

	nb_read = 1;
	temp = malloc((BUFFER_SIZE + 1));
	if (!temp)
		return ((void *)0);
	if (!buffer)
	{
		buffer = malloc(sizeof(char));
		if (!buffer)
			return ((void *)0);
		buffer[0] = '\0';
	}
	while (nb_read && !ft_strchr(buffer, '\n'))
	{
		nb_read = read(fd, temp, BUFFER_SIZE);
		if (nb_read < 0)
			break ;
		temp[nb_read] = '\0';
		ptr_buff = buffer;
		buffer = ft_strjoin(buffer, temp);
		if (!buffer)
			return ((void *)0);
		free(ptr_buff);
	}
	free(temp);
	if (nb_read < 0)
		return ((void *)0);
	else
		return (buffer);
}

char	*ft_get_line(char *buffer)
{
	char	*line;
	size_t	size;

	if (!buffer)
		return ((void *)0);
	size = 0;
	while (buffer[size] != '\0' && buffer[size] != '\n')
		size++;
	line = malloc(sizeof(char) * (size + 2));
	if (!line)
		return ((void *)0);
	ft_strlcpy(line, buffer, size + 1);
	if (buffer[size] == '\n')
		line[size] = '\n';
	line[++size] = '\0';
	return (line);
}
