#ifndef ENV_H
# define ENV_H

# include <builtins.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <minishell.h>
# include <libft.h>

void	print_dblptr(const char *input);
void	ft_print_env_ordered(char **env);
int		check_valid_env_var(char *arg);
int		ft_check_replace(char **varval, char ***env, int i);
char	**add_env(char ***env, char **varval);
int		ft_set_varval(char ***varval, char *arg);
int		add_var_env(char *arg, char ***env);
int		ft_export(char ***env, char **args);
int		ft_env(char **env);
void	rm_env_var(char ***env, int i);
int		check_env_var(char *var, char ***env);
int		ft_unset(char ***env, char **args);
int		check_exit_arg(int num, char **args);
int		ft_exit(char **args);
char	*ft_getenv(const char *name);

#endif
