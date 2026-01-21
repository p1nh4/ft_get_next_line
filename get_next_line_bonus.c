/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidos- <davidos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:20:56 by davidos-          #+#    #+#             */
/*   Updated: 2026/01/21 20:49:27 by davidos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free_and_return(char *buffer, char *temp);
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
	buffer[fd] = ft_update_buff(buffer[fd]);
	return (line);
}

char	*ft_join_and_free(char *buffer, char *temp)
{
	char	*new_buffer;

	new_buffer = ft_strjoin(buffer, temp);
	free(buffer);
	return (new_buffer);
}

char	*ft_read_file(int fd, char *buffer)
{
	int		nb_read;
	char	*temp;

	if (!buffer)
		buffer = ft_strdup("");
	temp = malloc((BUFFER_SIZE + 1));
	if (!temp)
		return ((void *)0);
	nb_read = 1;
	while (nb_read && !ft_strchr(buffer, '\n'))
	{
		nb_read = read(fd, temp, BUFFER_SIZE);
		if (nb_read < 0)
			return (free(buffer), free(temp), ((void *)0));
		temp[nb_read] = '\0';
		buffer = ft_join_and_free(buffer, temp);
		if (!buffer)
			return (free(temp), ((void *)0));
	}
	free(temp);
	if (!buffer || !buffer[0])
		return (free(buffer), (void *)0);
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
	line = malloc(size + 2);
	if (!line)
		return ((void *)0);
	size = 0;
	while (buffer[size] && buffer[size] != '\n')
	{
		line[size] = buffer[size];
		size++;
	}
	if (buffer[size] == '\n')
		line[size++] = '\n';
	line[size] = '\0';
	return (line);
}

char	*ft_update_buff(char *buffer)
{
	char	*new_buffer;
	char	*posit_newline;

	posit_newline = ft_strchr(buffer, '\n');
	if (!posit_newline)
		return (free(buffer), (void *)0);
	if (!posit_newline[1])
		return (free(buffer), ((void *)0));
	new_buffer = ft_strdup(posit_newline + 1);
	free(buffer);
	return (new_buffer);
}
