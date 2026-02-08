/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidos- <davidos-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:20:56 by davidos-          #+#    #+#             */
/*   Updated: 2026/02/08 21:37:43 by davidos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free_and_return(char *buffer, char *temp);
char	*ft_read_file(int fd, char *buffer);
char	*ft_get_line(char *buffer);
char	*ft_update_buff(char *buffer);
char	*get_next_line(int fd);

/**
 * @brief Função principal para ler próxima linha de file descriptor (bonus)
 * 
 * Versão bonus que suporta leitura de múltiplos file descriptors
 * simultaneamente. Usa um array estático indexado por file descriptor para
 * manter buffers separados para cada ficheiro aberto.
 * 
 * @param fd File descriptor para ler (deve ser >= 0 e < OPEN_MAX)
 * @return A próxima linha incluindo '\n', ou NULL se EOF/erro
 * 
 * @note Suporta múltiplos file descriptors concorrentemente
 * @note Usa array estático de buffers indexado por fd
 * @note Valida que fd está dentro do intervalo válido (0 a OPEN_MAX)
 * @note Quem chama é responsável por libertar a string retornada
 */

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

/**
 * @brief Junta duas strings e liberta a primeira
 * 
 * Função auxiliar que concatena buffer e temp,
 * depois liberta o buffer original para prevenir memory leaks.
 * 
 * @param buffer String a ser juntada e libertada
 * @param temp String a ser adicionada
 * @return String juntada recém-alocada
 */

char	*ft_join_and_free(char *buffer, char *temp)
{
	char	*new_buffer;

	new_buffer = ft_strjoin(buffer, temp);
	free(buffer);
	return (new_buffer);
}

/**
 * @brief Lê do file descriptor para buffer até newline ou EOF
 * 
 * Lê continuamente BUFFER_SIZE bytes de cada vez do file descriptor
 * e acumula-os no buffer até encontrar um caractere newline ou
 * chegar ao fim do ficheiro.
 * 
 * @param fd File descriptor para ler
 * @param buffer Buffer existente para este fd (pode ser NULL na 1ª chamada)
 * @return Buffer atualizado com conteúdo lido, ou NULL em caso de erro
 * 
 * @note Gere erros de alocação de memória
 * @note Retorna NULL se read falhar ou buffer estiver vazio
 * @note Preserva conteúdo do buffer entre chamadas para o mesmo fd
 */

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

/**
 * @brief Extrai uma única linha do buffer
 * 
 * Extrai caracteres do buffer até e incluindo o primeiro caractere
 * newline, ou até ao fim da string se não houver newline.
 * 
 * @param buffer Buffer contendo texto para extrair linha
 * @return String recém-alocada contendo a linha, ou NULL em caso de erro
 * 
 * @note Inclui o caractere newline na linha retornada se presente
 * @note Aloca size+2 para ter em conta newline e terminador null
 */

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

/**
 * @brief Atualiza buffer removendo a linha processada
 * 
 * Cria um novo buffer contendo apenas o texto restante após
 * o primeiro caractere newline. Liberta o buffer antigo.
 * 
 * @param buffer Buffer atual a atualizar
 * @return Novo buffer com conteúdo restante, ou NULL se não restar conteúdo
 * 
 * @note Liberta o buffer de entrada
 * @note Retorna NULL se não houver newline ou nada após newline
 */

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
