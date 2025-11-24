/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:18:59 by smenard           #+#    #+#             */
/*   Updated: 2025/11/24 12:21:11 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Allocates memory and reads the next line in the file pointed by fd
 */
char	*build_next_line(int fd, char *buffer, size_t *last_part_len)
{
	t_line_extract_result	extract_line_res;
	char					*line_part;
	char					*full_line;
	int64_t					read_result;

	full_line = NULL;
	extract_line_res = INCOMPLETE;
	while (extract_line_res == INCOMPLETE || extract_line_res == BUFFER_END)
	{
		line_part = malloc((ft_strlen(buffer, '\n') + 1) * sizeof(char));
		if (!line_part)
			return (safe_free_return(full_line, NULL, NULL, NULL));
		extract_line_res = extract_line(buffer, line_part);
		*last_part_len = ft_strlen(line_part, '\0');
		full_line = ft_strjoin_free(full_line, line_part);
		if (!full_line)
			return (NULL);
		if (extract_line_res == BUFFER_END)
		{
			read_result = read_file(fd, buffer, BUFFER_SIZE);
			if (read_result == -1)
				return (safe_free_return(full_line, NULL, NULL, NULL));
			if (read_result <= 0)
				extract_line_res = NO_LINES;
		}
	}
	return (full_line);
}

/**
 * Get the next line of the file pointed by fd
 */
char	*get_next_line(int fd)
{
	size_t	last_part_line;
	char	*buffer;
	char	**rest;
	char	*line;

	if (fd < 0)
		return (NULL);
	rest = get_rest(fd);
	if (!rest || !*rest)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (safe_free_return(NULL, NULL, rest, NULL));
	ft_strcpy(*rest, buffer);
	if (!buffer[0])
		if (read_file(fd, buffer, BUFFER_SIZE) == -1)
			return (safe_free_return(NULL, buffer, rest, NULL));
	line = build_next_line(fd, buffer, &last_part_line);
	if (!line || !line[0])
		return (safe_free_return(line, buffer, rest, NULL));
	extract_rest(rest, buffer, last_part_line);
	return (safe_free_return(NULL, buffer, NULL, line));
}

/**
 * Get the static buffer containing the rest of the last call to get_next_line
 */
char	**get_rest(int fd)
{
	static char	*rests[MAX_FD];

	if (fd >= MAX_FD)
		return (NULL);
	if (!rests[fd])
	{
		rests[fd] = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!rests[fd])
			return (NULL);
		rests[fd][0] = '\0';
	}
	return (&rests[fd]);
}

/**
 * Extract the unused characters in buffer and puts them into rest
 */
void	extract_rest(char **rest, char *buffer, size_t last_line_len)
{
	size_t	i;
	size_t	buffer_len;
	char	*rest_val;

	rest_val = *rest;
	i = 0;
	buffer_len = ft_strlen(buffer, '\0') + 1;
	while (buffer[i] && i < buffer_len - last_line_len)
	{
		rest_val[i] = buffer[i + last_line_len];
		i++;
	}
	if (i == 0)
	{
		free(*rest);
		*rest = NULL;
		return ;
	}
	rest_val[i] = '\0';
}

/**
 * Copies n characters from src into the string dest and returns it
 */
char	*ft_strcpy(char *src, char *dest)
{
	size_t	i;

	if (!src)
		return (dest);
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
