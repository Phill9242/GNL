#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
int main (void)
{
	int fd;
	int fd1;

	fd = open ("k", O_RDWR);
	fd1 = open ("n", O_RDWR);

	printf ("%s",get_next_line(fd));
	printf ("%s",get_next_line(fd1));
	printf ("%s",get_next_line(fd));
	printf ("%s",get_next_line(fd1));
	printf ("%s",get_next_line(fd));
	printf ("%s",get_next_line(fd1));


}
