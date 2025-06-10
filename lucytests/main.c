#include "../get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd1, fd2;
	char *line;
	
	fd1 = open("lucytests/test1.txt", O_RDONLY);
	fd2 = open("lucytests/test2.txt", O_RDONLY);
	
	printf("testing multiple fd support\n \n");
	
	printf("read from fd1:\n");
	line = get_next_line(fd1);
	printf("FD1 Line 1: %s", line);
	free(line);
	
	printf("\nread from fd2:\n");
	line = get_next_line(fd2);
	printf("FD2 Line 1: %s", line);
	free(line);
	
	printf("\nback to fd1 (should remember where we left off):\n");
	line = get_next_line(fd1);
	printf("FD1 line 2: %s", line);
	free(line);
	
	printf("\nback to fd2 (should remember where we left off):\n");
	line = get_next_line(fd2);
	printf("FD2 line 2: %s", line);
	free(line);
	
	printf("\none more time from fd1:\n");
	line = get_next_line(fd1);
	printf("FD1 line 3: %s", line);
	free(line);
	
	close(fd1);
	close(fd2);
	
	return (0);
}
