#include <env.h>

void	ft_print_env_ordered(char **env)
{
	char	**tmp;
	char	**tmp2;
	int		size;
	int		i;
	t_list	*sorted;

	(void)sorted;
	tmp = ft_dblptr_cpy((const char **)env, NULL, 0);
	size = ft_dblptrlen((void **)env);
	sorted = ft_arrtolst((void **)tmp, size, NULL);
	ft_list_sort(&sorted, ft_strcmp);
	free(tmp);
	tmp = (char **)ft_lsttoarr(sorted, &size);
	while (size--)
	{
		tmp2 = ft_split_ultimate(tmp[size], "=");
		tmp[size] = ft_strjoin_ult(2, (const char **) tmp2, "=\"");
		ft_dblptr_free((void **)tmp2);
	}
	size = ft_dblptrlen((void **)env);
	i = 0;
	while (i < size)
		printf("declare -x %s\"\n", tmp[i++]);
	ft_dblptr_free((void **)tmp);
	ft_lstclear(&sorted, NULL, free);
}

int	check_valid_env_var(char *arg)
{
	if (ft_isdigit(arg[0]))
	{
		ft_dprintf(STDERR_FILENO, "%s: export: `%s': not a valid"
			" identifier\n", EXENAME, arg);
		g_term.lastret = 1;
		return (1);
	}
	return (0);
}

int	ft_check_replace(char **varval, char ***env, int i)
{
	int	j;
	int	k;

	j = ft_strlen(varval[0]);
	if (ft_strncmp(varval[0], (*env)[i], j) == 0 && (*env)[i][j] == '=')
	{
		free((*env)[i]);
		(*env)[i] = malloc(j + ft_strlen(varval[1]) + 2);
		j = 0;
		while (varval[0][j])
		{
			(*env)[i][j] = varval[0][j];
			j++;
		}
		(*env)[i][j++] = '=';
		k = 0;
		while (varval[1][k])
			(*env)[i][j++] = varval[1][k++];
		(*env)[i][j] = 0;
		return (1);
	}
	return (0);
}

int	ft_env(char **env)
{
	ft_dblptr_foreach(env, print_dblptr);
	return (0);
}
