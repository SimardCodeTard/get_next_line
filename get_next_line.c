/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:18:59 by smenard           #+#    #+#             */
/*   Updated: 2025/11/20 12:47:10 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Get the next line of the file pointed by fd
 */
char	*get_next_line(int fd)
{
	size_t	last_line_len;
	size_t	rest_len;
	char	*buffer;
	char	*rest;
	char	*line;

	if (fd < 0)
		return (NULL);
	rest = get_rest(fd);
	if (!rest)
		return (NULL);
	rest_len = ft_strlen(rest, -1);
	buffer = ft_strndup(rest, rest_len);
	if (!buffer)
		return (safe_free_return((void **) &buffer, 1, NULL));
	line = extract_line(fd, buffer, rest_len);
	last_line_len = ft_strlen(line, 0);
	extract_rest(rest, buffer, last_line_len);
	return (safe_free_return((void **) &buffer, 1, line));
}

/**
 * Get the static buffer containing the rest of the last call to get_next_line
 */
char	*get_rest(int fd)
{
	static char	*rests[MAX_FD];

	if (!rests[fd])
	{
		rests[fd] = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!rests[fd])
			return (NULL);
		rests[fd][0] = -1;
	}
	return (rests[fd]);
}

/**
 * Extract the unused characters in buffer and puts them into rest
 */
void	extract_rest(char *rest, char *buffer, size_t last_line_len)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		rest[i] = buffer[i + last_line_len];
		i++;
	}
	rest[i] = -1;
}

/**
 * Allocates memory and copies n characters from src into a new string
 * Does not NULL-terminate the new string
 */
char	*ft_strndup(char *src, size_t n)
{
	size_t	i;
	char	*dest;

	dest = malloc(n * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

/**
 * Counts the length of the given NULL-terminated string
 */
size_t	ft_strlen(char *str, char stop)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] != stop)
		len++;
	return (len);
}
