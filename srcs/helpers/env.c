#include <env.h>

static int	ft_getvalue(const char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;

	if (!ft_strchr(s2, '='))
		return (-1);
	len1 = ft_strlen(s1);
	len2 = ft_strchr(s2, '=') - s2;
	if (len1 < len2)
		len1 = len2;
	return (ft_strncmp(s1, s2, len1));
}

char	*ft_getenv(const char *name)
{
	size_t	i;

	i = 0;
	while (g_term.environ[i])
	{
		if (ft_getvalue(name, g_term.environ[i]) == 0)
			return (ft_strchr(g_term.environ[i], '=') + 1);
		i++;
	}
	return (NULL);
}

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
	{
		printf("declare -x %s\"\n", tmp[i++]);
	}
	ft_dblptr_free((void **)tmp);
	ft_lstclear(&sorted, NULL, free);
}

int	check_valid_env_var(char **varval, char *arg, char ***env)
{
	(void)env;
	if (ft_isdigit(varval[0][0]))
	{
		printf("bash: export: \'%s:\' bit a valid identifier\n", arg);
		ft_dblptr_free((void **)varval);
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

char	**add_env(char ***env, char **varval)
{
	char	*varvaltoenv;
	char	**tmp;

	tmp = *env;
	varvaltoenv = ft_strjoin_ult(2, (const char **) varval, "=");
	*env = ft_dblptr_cpy((const char **)(*env), varvaltoenv, 0);
	free (tmp);
	return (*env);
}

static int	gotochar(char *arg, char a)
{
	int	i;

	i = 0;
	while (arg[i] != a)
		i++;
	return (i);
}

int	ft_set_varval(char ***varval, char *arg)
{
	int	i;

	if (arg[0] == '=')
	{
		printf("bash: export: '%s': not a valid identifier\n", arg);
		return (1);
	}
	i = gotochar(arg, '=');
	if (arg[i] == '=' && !arg[i + 1])
	{
		(*varval) = malloc(sizeof(char *) * 2);
		(*varval)[0] = malloc(ft_strlen(arg));
		i = 0;
		while (arg[i] != '=')
		{
			(*varval)[0][i] = arg[i];
			i++;
		}
		(*varval)[0][i] = 0;
		(*varval)[1] = ft_strdup("");
	}
	else
		(*varval) = ft_split_ultimate(arg, "=");
	return (0);
}

int	add_var_env(char *arg, char ***env)
{
	char	**varval;
	int		i;

	if (ft_set_varval(&varval, arg))
		return (1);
	if (check_valid_env_var(varval, arg, env))
		return (1);
	i = 0;
	while ((*env)[i] != NULL)
	{
		if (ft_check_replace(varval, env, i))
			break ;
		i++;
	}
	if (!(*env)[i])
		*env = add_env(env, varval);
	ft_dblptr_free((void **)varval);
	return (0);
}

int	ft_export(char ***env, char **args)
{
	int	i;
	int	j;
	int	ret;

	ret = 0;
	if (!args[1])
		ft_print_env_ordered(*env);
	else
	{
		j = 0;
		while (args[j])
		{
			i = 0;
			while (args[j][i])
			{
				if (args[j][i] == '=')
				{
					ret = add_var_env(args[j], env);
				}
				i++;
			}
			j++;
		}
	}
	return (ret);
}

void	ft_dblptr_foreach(char **data, void (*f)());

int	ft_env(char **env)
{
	ft_dblptr_foreach(env, print_dblptr);
	return (0);
}

/// unset

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

//exit

void	check_exit_arg(int num, char **args)
{
	int	i;

	i = 0;
	if (ft_strncmp(args[1], "-", 1) == 0)
		i++;
	while (args[1][i])
	{
		if (ft_isdigit(args[1][i]) != 1)
		{
			ft_dprintf(2, "%s: exit: %s: numeric argument required\n", EXENAME,
				args[1]);
			exit(2);
		}
		i++;
	}
	i = 0;
	while (args[++i])
		;
	if (i > 2)
		ft_dprintf(2, "%s: exit: too many arguments\n", EXENAME);
	else
		exit (num);
}

int	ft_exit(char **args)
{
	int	i;

	printf("exit\n");
	if (args[1])
	{
		i = ft_atoi(args[1]);
		check_exit_arg(i, args);
	}
	else
		exit (g_term.lastret);
	return (0);
}
