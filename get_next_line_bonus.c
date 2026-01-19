/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidos- <davidos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:20:56 by davidos-          #+#    #+#             */
/*   Updated: 2026/01/19 17:02:41 by davidos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*ft_read_file(int fd, char *buffer);
char	*ft_get_line(char *buffer);
char	*ft_update_buff(char *buffer);
char	*get_next_line(int fd);

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE < 1)
		return ((void *)0);
	buffer[fd] = ft_read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return ((void *)0);
	line = ft_get_line(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = ((void *)0);
		return ((void *)0);
	}
	buffer[fd] = ft_update_buff(buffer[fd]);
	return (line);
}

char	*ft_read_file(int fd, char *buffer)
{
	int		nb_read;	
	char	*temp;
	char	*ptr_buff;

	nb_read = 1;
	temp = malloc((BUFFER_SIZE + 1));
	if (!temp)
		return ((void *)0);
	if (!buffer)
	{
		buffer = ft_strdup("");
		if (!buffer)
		{
			free(temp);
			return ((void *)0);
		}
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
		{
			free(ptr_buff);
			free(temp);
			return ((void *)0);
		}
		free(ptr_buff);
	}
	free(temp);
	if (nb_read < 0)
	{
		free(buffer);
		return ((void *)0);
	}
	if (buffer[0] == '\0')
	{
		free(buffer);
		return ((void *)0);
	}
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
	if (buffer[size] == '\n')
		line = malloc(sizeof(char) * (size + 2));
	else
		line = malloc(sizeof(char) * (size + 1));
	if (!line)
		return ((void *)0);
	ft_strlcpy(line, buffer, size + 1);
	if (buffer[size] == '\n')
	{
		line[size] = '\n';
		line[++size] = '\0';
	}
	return (line);
}

char	*ft_update_buff(char *buffer)
{
	char	*temp;
	char	*ptr_buff;
	int		size;

	if (!buffer)
		return ((void *)0);
	temp = ft_strchr(buffer, '\n');
	if (!temp)
	{
		free(buffer);
		return ((void *)0);
	}
	else
		size = (temp - buffer) + 1;
	if (!buffer[size])
	{
		free(buffer);
		return ((void *)0);
	}
	ptr_buff = ft_substr(buffer, size, ft_strlen(buffer) - size);
	free(buffer);
	return (ptr_buff);
}
