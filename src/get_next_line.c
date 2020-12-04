#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

t_segment	*new_seg (t_segment *pseg, int status, char *str)
{
	t_segment	*segment;
	int			len;

	len = ft_strlen(str);
	if ((segment = malloc(sizeof(t_segment))))
	{
		segment->str = len ? str : malloc(sizeof(char) * len + 1);
		segment->len = len;
		segment->status = str ? status : ERROR;
		segment->previous = pseg;
		if (pseg)
			pseg->next = segment;
		segment->next = NULL;
	}
	return (segment);
}

t_segment	*process_str(char *str, t_segment *lseg, int pos)
{
	int			dst_size;
	int			i;
	char		*dst;
	char		*src;
	t_segment	*wseg;

	i = 0;
	dst = str;
	src = lseg->str;
	dst_size = ft_strlen(str);
	while (i < lseg->len)
		dst[dst_size + i++] = *src++;
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

	nseg = new_seg(NULL, status, ft_substr(lseg->str, pos + 1, lseg->len - pos -1));
	str = ft_substr(lseg->str, 0, pos);
	free(lseg->str);
	lseg->str = str;
	lseg->len = ft_strlen(str);
	len = line_length(&lseg);
	if ((str = malloc(sizeof(char) * (len + 1))))
	{
		while (lseg)
			lseg = process_str(str, lseg, pos);
		str[len + 1] = 0;
	}
	*line++ = str;
	return (nseg);
}

t_segment	*process_segment(int fd, t_segment *lseg, char **line)
{
	int 		pos;

	if ((pos = (NULL == lseg) ? -2 : indexof(lseg->str, EOL)) >  -1)
		lseg = process_line(lseg, LP, pos, line);
	else
	{
		lseg = new_seg(lseg, OK, "");
		if ((lseg->str = malloc(sizeof(char) * BUFFER_SIZE)))
		{
			lseg->len = read(fd, lseg->str, BUFFER_SIZE);
			if (lseg->len)
				lseg = process_segment(fd, lseg, line);
			else
				lseg = process_line(lseg, EOF, 0, line);
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
