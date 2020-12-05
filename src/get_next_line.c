#include "get_next_line.h"
#include <stdlib.h>

#include <unistd.h>
#include <stdio.h>
char *ymstr(char *str);

t_segment	*new_seg (t_segment *pseg, int status, char *str)
{
	t_segment	*segment;
	int			len;

	if ((segment = malloc(sizeof(t_segment))))
	{
		len = mod_strlen(str);
		segment->str = len ? str : NULL;
		segment->len = len;
		segment->status = str ? status : ERROR;
		segment->previous = pseg;
		if (pseg)
			pseg->next = segment;
		segment->next = NULL;
	}
	return (segment);
}

t_segment	*process_str(char *str, t_segment *lseg)
{
	int			dst_size;
	int			i;
	t_segment	*wseg;

	dst_size = mod_strlen(str);
	i = 0;
	while (i < lseg->len)
	{
		str[dst_size + i] = lseg->str[i];
		i++;
	}
	str[dst_size + i] = 0;
	free(lseg->str);
	wseg = lseg;
	lseg = lseg->next;
	free(wseg);
	return (wseg->next);
}

t_segment		*process_line(t_segment *lseg, int status, int pos, char **line)
{
	t_segment	*nseg;
	char		*str;
	int			len;

	nseg = new_seg(NULL, status, mod_substr(lseg->str, pos + 1, lseg->len - pos - 1));
	if (*(lseg->str) == '3')
		printf("toto");
	str = mod_substr(lseg->str, 0, pos);
//		printf("B1 <%s> %d, %dn", ymstr(lseg->str), pos, mod_strlen(str));
	if (lseg->len != mod_strlen(lseg->str))
		printf("V2 <%s>, %d, %d\n", ymstr(lseg->str), lseg->len, mod_strlen(lseg->str));
	free(lseg->str);
	lseg->str = str;
	lseg->len = mod_strlen(str);
	len = line_length(&lseg);
	if ((str = malloc(sizeof(char) * (len + 1))))
	{
		while (lseg)
			lseg = process_str(str, lseg);
		str[len + 1] = 0;
		printf("V1 <%s>, %d, %d\n", ymstr(str), len, mod_strlen(str));
	}
	else
		nseg->status = ERROR;
	*line++ = str;
	return (nseg);
}

t_segment	*process_segment(int fd, t_segment *lseg, char **line)
{
	int 		pos;

	if ((pos = (NULL == lseg) ? -2 : indexof(lseg->str, RC)) >  -1)
		lseg = process_line(lseg, LP, pos, line);
	else
	{
		lseg = new_seg(lseg, OK, NULL);
		if ((lseg->str = malloc(sizeof(char) * BUFFER_SIZE)))
		{
			lseg->len = read(fd, lseg->str, BUFFER_SIZE);
			if (lseg->len)
				lseg = process_segment(fd, lseg, line);
			else
				lseg = process_line(lseg, END, 0, line);
		}
		else
			lseg->status = ERROR;
	}
	return (lseg);
}

int get_next_line(int fd, char **line)
{
	static t_segment	*lseg = NULL;
	t_segment			*debug_seg;

	debug_seg = lseg;
	while (!debug_seg || 0 < debug_seg->status)
	{
		debug_seg = process_segment(fd, debug_seg, line);
		lseg = debug_seg;
	}
	if (LP == lseg->status)
		lseg->status = OK;
	return (lseg->status >  0);
}
