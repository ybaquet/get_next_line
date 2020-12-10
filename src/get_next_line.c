/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-mont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:58:05 by yde-mont          #+#    #+#             */
/*   Updated: 2020/12/08 18:02:47 by yde-mont         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

int		process_buffer(t_file *sfile, char *str, int len)
{
	int			pos;
	int			start;
	t_segment	*segment;

	pos = 0;
	start = 0;
	while (NOTFOUND != pos)
	{
		pos = indexof(str, '\n', start);
		if (!(segment = (t_segment *)malloc(sizeof(t_segment))))
			return (ERROR);
		segment->str = mod_substr(str, start, (-1 == pos) ? len : pos);
		segment->next = NULL;
		sfile->fseg = (sfile->fseg) ? sfile->fseg : segment;
		if (sfile->lseg)
			sfile->lseg->next = segment;
		sfile->lseg = segment;
		segment->status = (-1 == pos) ? CONTINUE : FINAL;
		sfile->status = (FINAL == segment->status) ? FINAL : sfile->status;
		start = start + pos + 1;
	}
	return (OK);
}

void	supply_str(int status, t_segment *seg, char *str)
{
	char		*s;

	while (CONTINUE == status && seg)
	{
		s = seg->str;
		while ((*str = *s++))
			str++;
		status = seg->status;
		seg = seg->next;
	}
	*str = 0;
}

int		process_line(t_file *sfile, char **line)
{
	int			len;
	t_segment	*seg;
	char		*str;
	int			status;

	if (ERROR == sfile->status)
		return (ERROR);
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
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (clear(sfile, ERROR));
	*line = str;
	seg = sfile->fseg;
	supply_str(status, seg, str);
	return (clear(sfile, CONTINUE));
}

int		get_next_line(int fd, char **line)
{
	static t_file	*sfile = NULL;
	char			*str;
	int				len;

	sfile = (sfile) ? sfile : new_tfile(fd);
	if (!sfile || 0 >= BUFFER_SIZE || fd != sfile->fd || 0 > fd || 1023 < fd)
		return (ERROR);
	while (CONTINUE == sfile->status)
	{
		if (!(str = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
			return (clear(sfile, ERROR));
		if ((len = read(sfile->fd, str, BUFFER_SIZE)) > 0)
		{
			str[len] = 0;
			if (ERROR == process_buffer(sfile, str, len))
				return (clear(sfile, ERROR));
		}
		else
			sfile->status = (0 == len) ? END : ERROR;
		str[len] = 0;
		free(str);
	}
	return (process_line(sfile, line));
}
