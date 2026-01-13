/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidos- <davidos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:20:56 by davidos-          #+#    #+#             */
/*   Updated: 2026/01/13 19:12:01 by davidos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE < 1)
		return ((void *)0);
	buffer = ft_read_file(fd, buffer);
	if (!buffer)
		return ((void *)0);
	return (buffer);
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
	while (nb_read && !f_strchr(buffer, '\n'))
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
