#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
	char *line;
	char *line2;

	int fd_1 = open("test.txt", O_RDONLY);
	int fd_2 =open("test.txt" , O_RDONLY);

	line = get_next_line(fd_1);
	line2 = get_next_line(fd_2);


	printf("%s", line);
	printf("%s", line2);



	free(line);
	free(line);


}
