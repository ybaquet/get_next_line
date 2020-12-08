#include "get_next_line.h"
#include <stdlib.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>

static t_file *new_tfile(int fd)
{
	t_file	*sfile;

	sfile = malloc(sizeof(t_file));
	sfile->fd = fd;
	sfile->fseg = NULL;
	sfile->lseg = NULL;
	sfile->status = CONTINUE;
	return (sfile);
}

int	process_buffer(t_file *sfile, char **line, char *str, int len)
{
	int		pos;
	int		start;
	t_segment *segment;

	pos = 0;
	start = 0;
	while (NOTFOUND != pos)
	{
		pos = indexof(str, '\n', start);
		if (!(segment = malloc(sizeof(t_segment))))
			return (ERROR);
		segment->str = mod_substr(str, start, (-1 == pos) ? len : pos);
		segment->next = NULL;
		sfile->fseg = (sfile->fseg) ? sfile->fseg : segment;
		if (sfile->lseg)
			sfile->lseg->next = segment;
		sfile->lseg = segment;
		segment->status = (-1 == pos) ? CONTINUE : EOS;
		sfile->status = (EOS == segment->status) ? EOS : sfile->status;
		start = start + pos + 1;
	}
	return (OK);
}

int clear(t_file *sfile, int status)
{
	t_segment *seg;
	t_segment *nseg;

	seg = sfile->fseg;
	while (seg && (ERROR == status || CONTINUE == status))
	{
		status = (ERROR == status) ? ERROR : seg->status;
		nseg = seg->next;
		free(seg->str);
		free(seg);
		seg = nseg;
		sfile->fseg = seg;
	}
	if (ERROR == status)
		return (ERROR);
	if (!seg)
		return (0);
	sfile->status = seg->status;
	return (1);
}

int process_line (t_file *sfile, char **line)
{
	int			len;
	t_segment	*seg;
	char		*str;
	char		*s;
	int			status;

	len = 0;
	status = CONTINUE;
	seg = sfile->fseg;
	while (CONTINUE == status && seg)
	{
		len = len + mod_strlen(seg->str);
		status = seg->status;
		seg = seg->next;
	}
	status = CONTINUE;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return clear(sfile, ERROR);
	*line = str;
	seg = sfile->fseg;
	while(CONTINUE == status && seg)
	{
		s = seg->str;
		while((*str = *s++))
			str++;
		status = seg->status;
		seg = seg->next;
	}
	*str=0;
	return (clear(sfile, CONTINUE));
}

int get_next_line(int fd, char **line)
{
	static int noline = 0;
	static t_file		*sfile = NULL;
	char	*str;
	int		len;

	sfile = sfile ? sfile : new_tfile(fd);
	noline++;
	t_file *ss = sfile;
	if (9 == noline)
		printf("line:%d, status:%d\n", noline, ss->status);
	while (CONTINUE == sfile->status) {
		if (!(str = malloc(sizeof(char) * BUFFER_SIZE + 1)))
			return (clear(sfile, ERROR));
		len = read(sfile->fd, str, BUFFER_SIZE);
		if (len) {
			str[len] = 0;
			if (ERROR == process_buffer(sfile, line, str, len))
				return (clear(sfile, ERROR));
		} else
			sfile->status = END;
		str[len] = 0;
		free(str);
	}
	return (process_line(sfile, line));
}

