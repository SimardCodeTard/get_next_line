/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:56:31 by smenard           #+#    #+#             */
/*   Updated: 2025/11/20 12:47:51 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Counts the number of charcaters in the NULL terminated buffer until we reach
 * the end of a line or the end of the buffer
 */
size_t	next_line_len(char *buffer, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && buffer[i] == '\n')
	{
		i++;
	}
	i += buffer[i] == '\n';
	return (i);
}

/**
 * Extract the next line from the buffer and returns it
 */
char	*extract_line(int fd, char *buffer, size_t rest_len)
{
	ssize_t	i;
	ssize_t	line_len;
	char	*full_line;
	char	*current_line;

	full_line = NULL;
	while (read_exact(fd, buffer + rest_len, BUFFER_SIZE - rest_len) > 0)
	{
		i = -1;
		line_len = next_line_len(buffer, BUFFER_SIZE);
		current_line = malloc((line_len + 1) * sizeof(char));
		if (!current_line)
			return (NULL);
		while (++i < line_len)
			current_line[i] = buffer[i];
		current_line[i] = '\0';
		full_line = ft_strjoin(full_line, current_line);
		if (!full_line)
			return (safe_free_return((void **) &current_line, 1, NULL));
		if (buffer[i - 1] == '\n')
			break ;
		rest_len = 0;
	}
	return (full_line);
}

/**
 * Reads up to size characets into buffer from fd
 */
size_t	read_exact(int fd, char *buffer, size_t size)
{
	size_t	read_result;
	size_t	total_bytes_read;

	read_result = 1;
	total_bytes_read = 0;
	while (read_result > 0 && total_bytes_read < size)
	{
		read_result = read(fd, buffer + total_bytes_read,
				size - total_bytes_read);
		if (read_result > 0)
			total_bytes_read += read_result;
	}
	return (read_result);
}

/**
 * Allocates memory and returns a string containing s1 and s2 joined together
 * The input strings are freed
 */
char	*ft_strjoin(char *s1, char *s2)
{
	const char	*ptrs[2] = {s1, s2};
	size_t		i;
	size_t		s1_len;
	size_t		s2_len;
	char		*s_joined;

	i = 0;
	s1_len = 0;
	s2_len = 0;
	while (s1 && s1[s1_len])
		s1_len++;
	while (s2 && s2[s2_len])
		s2_len++;
	s_joined = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!s_joined)
		return (safe_free_return ((void **) ptrs, 2, NULL));
	while (s1 && s1[i])
		s_joined[i] = s1[i];
	while (s2 && s2[i])
		s_joined[i - s1_len] = s2[i];
	s_joined[s1_len + i] = '\0';
	return (safe_free_return((void **) ptrs, 2, s_joined));
}

/**
 * Frees all pointers in ptrs and returns value
 */
void	*safe_free_return(void **ptrs, size_t ptrs_size, void *value)
{
	size_t	i;

	i = 0;
	while (i < ptrs_size)
	{
		if (ptrs[i])
			free(ptrs[i]);
		i++;
	}
	return (value);
}
