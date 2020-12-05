#include <stdlib.h>
#include "get_next_line.h"

#include <stdio.h>
#include <string.h>

char *ymstr(char *str) {
	char *src1 = malloc(500);
	char *src2 = src1;

	strcpy(src1, str);
	while (*src1) {
		*src1 = '\n' == *src1 ? '@' : *src1;
		src1++;
	}
	return src2;
}

int		indexof(char *str, char c)
{
	int i;

	i = 0;
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
	if (!str)
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

char	*mod_substr(char *s, unsigned int start, int len)
{
	char	*pt;
	int		i;

	i = 0;
	if (!(pt = malloc(len * sizeof(char) + 1)))
		return (NULL);
	while (start--)
		s++;
	while (len--)
		pt[i++] = *s++;
	pt[i] = 0;
	return (pt);
}

int		line_length(t_segment **segment)
{
	int			len;
	t_segment	*work_segment;
	t_segment	*first_segment;

	len = 0;
	work_segment = *segment;
	while (work_segment)
	{
		len += mod_strlen(work_segment->str);
		first_segment = work_segment;
		work_segment = work_segment->previous;
	}
	*segment = first_segment;
	return (len);
}


