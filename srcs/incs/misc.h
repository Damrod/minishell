#ifndef MISC_H
# define MISC_H

# include <libft.h>

void	print_dblptr(const char *input);
int		get_pipes(void *src, void *key);
int		quit_exec(int retstatus, char *sysc, t_dlist *cmds, char ***env);
int		is_internal(char *arg);
void	my_dup2(int oldfd, int newfd, t_dlist *cmds);

#endif
