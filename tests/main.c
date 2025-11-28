/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:46:29 by smenard           #+#    #+#             */
/*   Updated: 2025/11/28 15:58:33 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <time.h>

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

void	test_read_all_lines(int fd, char *path)
{
	char	*line;
	int		i;

	printf("=====Reading all lines from file %s=====\n", path);
	i = 0;
	line = "";
	while (line)
	{
		printf("Line [%2d]: ", i + 1);
		line = read_and_print_line(fd);
		free(line);
		i++;
	}
	close(fd);
	printf("==========\n");
}

void	test_read_file(char *path, int nlines)
{
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		printf("WARNING: Failed to open file at %s\n", path);
	if (nlines == -1)
		return (test_read_all_lines(fd, path));
	printf("=====Reading %2d lines from file %s=====\n", nlines, path);
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

void	test_read_file_all_lines_timer(char *path)
{
	int		fd;
	char	*line;
	clock_t	before;
	int		diff;
	int		duration;

	fd = open(path, 0, 0);
	if (fd == -1)
		printf("WARNING: Failed to open file at %s\n", path);
	printf("Reading all lines from file %s with timer\n", path);
	before = clock();
	while ((line = get_next_line(fd)))
		free(line);
	diff = clock() - before;
	duration = diff * 1000 / CLOCKS_PER_SEC;
	printf("Time taken: %d milliseconds\n",
		duration);
	close(fd);
	printf("==========\n");
}

void	test_read_file_timer(char *path, int nlines)
{
	int		fd;
	clock_t	before;
	int		diff;
	int		duration;

	fd = open(path, 0, 0);
	if (fd == -1)
		printf("WARNING: Failed to open file at %s\n", path);
	if (nlines == -1)
		return (test_read_file_all_lines_timer(path));
	printf("Reading %2d lines from file %s with timer\n", nlines, path);
	before = clock();
	for (int i = 0; i < nlines; i++)
		free(get_next_line(fd));
	diff = clock() - before;
	duration = diff * 1000 / CLOCKS_PER_SEC;
	printf("Time taken: %d milliseconds\n",
		duration);
	close(fd);
	printf("==========\n");
}

int	main(int ac, char **av)
{
	char	*path;
	int		nlines;
	// Norminette flag me :3

	if (ac == 1)
		return (1);
	if (ac == 2)
	{
		path = av[1];
		nlines = -1;
	}
	else if (ac == 3)
	{
		path = av[1];
		nlines = atoi(av[2]);
	}
	else
	{
		path = av[1];
		nlines = atoi(av[2]);
		if (atoi(av[ac - 1]) == 1)
			test_read_file_timer(path, nlines);
		else
			printf("Use \"1\" as the last argument to run the test \
with a timer.\n");
		return (EXIT_SUCCESS);
	}
	test_read_file(path, nlines);
	return (EXIT_SUCCESS);
}
