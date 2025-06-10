/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:52:43 by lucpardo          #+#    #+#             */
/*   Updated: 2025/06/10 22:07:22 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

// frees and sets pointers to NULL to avoid dangling pointers
static char	*ft_cleaner(char *line, char **buffer)
{
	if (line)
		free(line);
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

// returns current line and saves leftover data
// if data is beyond lenght, save for the next gnl call with substr
// "ft_strlen(*buffer) - len" is the total buff len minus already used line
// calculates how many character leftovers.
// ex. if total is 30 chars and used 6, 30-6 = 24 characters remain
// frees buffer if no data remains
static char	*ft_store_leftover(char **buffer, char *line, int len)
{
	char	*temp;

	if (ft_strlen(*buffer) > (size_t)len)
	{
		temp = ft_gnl_substr(*buffer, len, ft_strlen(*buffer) - len);
		if (!temp)
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
// returns extracted line or null if error
static char	*ft_builder(char **buffer)
{
	char	*newline_i;
	char	*line;
	int		len;

	if (!buffer || !*buffer || !**buffer)
		return (ft_cleaner(NULL, buffer));
	newline_i = ft_strchr(*buffer, '\n');
	if (newline_i)
		len = newline_i - *buffer + 1;
	else
		len = ft_strlen(*buffer);
	line = ft_gnl_substr(*buffer, 0, len);
	if (!line)
		return (ft_cleaner(NULL, buffer));
	if (newline_i)
		return (ft_store_leftover(buffer, line, len));
	ft_cleaner(NULL, buffer);
	return (line);
}

// gathers data in chunks until newline
// read BUFFER_SIZE bytes from fd into temp_buffer
// concatenate chunks in main_buffer
// continue until newline, EOF, or error
// return temp_buffer or NULL
static char	*ft_gatherer(char **main_buffer, char *temp_buffer, int fd)
{
	int		bytes_read;
	char	*temp;

	while (!*main_buffer || !ft_strchr(*main_buffer, '\n'))
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
		if (!temp)
		{
			*main_buffer = NULL;
			return (free(temp_buffer), NULL);
		}
		*main_buffer = temp;
	}
	return (temp_buffer);
}

// allocates temporary buffer for reading chunks
// gathers data until next lien is found with ft_gatherer
// extracts and returns the line with ft_builder
// returns next line with newline or NULL on error or EOF
char	*get_next_line(int fd)
{
	char		*temp_buffer;
	static char	*main_buffer[MAX_FD];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	temp_buffer = malloc(BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (ft_cleaner(NULL, &main_buffer[fd]));
	if (!ft_gatherer(&main_buffer[fd], temp_buffer, fd))
		return (NULL);
	free(temp_buffer);
	return (ft_builder(&main_buffer[fd]));
}
