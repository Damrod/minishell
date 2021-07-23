#ifndef READ_PATH_H
# define READ_PATH_H

# include "minishell.h"
# include <error_mng.h>

char	*ft_cat_path(char *path, char *arg);
char	*ft_cat_rel_path(char *path, char *arg);
void	ft_makerelat(char **args);

#endif
