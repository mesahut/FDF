#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 9999

# endif

char	*ft_calloc(int nmemb, int size);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
int		ft_get_strchr(const char *s);
int		ft_strlen(const char *s);

#endif