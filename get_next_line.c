/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:18:59 by smenard           #+#    #+#             */
/*   Updated: 2025/11/25 15:00:40 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Get the next line of the file pointed by fd
 */
char	*get_next_line(int fd)
{
	t_buffer	**buffer;
	char		*line;

	buffer = get_buffer(fd);
	if (!buffer || !*buffer)
		return (NULL);
	line = build_next_line(fd, buffer);
	if (!line)
		return (safe_free_return(NULL, buffer, NULL, NULL));
	return (line);
}

/**
 * Allocates memory and reads the next line in the file pointed by fd
 */
char	*build_next_line(int fd, t_buffer **buf)
{
	t_list				*lst;
	t_line_build_status	status;
	char				*line;
	size_t				total_content_length;

	status = INCOMPLETE;
	total_content_length = 0;
	lst = ft_lstnew(&total_content_length);
	if (!lst)
		return (NULL);
	while (status != COMPLETE && status != NO_LINES)
	{
		status = extract_line(fd, lst, buf, &(*buf)->rest_index);
		if (status == ERROR)
			return (safe_free_return(lst, NULL, NULL, NULL));
	}
	if ((*buf)->data[(*buf)->rest_index] == '\n')
	{
		(*buf)->rest_index++;
		if (!ft_lstappend(lst, '\n'))
			return (safe_free_return(lst, NULL, NULL, NULL));
	}
	line = ft_lstjoin_clear(lst);
	return (line);
}

t_line_build_status	extract_line(int fd, t_list *lst, t_buffer **buf,
					size_t *index)
{
	t_list				*curr_link;
	t_line_build_status	status;
	ssize_t				read_res;

	status = INCOMPLETE;
	read_res = 0;
	curr_link = lst;
	while (*index < (*buf)->buffer_length
		&& (*buf)->data[*index] && (*buf)->data[*index] != '\n')
	{
		curr_link = ft_lstappend(curr_link, (*buf)->data[*index]);
		if (!curr_link)
			return (ERROR);
		*index += 1;
	}
	if (*index < (*buf)->buffer_length && (*buf)->data[*index] == '\n')
		status = COMPLETE;
	if (status != COMPLETE)
		read_res = read_file(fd, *buf);
	if (read_res == -1 || (read_res == 0 && lst->total_content_length == 0))
		return (ERROR);
	if (read_res == 0)
		status = NO_LINES;
	return (status);
}

/**
 * Get the static buffer containing the rest of the last call to get_next_line
 */
t_buffer	**get_buffer(int fd)
{
	static t_buffer	*buffers[MAX_FD];

	if (fd < 0)
		return (NULL);
	if (!buffers[fd])
	{
		buffers[fd] = malloc(sizeof(t_buffer));
		if (!buffers[fd])
			return (NULL);
		buffers[fd]->data = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffers[fd]->data)
			return (safe_free_return(NULL, &buffers[fd], NULL, NULL));
		buffers[fd]->rest_index = 0;
		if (read_file(fd, buffers[fd]) <= 0)
			return (safe_free_return(NULL, &buffers[fd], NULL, NULL));
	}
	else if (!buffers[fd]->data[buffers[fd]->rest_index])
		if (read_file(fd, buffers[fd]) <= 0)
			return (safe_free_return(NULL, &buffers[fd], NULL, NULL));
	return (&buffers[fd]);
}
