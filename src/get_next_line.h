#ifndef GET_NEXT_LINE

# define GET_NEXT_LINE

#include <stdlib.h>

# define ERROR -1
# define END 0
# define RC '\n'
# define LP -999
# define OK 1

typedef struct s_segment
{
	char				*str;
	struct s_segment	*previous;
	struct s_segment	*next;
	int					len;
	int					status;
	int	a_supprimer;
} t_segment;

int		indexof(char *str, char c);
int		mod_strlcat(char *dst, char *src, int dst_size, int src_size);
char	*mod_substr(char *s, int start, int len);
int		mod_strlen(char *str);
int		get_next_line(int fd, char **line);
int		line_length(t_segment **segment);

// A supprimer
void print(t_segment *segment, char *message);
char *ymstr(char *str);
void ft_putchar(char c);
void ft_putstr(char *str);
void ft_putnbr(int nb);


#endif
