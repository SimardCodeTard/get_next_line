/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:29:37 by smenard           #+#    #+#             */
/*   Updated: 2025/11/20 12:46:55 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>

/* ===== get_next_line.c ===== */

char	*get_next_line(int fd);

char	*get_rest(int fd);

void	extract_rest(char *rest, char *buffer, size_t last_line_len);

char	*ft_strndup(char *src, size_t n);

size_t	ft_strlen(char *str, char stop);

/* ===== get_next_line_utils.c ===== */

size_t	next_line_len(char *buffer, size_t size);

char	*extract_line(int fd, char *buffer, size_t rest_len);

size_t	read_exact(int fd, char *buffer, size_t size);

char	*ft_strjoin(char *s1, char *s2);

void	*safe_free_return(void **ptrs, size_t ptrs_len, void *value);

#endif
