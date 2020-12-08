#include "get_next_line.h"
#include <stdlib.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>

t_segment	*new_seg (t_segment *pseg, int status, char *str)
{
	t_segment	*segment;
	int			len;

	if ((segment = malloc(sizeof(t_segment))))
	{
		len = NULL == str ? 0 : mod_strlen(str);
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
	lseg->str = NULL;
	wseg = lseg;
	lseg = lseg->next;
	free(wseg);
	return (lseg);
}

t_segment		*process_line(t_segment *lseg, int status, int pos, char **line)
{
	t_segment	*nseg;
	char		*str;
	int			len;

	str = lseg->str;
	nseg = new_seg(NULL, status, mod_substr(lseg->str, pos + 1, lseg->len - pos - 1));
	printf("str 1:<%s>, <%s>, pos:%d, %p, %p, %ld\n", ymstr(str), ymstr(lseg->str), pos, str, lseg->str, ((long)str) - ((long)lseg->str));
	fflush(stdout);
	lseg->str = mod_substr(lseg->str, 0, pos);
	printf("str 2:<%s>, <%s>, pos:%d, %p, %p, %ld\n", ymstr(str), ymstr(lseg->str), pos, str, lseg->str, ((long)str) - ((long)lseg->str));
	lseg->len = mod_strlen(lseg->str);
	len = line_length(&lseg);
	free(str);
	printf("OK\n");
	fflush(stdout);
	str = NULL;
	if ((str = malloc(sizeof(char) * (len + 1))))
	{
		while (lseg)
			lseg = process_str(str, lseg);
		str[len + 1] = 0;
	}
	else
		nseg->status = ERROR;
	*line++ = str;
	return (nseg);
}

t_segment	*process_segment(int fd, t_segment *lseg, char **line)
{
	int 		pos;

	if ((pos = (NULL == lseg) ? -2 : indexof(lseg->str, RC)) >  -1) {
		lseg = process_line(lseg, LP, pos, line);
	} else
	{
		lseg = new_seg(lseg, OK, NULL);
		if ((lseg->str = malloc(sizeof(char) * BUFFER_SIZE + 1)))
		{
			lseg->len = read(fd, lseg->str, BUFFER_SIZE);

			char *str2 = malloc(lseg->len + 1);
			strcpy(str2, lseg->str);
			lseg->str = str2;

			lseg->str[lseg->len + 1] = 0;
			if (lseg->len) {
				lseg = process_segment(fd, lseg, line);
			} else {
				if (!lseg->str)
					lseg = process_line(lseg, END, 0, line);
			}
		}
		else
			lseg->status = ERROR;
	}
	return (lseg);
}

int get_next_line(int fd, char **line)
{
	static t_segment	*lseg = NULL;
	// A supprimer
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
