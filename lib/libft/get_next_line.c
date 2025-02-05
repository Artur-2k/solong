/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:47:56 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/08 17:36:09 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_from_file(int fd, char *big_buffer);
static char	*append_buffers(char *big_buffer, char *small_buffer);
static char	*extract_line(char *buffer);
static char	*clear_buffer(char *big_buffer);

char	*get_next_line(int fd)
{
	char		*line;
	static char	*big_buffer;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!big_buffer)
		big_buffer = ft_calloc(1, sizeof(char));
	if (!ft_strchr(big_buffer, '\n'))
		big_buffer = read_from_file(fd, big_buffer);
	if (!big_buffer)
		return (NULL);
	line = extract_line(big_buffer);
	big_buffer = clear_buffer(big_buffer);
	if (*big_buffer == '\0')
	{
		free(big_buffer);
		big_buffer = NULL;
	}
	return (line);
}

char	*read_from_file(int fd, char *big_buffer)
{
	char	*small_buffer;
	int		bytes_read;

	small_buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!small_buffer)
		return (free(big_buffer), NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, small_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(big_buffer), free(small_buffer), NULL);
		small_buffer[bytes_read] = '\0';
		big_buffer = append_buffers(big_buffer, small_buffer);
		if (ft_strchr(big_buffer, '\n'))
			break ;
	}
	free(small_buffer);
	return (big_buffer);
}

char	*append_buffers(char *big_buffer, char *small_buffer)
{
	char	*new_big_buffer;

	new_big_buffer = ft_strjoin(big_buffer, small_buffer);
	if (!new_big_buffer)
		return (NULL);
	free(big_buffer);
	return (new_big_buffer);
}

char	*extract_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	if (!buffer || !*buffer)
		return (NULL);
	i = 0;
	while (buffer[i])
	{
		if (buffer[i++] == '\n')
			break ;
	}
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (line = NULL, NULL);
	line[i] = '\0';
	j = 0;
	while (j < i)
	{
		line[j] = buffer[j];
		j++;
	}
	return (line);
}

char	*clear_buffer(char *big_buffer)
{
	char	*cleaned_big_buffer;
	int		i;

	i = 0;
	while (big_buffer[i])
	{
		if (big_buffer[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	cleaned_big_buffer = ft_substr(big_buffer, i, ft_strlen(&big_buffer[i]));
	free(big_buffer);
	return (cleaned_big_buffer);
}
