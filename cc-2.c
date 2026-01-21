i/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cc-2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidos- <davidos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:20:56 by davidos-          #+#    #+#             */
/*   Updated: 2026/01/21 18:56:05 by davidos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free_and_return(char *buffer, char *temp)
{
	free(buffer);
	free(temp);
	return (NULL);
}

char	*ft_read_file(int fd, char *buffer)
{
	int		nb_read;
	char	*temp;
	char	*ptr_buff;

	nb_read = 1;
	if (!buffer)
		buffer = ft_strdup("");
	if (!buffer)
		return (NULL);
	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	while (nb_read && !ft_strchr(buffer, '\n'))
	{
		nb_read = read(fd, temp, BUFFER_SIZE);
		if (nb_read < 0)
			return (ft_free_and_return(buffer, temp));
		temp[nb_read] = '\0';
		ptr_buff = buffer;
		buffer = ft_strjoin(buffer, temp);
		free(ptr_buff);
		if (!buffer)
			return (ft_free_and_return(NULL, temp));
	}
	free(temp);
	if (buffer[0] == '\0')
		return (free(buffer), NULL);
	return (buffer);
}

char	*ft_get_line(char *buffer)
{
	char	*line;
	size_t	size;
	size_t	i;

	if (!buffer)
		return (NULL);
	size = 0;
	while (buffer[size] && buffer[size] != '\n')
		size++;
	if (buffer[size] == '\n')
		line = malloc(sizeof(char) * (size + 2));
	else
		line = malloc(sizeof(char) * (size + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < size)
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[size] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_update_buff(char *buffer)
{
	char	*temp;
	char	*ptr_buff;
	int		size;

	if (!buffer)
		return (NULL);
	temp = ft_strchr(buffer, '\n');
	if (!temp)
	{
		free(buffer);
		return (NULL);
	}
	size = (temp - buffer) + 1;
	if (!buffer[size])
	{
		free(buffer);
		return (NULL);
	}
	ptr_buff = ft_substr(buffer, size, ft_strlen(buffer) - size);
	free(buffer);
	return (ptr_buff);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = ft_read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = ft_update_buff(buffer);
	return (line);
}
