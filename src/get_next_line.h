/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-mont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:52:36 by yde-mont          #+#    #+#             */
/*   Updated: 2020/12/08 17:57:30 by yde-mont         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define NOTFOUND -1
# define ERROR -1
# define END 0
# define OK 1
# define FINAL 2
# define CONTINUE 3
# define RC '\n'

typedef struct	s_segment
{
	char				*str;
	struct s_segment	*next;
	int					status;
}				t_segment;

typedef struct	s_file
{
	int			fd;
	int			status;
	t_segment	*fseg;
	t_segment	*lseg;
}				t_file;

int				indexof(char *str, char c, int start);
t_file			*new_tfile(t_file *sfile, int fd);
char			*mod_substr(char *s, int start, int len);
int				mod_strlen(char *str);
int				clear(t_file **sfile, int status);
int				get_next_line(int fd, char **line);

#endif
