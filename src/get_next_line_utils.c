#include <stdlib.h>
#include "get_next_line.h"

#include <stdio.h>
#include <string.h>

void	print(t_segment *segment, char *message)
{
	printf("-----------------------------------------------------------------\n");
	printf("%s\n", message);
	for(int i=0;i<mod_strlen(message);i++)
		printf("-");
	printf("\n");
	printf("sizeof: %lu.\n", sizeof(t_segment));
	printf("str: %s.\n", ymstr(segment->str));
	printf("\t\t\tstatus: %d\n", segment->status);
	printf("\t\t\tnext:%p\n\n", segment->next);
	printf("-----------------------------------------------------------------\n\n");
	fflush(stdout);
}

char wbuffer[500];
char *ymstr(char *str) {
	char *src2;
	if (!str || !*str)
		return str;
	strcpy(wbuffer, str);
	src2  = wbuffer;
	while (*src2) {
		*src2 = '\n' == *src2 ? '@' : *src2;
		src2++;
	}
	return wbuffer;
}

int		indexof(char *str, char c, int start)
{
	int i;

	i = 0;
	while (start--)
		str++;
	if(!str)
		return (-1);
	while (*str)
	{
		if (c == *str)
			return (i);
		i++;
		str++;
	}
	return (-1);
}

int		mod_strlen(char *str)
{
	int i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (*str++)
	{
		i++;
	}
	return (i);
}

int		mod_strlcat(char *dst, char *src, int dst_size, int src_size)
{
	int	i;

	i = 0;
	while (i< src_size)
	{
		dst[dst_size + i] = *src++;
		i++;
	}
	dst[dst_size + i] = 0;
	return (dst_size + src_size);
}

char	*mod_substr(char *s, int start, int len)
{
	char	*pt;
	int		i;

	i = 0;
	if (!(pt = malloc(len * sizeof(char) + 1)))
		return (NULL);
	while (start--)
		s++;
	while (len-- && *s)
		pt[i++] = *s++;
	pt[i] = 0;
	return (pt);
}
