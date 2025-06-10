/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:51:37 by lucpardo          #+#    #+#             */
/*   Updated: 2025/06/10 21:30:00 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)c)
		{
			return ((char *)str + i);
		}
		++i;
	}
	if (str[i] == '\0' && (unsigned char)c == '\0')
	{
		return ((char *)str + i);
	}
	return (NULL);
}

// returns new string containing a portion of existing string
char	*ft_gnl_substr(char const *str, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	slen;
	size_t	i;

	if (str == NULL)
		return (NULL);
	slen = ft_strlen(str);
	if (start >= slen)
		return (ptr = malloc (1), ptr && (ptr[0] = '\0'), ptr);
	if (len > slen - start)
		len = slen - start;
	ptr = malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = str[start + i];
		i++;
	}
	return (ptr[i] = '\0', ptr);
}

// difference with normal strjoin: automatically frees s1 after copying
// to prevent leaks while the buffer is accumulating
// returns concatenated string
char	*ft_gnl_strjoin(char *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	if (s2 == NULL)
		return (s1);
	s1_len = 0;
	if (s1)
		s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc(s1_len + s2_len + 1);
	if (str == NULL)
		return (free(s1), NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (free(s1), str);
}

// frees pointer and initializes it to NULL to prevent dangling pointer
void	ft_free_and_zero(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
