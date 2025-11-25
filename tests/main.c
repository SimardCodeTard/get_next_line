/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:46:29 by smenard           #+#    #+#             */
/*   Updated: 2025/11/25 15:00:18 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

static char	*convert_unprintable_char(char c)
{
	char	*special_unprintable_chars[14];
	char	*str;

	special_unprintable_chars['\a'] = "\\a";
	special_unprintable_chars['\b'] = "\\b";
	special_unprintable_chars['\t'] = "\\t";
	special_unprintable_chars['\n'] = "\\n";
	special_unprintable_chars['\v'] = "\\v";
	special_unprintable_chars['\f'] = "\\f";
	special_unprintable_chars['\r'] = "\\r";
	str = malloc(5);
	if (!str)
		return (NULL);
	if (isprint(c))
		sprintf(str, "%c", c);
	else if (c >= '\a' && c <= '\r')
		sprintf(str, "%s", special_unprintable_chars[(int) c]);
	else if (c < 10)
		sprintf(str, "\\x0%d", c);
	else
		sprintf(str, "\\x%d", c);
	return (str);
}

char	*read_and_print_line(int fd)
{
	char	*c_toprint;
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	if (!line)
	{
		printf("(null)\n");
		return (NULL);
	}
	while (line && line[i] && i < 200)
	{
		c_toprint = convert_unprintable_char(line[i]);
		printf("%s", c_toprint);
		free(c_toprint);
		i++;
	}
	if (i == 200)
		printf("... (%lu characters remaining)", strlen(line) - 200);
	printf("\n");
	return (line);
}

void	test_read_file(char *path, int nlines)
{
	char	*line;
	int		fd;

	printf("=====Reading %2d lines from file %s=====\n", nlines, path);
	fd = open(path, O_RDONLY);
	line = "";
	for (int i = 0; i < nlines; i++)
	{
		printf("Line [%2d]: ", i + 1);
		line = read_and_print_line(fd);
		free(line);
	}
	close(fd);
	printf("==========\n");
}

int	main(void)
{
	// Norminette flag me :3
	test_read_file("(INVALID FD)", 1);
	test_read_file("tests/1char.txt", 2);
	test_read_file("tests/empty.txt", 1);
	test_read_file("tests/giant_line_nl.txt", 3);
	test_read_file("tests/giant_line.txt", 2);
	test_read_file("tests/lines_around_10.txt", 6);
	test_read_file("tests/multiple_nl.txt", 6);
	test_read_file("tests/one_line_no_nl.txt", 2);
	test_read_file("tests/only_nl.txt", 2);
	test_read_file("tests/read_error.txt", 5);
	test_read_file("tests/variable_nls.txt", 13);
	return (EXIT_SUCCESS);
}
