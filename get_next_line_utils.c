/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidos- <davidos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:21:32 by davidos-          #+#    #+#             */
/*   Updated: 2026/01/15 15:55:37 by davidos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i) != '\0')
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*s_dest;
	const unsigned char	*s_src;

	if (!src && !dest)
		return ((void *)0);
	if (n == 0 && dest == src)
		return (dest);
	s_dest = (unsigned char *)dest;
	s_src = (const unsigned char *)src;
	while (n > 0)
	{
		*s_dest++ = *s_src++;
		n--;
	}
	return (dest);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	s_len;

	s_len = ft_strlen(src);
	if (s_len >= size)
		len = size - 1;
	else
		len = s_len;
	if (size)
	{
		ft_memcpy(dst, src, len);
		dst[len] = '\0';
	}
	return (s_len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	if (size <= d_len)
		return (size + s_len);
	size = (size - d_len) - 1;
	if (s_len < size)
		size = s_len;
	ft_memcpy(dst + d_len, src, size);
	dst[d_len + size] = '\0';
	return (d_len + s_len);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *) &s[i]);
	return ((void *)0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr_s;
	size_t	len_s;

	len_s = ft_strlen(s);
	if (start >= len_s)
		len = 0;
	else if (len > (len_s - start))
		len = (len_s - start);
	ptr_s = malloc((len + 1) * sizeof(char));
	if (!ptr_s)
		return ((void *)0);
	if (start < len_s)
		s += start;
	ft_strlcpy(ptr_s, s, (len + 1));
	return (ptr_s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*concat_s;
	size_t	len_s;

	if (!s1 || !s2)
		return ((void *)0);
	len_s = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	concat_s = malloc(len_s * sizeof(char));
	if (!concat_s)
		return ((void *)0);
	ft_strlcpy(concat_s, s1, len_s);
	ft_strlcat(concat_s, s2, len_s);
	return (concat_s);
}
