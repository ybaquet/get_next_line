#ifndef GET_NEXT_LINE

# define GET_NEXT_LINE

#include <stdlib.h>

# define ERROR -1
# define EOF 0
# define EOL '\n'
# define LP -999
# define OK 1

typedef struct s_segment
{
	char				*str;
	struct s_segment	*previous;
	struct s_segment	*next;
	int					len;
	int					status;
} t_segment;

int		indexof(char *str, char c);
int		mod_strlcat(char *dst, char *src, int dst_size, int src_size);
char	*ft_substr(char *s, unsigned int start, int len);
int		ft_strlen(char *str);
int		get_next_line(int fd, char **line);
int		line_length(t_segment **segment);

#endif
