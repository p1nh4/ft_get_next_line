/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidos- <davidos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:21:32 by davidos-          #+#    #+#             */
/*   Updated: 2026/02/08 21:33:19 by davidos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Calcula o comprimento de uma string
 * 
 * Itera pela string contando caracteres até
 * encontrar o terminador null.
 * 
 * @param s String para medir
 * @return Comprimento da string, ou 0 se s for NULL
 * 
 * @note Retorna 0 para input NULL (tratamento seguro)
 */

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (*(s + i) != '\0')
		i++;
	return (i);
}

/**
 * @brief Localiza primeira ocorrência de caractere numa string
 * 
 * Procura a primeira ocorrência do caractere c (convertido para char)
 * na string s. O byte null terminador é considerado parte da string.
 * 
 * @param s String onde procurar
 * @param c Caractere a localizar (convertido para char)
 * @return Ponteiro para caractere encontrado, ou NULL se não encontrado
 * 
 * @note Retorna NULL se s for NULL
 * @note Verifica também o terminador null
 */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return ((void *)0);
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

/**
 * @brief Duplica uma string
 * 
 * Aloca memória e cria uma cópia da string de entrada,
 * incluindo o terminador null.
 * 
 * @param s String a duplicar
 * @return Ponteiro para nova string, ou NULL se alocação falhar
 * 
 * @note Quem chama deve libertar o ponteiro retornado
 * @note Copia toda a string incluindo terminador null
 */

char	*ft_strdup(const char *s)
{
	char	*ptr_s;
	size_t	len_s;
	size_t	i;

	len_s = ft_strlen(s) + 1;
	ptr_s = malloc(len_s * sizeof(char));
	if (!ptr_s)
		return ((void *)0);
	i = 0;
	while (i < len_s)
	{
		ptr_s[i] = s[i];
		i++;
	}
	return (ptr_s);
}

/**
 * @brief Extrai uma substring de uma string
 * 
 * Aloca e retorna uma substring da string s. A substring
 * começa no índice start e tem tamanho máximo len.
 * 
 * @param s String de onde extrair
 * @param start Índice inicial em s
 * @param len Comprimento máximo da substring
 * @return Nova substring, ou NULL se alocação falhar ou s for NULL
 * 
 * @note Trata casos onde start >= comprimento da string (retorna string vazia)
 * @note Ajusta len se exceder o comprimento restante da string
 * @note Quem chama deve libertar o ponteiro retornado
 */

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr_s;
	size_t	len_s;
	size_t	i;

	if (!s)
		return ((void *)0);
	len_s = ft_strlen(s);
	if (start >= len_s)
		len = 0;
	else if (len > (len_s - start))
		len = (len_s - start);
	ptr_s = malloc((len + 1) * sizeof(char));
	if (!ptr_s)
		return ((void *)0);
	i = 0;
	while (i < len && s[start + i])
	{
		ptr_s[i] = s[start + i];
		i++;
	}
	ptr_s[i] = '\0';
	return (ptr_s);
}

/**
 * @brief Concatena duas strings numa nova string
 * 
 * Aloca e retorna uma nova string que é o resultado de
 * concatenar s1 e s2.
 * 
 * @param s1 Primeira string (prefixo)
 * @param s2 Segunda string (sufixo)
 * @return Nova string concatenada, ou NULL se alocação falhar ou parâmetros NULL
 * 
 * @note Ambas s1 e s2 devem ser não-NULL
 * @note Quem chama deve libertar o ponteiro retornado
 * @note Strings originais não são modificadas
 */

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*concat_s;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return ((void *)0);
	concat_s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!concat_s)
		return ((void *)0);
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
