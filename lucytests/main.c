#include "../get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

void	ft_oOo(void)
{
	printf("\n o O o O o O o O o O o O o O o O o O o O o O o O o O o \n");
}

void	ft_sep(void)
{
	printf("\n                                                       \n");
}

void	ft_start(void)
{
	printf("\033[1m    g e t _ n e x t _ l i n e   t e s t s   s t a r t\033[0m");
}

void	ft_end(void)
{
	printf("\033[1m      g e t _ n e x t _ l i n e   t e s t s   e n d\033[0m");
}

int	main(void)
{
	char	*line;

	int fd1, fd2, fd3;
	ft_oOo();
	ft_oOo();
	ft_oOo();
	ft_start();
	ft_oOo();
	ft_oOo();
	ft_oOo();
	ft_sep();
	printf("\033[1m         testing multiple fd support\033[0m");
	ft_sep();
	fd1 = open("lucytests/test1.txt", O_RDONLY);
	fd2 = open("lucytests/test2.txt", O_RDONLY);
	printf("read from fd1:");
	ft_sep();
	line = get_next_line(fd1);
	printf("FD1 Line 1: %s", line);
	if (line)
		free(line);
	ft_sep();
	printf("read from fd2:");
	ft_sep();
	line = get_next_line(fd2);
	printf("FD2 Line 1: %s", line);
	if (line)
		free(line);
	ft_sep();
	printf("back to fd1 (should remember where we left off):");
	ft_sep();
	line = get_next_line(fd1);
	printf("FD1 line 2: %s", line);
	if (line)
		free(line);
	ft_sep();
	printf("back to fd2 (should remember where we left off):");
	ft_sep();
	line = get_next_line(fd2);
	printf("FD2 line 2: %s", line);
	if (line)
		free(line);
	ft_sep();
	printf("one more time from fd1:");
	ft_sep();
	line = get_next_line(fd1);
	printf("FD1 line 3: %s", line);
	if (line)
		free(line);
	close(fd1);
	close(fd2);
	ft_sep();
	printf("\033[1m      edge cases (the scary stuff)\033[0m");
	ft_sep();
	printf("1. testing invalid fd (-1) - will my function survive?");
	ft_sep();
	line = get_next_line(-1);
	if (line)
	{
		printf("oh no something went wrong D:");
		free(line);
	}
	else
		printf("NULL (phew!)");
	ft_sep();
	printf("2. testing non-existent file (asking for trouble):");
	ft_sep();
	fd3 = open("lucytests/this_file_doesnt_exist_lol.txt", O_RDONLY);
	line = get_next_line(fd3);
	if (line)
	{
		printf("somehow it worked??");
		free(line);
	}
	else
		printf("NULL (as expected!)");
	if (fd3 != -1)
		close(fd3);
	ft_sep();
	printf("3. testing empty file (the void stares back):");
	ft_sep();
	fd3 = open("lucytests/empty.txt", O_RDONLY);
	line = get_next_line(fd3);
	if (line)
	{
		printf("wait how did we get something??");
		free(line);
	}
	else
		printf("NULL (correct, nothing to read!)");
	close(fd3);
	ft_sep();
	printf("4. testing file with no final newline:");
	ft_sep();
	fd3 = open("lucytests/no_final_nl.txt", O_RDONLY);
	line = get_next_line(fd3);
	if (line)
	{
		printf("result: '%s'", line);
		free(line);
	}
	else
		printf("NULL");
	close(fd3);
	ft_sep();
	printf("5. testing single character file (minimalist vibes):");
	ft_sep();
	fd3 = open("lucytests/single_char.txt", O_RDONLY);
	line = get_next_line(fd3);
	if (line)
	{
		printf("result: '%s'", line);
		free(line);
	}
	else
		printf("NULL");
	close(fd3);
	ft_sep();
	printf("6. testing multiple calls on empty file (being persistent):");
	ft_sep();
	fd3 = open("lucytests/empty2.txt", O_RDONLY);
	line = get_next_line(fd3);
	if (line)
	{
		printf("first call: unexpected!");
		free(line);
	}
	else
		printf("first call: NULL (good!)");
	ft_sep();
	line = get_next_line(fd3);
	if (line)
	{
		printf("second call: still getting stuff??");
		free(line);
	}
	else
		printf("second call: NULL (still good!)");
	close(fd3);
	ft_sep();
	printf("7. testing ridiculously large fd number:");
	ft_sep();
	line = get_next_line(9999);
	if (line)
	{
		printf("somehow this worked???");
		free(line);
	}
	else
		printf("NULL (boundary protection works!)");
	ft_sep();
	printf("8. testing reading past eof (asking for more when there's nothing left):");
	ft_sep();
	fd3 = open("lucytests/short.txt", O_RDONLY);
	line = get_next_line(fd3);
	if (line)
	{
		printf("first read: '%s'", line);
		free(line);
	}
	else
		printf("first read: NULL");
	ft_sep();
	line = get_next_line(fd3);
	if (line)
	{
		printf("second read (past eof): got something mysterious");
		free(line);
	}
	else
		printf("second read (past eof): NULL (correctly nothing left!)");
	close(fd3);
	ft_sep();
	printf("\033[1m  evaluation sheet tests\033[0m");
	ft_sep();
	printf("9. testing invalid fd 42 (classic evaluator test):");
	ft_sep();
	line = get_next_line(42);
	if (line)
	{
		printf("somehow fd 42 worked??");
		free(line);
	}
	else
		printf("NULL (correct - fd 42 is invalid!)");
	ft_sep();
	printf("10. testing multiple long lines (2k+ chars each):");
	ft_sep();
	fd3 = open("lucytests/long_lines.txt", O_RDONLY);
	line = get_next_line(fd3);
	if (line)
	{
		printf("first long line length: %d chars", (int)strlen(line));
		free(line);
	}
	else
		printf("NULL on long line");
	line = get_next_line(fd3);
	if (line)
	{
		printf(" | second long line length: %d chars", (int)strlen(line));
		free(line);
	}
	else
		printf(" | NULL on second long line");
	close(fd3);
	ft_sep();
	printf("11. testing multiple empty lines:");
	ft_sep();
	fd3 = open("lucytests/empty_lines.txt", O_RDONLY);
	line = get_next_line(fd3);
	if (line)
	{
		printf("first empty line: '%s' (should be just newline)", line);
		free(line);
	}
	else
		printf("NULL on empty line");
	line = get_next_line(fd3);
	if (line)
	{
		printf("second empty line: '%s'", line);
		free(line);
	}
	else
		printf("NULL on second empty line");
	close(fd3);
	ft_sep();
	printf("12. testing mix of very short (1 char) and normal lines:");
	ft_sep();
	fd3 = open("lucytests/mixed.txt", O_RDONLY);
	line = get_next_line(fd3);
	if (line)
	{
		printf("short line: '%s'", line);
		free(line);
	}
	line = get_next_line(fd3);
	if (line)
	{
		printf("normal line: '%s'", line);
		free(line);
	}
	line = get_next_line(fd3);
	if (line)
	{
		printf("short line again: '%s'", line);
		free(line);
	}
	close(fd3);
	ft_sep();
	printf("13. testing stdin reading (fd 0) - might hang if no input:");
	ft_sep();
	printf("(skipping stdin test to avoid hanging - but it should work!)");
	ft_sep();
	printf("all tests complete! hopefully nothing exploded :D");
	ft_sep();
	ft_oOo();
	ft_oOo();
	ft_oOo();
	ft_end();
	ft_oOo();
	ft_oOo();
	ft_oOo();
	return (0);
}
