#include "env.h"

void	rm_env_var(char ***env, int i)
{
	t_list	*lst;
	int		len;
	char	*pattmask;
	char	**tmp;

	len = ft_dblptrlen((void **)*env);
	if (!na_calloc(len, sizeof(char), (void **)&pattmask))
		return ;
	ft_memset(pattmask, '\0', len);
	lst = ft_arrtolst((void **)*env, -1, NULL);
	pattmask[i] = 1;
	ft_lstcullpat(&lst, pattmask, free, free);
	tmp = *env;
	*env = (char **)ft_lsttoarr(lst, NULL);
	free (pattmask);
	ft_lstclear(&lst, NULL, free);
	free (tmp);
}

int	check_env_var(char *var, char ***env)
{
	int	i;
	int	size;

	size = ft_strlen(var);
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp(var, (*env)[i], size) == 0 && (*env)[i][size] == '=')
		{
			rm_env_var(env, i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_unset(char ***env, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (check_env_var(args[i], env))
			i++;
	}
	return (0);
}
