/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidos- <davidos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:21:46 by davidos-          #+#    #+#             */
/*   Updated: 2026/01/11 14:44:26 by davidos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef	GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>

# define BUFFER_SIZE 42

char	*get_next_line(int fd);

#endif

