#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "../get_next_line.h"
#include <stdio.h>

void	print(t_segment *segment, char *message)
{
	printf("-----------------------------------------------------------------\n");
	printf("%s\n", message);
	for(int i=0;i<mod_strlen(message);i++)
		printf("-");
	printf("\n");
	printf("str: %s.\n", segment->str);
	printf("\t\t\tReturn_value: %d\n", segment->len);
	printf("\t\t\tprevious:%p\n", segment->previous);
	printf("\t\t\tnext:%p\n", segment->next);
	printf("-----------------------------------------------------------------\n\n");
	fflush(stdout);
}

int	ft_isascii(int c)
{
	if ((c >= 0 && c <= 127))
		return (1);
	return (0);
}

int		main()
{

	char	*str = "";
//	char	*file = "/Users/yde-mont/Desktop/ECLIPSE/workspace/LIBFT/get_next_line/toto.txt";
	char	*file = "/Users/yde-mont/Desktop/ECLIPSE/workspace/LIBFT/get_next_line/numbers.dict.txt";

	int		fd = open(file, O_RDONLY);
	printf("Buffer:%d\n", BUFFER_SIZE);
	if (ERROR == fd)
	{
		write(2, "ERROR on opening file!\n", 22);
		return -1;
	}
	int i = 0;
	while (get_next_line(fd, &str))
		;
//		printf("line %d:\t\t%s.\n", i++, str);
//	printf("line %d:\t%s.\n", i++, str);
	close(fd);
	return (0);
}
