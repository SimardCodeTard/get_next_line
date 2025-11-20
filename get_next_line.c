/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:18:59 by smenard           #+#    #+#             */
/*   Updated: 2025/11/20 13:37:32 by smenard          ###   ########.fr       */
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
	rest_len = ft_strlen(rest);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	ft_strncpy(rest, buffer, rest_len);
	if (!buffer)
		return (safe_free_return((void **) &buffer, 1, NULL));
	line = extract_line(fd, buffer, rest_len);
	last_line_len = ft_strlen(line);
	extract_rest(rest, buffer, last_line_len);
	// if (rest && !rest[0])
	// 	free(rest);
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
		rests[fd][0] = '\0';
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
	while (i < BUFFER_SIZE - last_line_len)
	{
		rest[i] = buffer[i + last_line_len];
		i++;
	}
	rest[i] = '\0';
}

/**
 * Copies n characters from src into the string dest and returns it
 */
char	*ft_strncpy(char *src, char *dest, size_t n)
{
	size_t	i;

	if (!src)
		return (dest);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * Counts the length of the given NULL-terminated string
 */
size_t	ft_strlen(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}
