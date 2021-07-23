#ifndef WSTRCMP_H
# define WSTRCMP_H

# include <stdlib.h>
# include <libft.h>

char			is_anytoken(unsigned short str);
unsigned short	cmp_space(const unsigned short str, char is_untilspace);
size_t			ft_wstrlen(const unsigned short *str, char is_untilspace);
char			**downcast_dblwstr(t_dlist **args);
char			*downcast_wstr(const unsigned short *str, char is_low);
int				ft_wstrncmp(unsigned short *s1, const char *str2,
					char checkdepth, size_t n);
unsigned short	*ft_wstrdup(const unsigned short *str, char is_untilspace);
unsigned short	*upcast_str(const char *args);

#endif
