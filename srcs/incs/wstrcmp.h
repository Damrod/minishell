#ifndef WSTRCMP_H
# define WSTRCMP_H

# include <stdlib.h>
# include <libft.h>

char	**downcast_dblwstr(t_dlist **args);
char	*downcast_wstr(const unsigned short *str, char is_low);
int		ft_wstrncmp(unsigned short *s1, const char *str2,
			char checkdepth, size_t n);

#endif
