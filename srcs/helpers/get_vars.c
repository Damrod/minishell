#include <get_vars.h>

static int	join_var2(int i, unsigned short **bitmap, char **var,
	unsigned short **tempbitmap)
{
	int	paracortes;
	int	j;
	int	flags;

	flags = 0;
	flags |= (*bitmap)[i] >> 8;
	paracortes = i;
	i = 0;
	while (i < paracortes)
	{
		(*tempbitmap)[i] = (*bitmap)[i];
		i++;
	}
	paracortes += ft_strlen((*var));
	j = 0;
	while (i + j < paracortes)
	{
		(*tempbitmap)[i + j] = (*var)[j];
		(*tempbitmap)[i + j] |= flags << 8;
		j++;
	}
	return (j);
}

static void	join_var_3(char **var, int *varsize, char **env)
{
	char			*tmp;

	tmp = *var;
	*varsize = ft_strlen(*var);
	if (ft_strlen(*var) == 1 && (*var)[0] == '?')
		*var = ft_itoa(g_lastret);
	else
	{
		if (ft_getenv(*var, env))
			*var = ft_strdup(ft_getenv(*var, env));
		else
			*var = ft_strdup("");
	}
	free(tmp);
}

static int	join_var(unsigned short **bitmap, int i, char **var, char **env)
{
	int				j;
	int				lennew;
	int				varsize;
	unsigned short	*tempbitmap;

	join_var_3(var, &varsize, env);
	lennew = ft_wstrlen(*bitmap, UNTIL_END_OF_STRING) - (varsize + 1)
		+ ft_strlen(*var);
	if (!na_calloc(lennew + 1, sizeof(**bitmap), (void **)&tempbitmap))
		return (-1);
	j = join_var2(i, bitmap, var, &tempbitmap);
	while (i + j < lennew)
	{
		tempbitmap[i + j] = (*bitmap)[i + varsize + 1];
		i++;
	}
	free(*bitmap);
	(*bitmap) = tempbitmap;
	return (1);
}

static int	check_quotes(unsigned short **var, int flags)
{
	int				i;
	int				j;
	unsigned short	*tmp;

	i = 0;
	j = 0;
	while ((char)(*var)[i])
	{
		if (((((*var)[i] >> 8) ^ flags)))
		{
			if (!na_calloc(sizeof(*tmp), i + 1, (void **)&tmp))
				return (-1);
			while (j < i)
			{
				tmp[j] = (*var)[j];
				j++;
			}
			free(*var);
			(*var) = tmp;
			return (j);
		}
		i++;
	}
	return (i);
}

int	swap_var(unsigned short **bitmap, int i, char **env)
{
	unsigned short	*tmp;
	char			*var;
	int				varlen;
	int				j;

	tmp = ft_wstrdup((*bitmap) + i + 1, UNTIL_ANY_SPACE);
	varlen = check_quotes(&tmp, *((*bitmap) + i) >> 8);
	var = malloc(varlen + 1);
	j = 0;
	while (j < varlen)
	{
		var[j] = (char)tmp[j];
		j++;
	}
	free(tmp);
	var[j] = 0;
	if (!join_var(bitmap, i, &var, env))
		return (1);
	j = ft_strlen(var);
	free(var);
	return (j);
}
