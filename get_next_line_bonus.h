/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:29:37 by smenard           #+#    #+#             */
/*   Updated: 2025/12/01 13:31:18 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# ifndef LIST_MAX_CONTENT_LENGTH
#  define LIST_MAX_CONTENT_LENGTH 4096
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

typedef enum e_line_build_status
{
	ERROR,
	INCOMPLETE,
	COMPLETE,
	NO_LINES,
}						t_line_build_status;

typedef struct s_list
{
	struct s_list		*next;
	char				content[LIST_MAX_CONTENT_LENGTH];
	size_t				content_length;
	size_t				*total_content_length;
}						t_list;

typedef struct s_buffer
{
	char				*data;
	size_t				index;
}						t_buffer;

/* ===== get_next_line.c ===== */

char					*get_next_line(int fd);

char					*build_next_line(int fd, t_buffer *buffer);

t_line_build_status		extract_line(int fd, t_list *lst, t_buffer *buffer);

size_t					find_buffer_start(t_buffer *buffer);

t_buffer				*get_buffer(int fd);

/* ===== get_next_line_utils.c ===== */

char					*ft_lstjoin_clear(t_list *lst);

t_list					*ft_lstnew(size_t *total_content_length);

t_list					*ft_lstappend(t_list *lst, char c);

ssize_t					read_file(int fd, t_buffer *buffer);

void					*safe_free_return(t_list *lst, t_buffer *buffer,
							char *line, void *value);

#endif
