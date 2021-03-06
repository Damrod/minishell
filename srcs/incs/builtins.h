#ifndef BUILTINS_H
# define BUILTINS_H

# include	<minishell.h>
# include	<libft.h>

char	**read_path(char **env);
int		check_path(char **args, char **path, char ***env);
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_cd(char **args, char ***env);
int		ft_env(char **g_term);
int		ft_export(char ***env, char **args);
int		ft_unset(char ***env, char **args);
int		ft_exit(char **args, char ***env, t_dlist *cmd);

#endif
