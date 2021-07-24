#include "env.h"

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
		ft_dprintf(STDERR_FILENO, "%s: export: `%s': not a valid identifier\n",
			EXENAME, arg);
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

	if (check_valid_env_var(arg))
		return (1);
	if (ft_strchr(arg, '='))
	{
		if (ft_set_varval(&varval, arg))
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
	return (1);
}

int	ft_export(char ***env, char **args)
{
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
			ret = add_var_env(args[j], env);
			j++;
		}
	}
	return (ret);
}
