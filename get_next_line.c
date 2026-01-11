/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidos- <davidos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:20:56 by davidos-          #+#    #+#             */
/*   Updated: 2026/01/11 17:29:40 by davidos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			nb_read;	//number bytes read
	char		*str;
	static char	buffer[BUFFER_SIZE + 1];

	nb_read = read(fd, buffer, BUFFER_SIZE);
	if (nb_read == -1)
		return ;
	buffer[nb_read] = '\0';
	return (str);
}
