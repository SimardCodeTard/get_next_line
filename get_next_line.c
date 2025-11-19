/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:18:59 by smenard           #+#    #+#             */
/*   Updated: 2025/11/19 17:16:18 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Get the next line of the file pointed by fd
 */
char	*get_next_line(int fd);

/**
 * Get the static buffer containing the rest of the last call to get_next_line
 */
char	*get_rest(int fd)
{
	static char *rests[MAX_FD];
	char		*buffer;

	if (!rests[fd])
		rests[fd] = malloc(BUFFER_SIZE * sizeof(char));
	return (rests[fd]);
}
