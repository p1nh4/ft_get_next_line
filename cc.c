/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidos- <davidos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:21:32 by davidos-          #+#    #+#             */
/*   Updated: 2026/01/21 18:55:40 by davidos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*ptr_s;
	size_t	len_s;
	size_t	i;

	len_s = ft_strlen(s) + 1;
	ptr_s = malloc(len_s * sizeof(char));
	if (!ptr_s)
		return (NULL);
	i = 0;
	while (i < len_s)
	{
		ptr_s[i] = s[i];
		i++;
	}
	return (ptr_s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr_s;
	size_t	len_s;
	size_t	i;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		len = 0;
	else if (len > (len_s - start))
		len = (len_s - start);
	ptr_s = malloc((len + 1) * sizeof(char));
	if (!ptr_s)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		ptr_s[i] = s[start + i];
		i++;
	}
	ptr_s[i] = '\0';
	return (ptr_s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*concat_s;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	concat_s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!concat_s)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		concat_s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		concat_s[i + j] = s2[j];
		j++;
	}
	concat_s[i + j] = '\0';
	return (concat_s);
}
