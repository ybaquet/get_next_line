#include <stdlib.h>
#include "get_next_line.h"

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

char	*ft_substr(char *s, unsigned int start, int len)
{
	int		s_size;
	int		pt_size;
	char	*pt;
	int		i;

	i = 0;
	s_size = mod_strlen(s);
	if (s_size <= start)
	{
		if (!(pt = malloc(sizeof(char))))
			return (NULL);
		*pt = 0;
		return (pt);
	}
	pt_size = (len + start > s_size ? s_size - start : len);
	if (!(pt = malloc(pt_size * sizeof(char) + 1)))
		return (NULL);
	while (start--)
		s++;
	while (pt_size--)
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


