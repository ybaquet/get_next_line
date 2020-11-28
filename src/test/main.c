#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <fcntl.h>

int	*open_read_file(char *file, char *search)
{
	int		fd;
	char	**line;

	fd =  open(file, O_RDONLY);
	if(-1 == fd)
		return NULL;
	while(!get_next_line(fd, **line))
	{

	}
	close(fd);
	return fd;
}

int main(void)
{

}
