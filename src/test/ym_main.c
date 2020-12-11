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

int test3() {
	int             fd;
	int             i;
	int             j;
	char    		*line = 0;
//	char			*lineadress[66];

	j = 1;
	printf("\n==========================================\n");
	printf("============= TEST 7 : Marge =============\n");
	printf("==========================================\n\n");

//	int fd2;

	if (!(fd = open("/Users/yde-mont/Desktop/ECLIPSE/workspace/LIBFT/get_next_line/files_gnl/mix_marge1", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
//	if (!(fd2 = open("/Users/yde-mont/Desktop/ECLIPSE/workspace/LIBFT/get_next_line/files_gnl/mix_marge2", O_RDONLY)))
//	{
//		printf("\nError in open\n");
//		return (0);
//	}
	while (j < 8)
	{
		if ((i = get_next_line(fd, &line)) > 0)
			printf("1 %d, %s\n", j, line);
		free(line);
		j++;
	}
//	while (j < 13)
//	{
//		if ((i = get_next_line(fd2, &line)) > 0)
//			printf("%s\n", line);
//		free(line);
//		j++;
//	}
	if ((i = get_next_line(fd, &line)) > 0)
		printf("2 %d, %s\n", j, line);
	free(line);
	j++;
////	if ((i = get_next_line(fd2, &line)) > 0)
////		printf("3 %d, %s\n", j, line);
////	free(line);
////	j++;
//	if ((i = get_next_line(fd2, &line)) > 0)
//		printf("4 %d, %s\n", j, line);
//	free(line);
//	j++;
	if ((i = get_next_line(fd, &line)) > 0)
		printf("5 %d, %s\n", j, line);
	free(line);
	j++;
//	if ((i = get_next_line(fd2, &line)) > 0)
//		printf("6 %d, %s\n", j, line);
//	free(line);
//	j++;
	if ((i = get_next_line(fd, &line)) > 0)
		printf("7 %d, %s\n", j, line);
	free(line);
	j++;
//	while (j < 23)
//	{
//		if ((i = get_next_line(fd2, &line)) > 0)
//			printf("8 %d, %s\n", j, line);
//		free(line);
//		j++;
//	}
//	get_next_line(fd2, &line);
//	printf("9 %d, %s\n", j, line);
//	free(line);
//	j++;
	while (j < 25)
	{
		if ((i = get_next_line(fd, &line)) > 0)
			printf("a %d, %s\n", j, line);
		free(line);
		j++;
	}
	get_next_line(fd, &line);
	printf("b %d, %s\n", j, line);
	free(line);
	close(fd);
//	close(fd2);

	if (i == -1)
		printf ("\nError in Fonction - Returned -1\n");
	else if (j == 25)
		printf("\nRight number of lines\n");
	else if (j != 25)
		printf("\nNot Good - Wrong Number Of Lines\n");
return (0);
}

void test2() {
	t_segment *s1 = malloc(sizeof(t_segment));
	t_segment *s2 = malloc(sizeof(t_segment));

	printf("%p, %p, %ld, %ld\n", s1, s2, s2 - s1, ((long) s2) - ((long) s1));
}
int		ym_main()
{
	test3();
	return (0);
}
