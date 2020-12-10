#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "../get_next_line.h"
#include <stdio.h>

int	ft_isascii(int c)
{
	if ((c >= 0 && c <= 127))
		return (1);
	return (0);
}

void test1() {
	char	*str = "";
	char	*file = "/Users/yde-mont/Desktop/ECLIPSE/workspace/LIBFT/get_next_line/toto.txt";
//	char	*file = "/Users/yde-mont/Desktop/ECLIPSE/workspace/LIBFT/get_next_line/numbers.dict.txt";

	int		fd = open(file, O_RDONLY);
	printf("Buffer:%d\n", BUFFER_SIZE);
	if (ERROR == fd)
	{
		write(2, "ERROR on opening file!\n", 22);
	}
	int i = 0;
	int result = 1;
	while ((result = get_next_line(fd, &str)) >= 0)
	{
		fprintf(stderr, "line %d:\t\t%s.\n", i++, str);
		free(str);
		if (!result)
			break;
	}
	close(fd);
}

void test2() {
	t_segment *s1 = malloc(sizeof(t_segment));
	t_segment *s2 = malloc(sizeof(t_segment));

	printf("%p, %p, %ld, %ld\n", s1, s2, s2 - s1, ((long) s2) - ((long) s1));
}
int		main()
{
	test1();
 while(1) ;
	return (0);
}
