/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:58:46 by lucpardo          #+#    #+#             */
/*   Updated: 2025/06/08 22:53:35 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

// frees and sets pointers to NULL
static char	*ft_cleaner(char *line, char **buffer)
{
	if (line != NULL)
		free(line);
	if (buffer != NULL && *buffer != NULL)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

// returns current line and saves leftover data
// if data is beyond lenght, save for the next gnl call with substr.
// "ft_strlen(*buffer) - len" is the total buff len - already used line
// calculates how many character leftovers.
// if total is 30 chars and used 6, 30-6 = 24 characters remain
// frees buffer if no data remains
static char	*ft_store_leftover(char **buffer, char *line, int len)
{
	char	*temp;

	if (ft_strlen(*buffer) > (size_t)len)
	{
		temp = ft_gnl_substr(*buffer, len, ft_strlen(*buffer) - len);
		if (temp == NULL)
			return (ft_cleaner(line, buffer));
		free(*buffer);
		*buffer = temp;
	}
	else
		ft_cleaner(NULL, buffer);
	return (line);
}

// constructs next line from main_buffer
// extracts line portion
// if newline, save leftover for next calls, if no nl, clean.
// returns formatted line
static char	*ft_builder(char **buffer)
{
	char	*newline_i;
	char	*line;
	int		len;

	if (buffer == NULL || *buffer == NULL || !**buffer)
		return (ft_cleaner(NULL, buffer));
	newline_i = ft_strchr(*buffer, '\n');
	if (newline_i != NULL)
		len = newline_i - *buffer + 1;
	else
		len = ft_strlen(*buffer);
	line = ft_gnl_substr(*buffer, 0, len);
	if (line == NULL)
		return (ft_cleaner(NULL, buffer));
	if (newline_i != NULL)
		return (ft_store_leftover(buffer, line, len));
	ft_cleaner(NULL, buffer);
	return (line);
}

// gathers data in chunks until newline
// read BUFFER_SIZE bytes from fd into temp_buffer
// concatenate chunks in main_buffer
// continue until nl, EOF or error
// return temp_buffer or NULL
static char	*ft_gatherer(char **main_buffer, char *temp_buffer, int fd)
{
	int		bytes_read;
	char	*temp;

	while (*main_buffer == NULL || ft_strchr(*main_buffer, '\n') == NULL)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			ft_cleaner(NULL, main_buffer);
			return (free(temp_buffer), NULL);
		}
		if (bytes_read == 0)
			break ;
		temp_buffer[bytes_read] = '\0';
		temp = ft_gnl_strjoin(*main_buffer, temp_buffer);
		if (temp == NULL)
		{
			*main_buffer = NULL;
			return (free(temp_buffer), NULL);
		}
		*main_buffer = temp;
	}
	return (temp_buffer);
}

char	*get_next_line(int fd)
{
	char		*temp_buffer;
	static char	*main_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp_buffer = malloc(BUFFER_SIZE + 1);
	if (temp_buffer == NULL)
		return (ft_cleaner(NULL, &main_buffer));
	if (ft_gatherer(&main_buffer, temp_buffer, fd) == NULL)
		return (NULL);
	free(temp_buffer);
	temp_buffer = NULL;
	return (ft_builder(&main_buffer));
}
