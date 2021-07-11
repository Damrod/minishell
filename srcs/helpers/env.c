#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//join2
static size_t	dblptrlen(const char **strs)
{
	const char	**last;

	last = strs;
	while (*last)
		last++;
	return ((size_t)(last - strs));
}

static size_t	ft_strlen_ult(ssize_t *size, const char **str)
{
	size_t	i;
	size_t	resul;

	if (*size < 0)
		*size = (signed)dblptrlen(str);
	if (*size == 0 || *str == NULL)
		return (0);
	resul = 0;
	i = 0;
	while (i < (unsigned) *size)
	{
//check aqui
		if(*(str + i))
			resul += ft_strlen(*(str + i));
		i++;
	}
	return (resul);
}

static void	*malloc_mng(ssize_t *size, const char **strs, const char *sep)
{
	char	*resul;
	int		fnl_pad;
	size_t	totsz;

	if (!strs || !*strs)
		return (NULL);
	if (*size != 0)
		fnl_pad = ft_strlen(sep);
	else
		fnl_pad = 0;
	totsz = ft_strlen_ult(size, strs) + (*size - 1) * fnl_pad;
	resul = malloc(sizeof(char) * totsz + 1);
	if (!resul)
		return (NULL);
	ft_memset(resul, '\0', totsz + 1);
	return (resul);
}

char	*ft_strjoin_ult2(ssize_t sz, const char **strs, const char *sep)
{
	char	*res;
	ssize_t	i;
	size_t	aux;

	if (!strs || !*strs)
		return (NULL);
	res = malloc_mng(&sz, strs, sep);
	if (!res)
		return (NULL);
	if (sz == 0)
	{
		*res = '\0';
		return (res);
	}
	aux = 0;
	i = 0;
	while (i < sz - 1)
	{

		aux = ft_strlcat(res, strs[i], ft_strlen(res) + ft_strlen(strs[i]) + 1);
		aux = ft_strlcat(res, sep, aux + ft_strlen(sep) + 1);
		i++;
	}
//check aqui
	if(strs[i])
		ft_strlcat(res, strs[i], aux + ft_strlen(strs[i]) + 1);
	return (res);
}

//export

//esto a libft o common(?)
static int	ft_strcmp(char *s1, char *s2)
{
	while (*s2 == *s1 && *s1)
	{
		s2++;
		s1++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	ft_print_env_ordered(char **env)
{
	char	**tmp;
	char	**tmp2;
	int		size;
	t_list	*sorted;

	(void)sorted;
	tmp = ft_dblptr_cpy((const char **)env, NULL, 0);
	size = ft_dblptrlen((void **)env);
	sorted = ft_arrtolst((void **)tmp, size, NULL);
	ft_list_sort(&sorted, ft_strcmp);
	tmp = (char **)ft_lsttoarr(sorted, &size);
	while (size--)
	{
		tmp2 = ft_split_ultimate(tmp[size], "=");
printf("PETAAQUI\n");
		tmp[size] = ft_strjoin_ult2(2, (const char **) tmp2, "=\"");
printf("NO\n");
	}
	size = ft_dblptrlen((void **)env);
	while (size--)
	{
		printf("declare -x %s\"\n", tmp[size]);
	}
}

int	check_valid_env_var(char **varval, char *arg, char ***env)
{
(void)env;
	if (ft_isdigit(varval[0][0]))
	{
		printf("bash: export: \'%s:\' bit a valid identifier\n", arg);
		ft_dblptr_free((void **)varval);
//		g_term.status = 1;
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

	varvaltoenv = ft_strjoin_ult(2, (const char **) varval, "=");
	return (ft_dblptr_cpy((const char **)(*env), varvaltoenv, 0));
}

int	ft_set_varval(char ***varval, char *arg)
{
	int i;

	if(arg[0] == '=')
	{
		printf("ENTRAENESTOnovar izquierda\n");
		printf("bash: export: '%s': not a valid identifier\n", arg);
		return (1);
	}
	i = 0;
	while(arg[i] != '=')
		i++;
	if(arg[i] == '=' && !arg[i + 1])
	{
		printf("ENTRAENESTOnovar derecha\n");

		(*varval) = malloc(sizeof(char *) * 2);
		(*varval)[0] = malloc(ft_strlen(arg));
		i = 0;
		while(arg[i] != '=')
		{
			(*varval)[0][i] = arg[i];
			i++;
		}
		(*varval)[0][i] = 0;
		(*varval)[1] = ft_strdup("");
	}
	else
	{
		(*varval) = ft_split_ultimate(arg, "=");
		printf("ENTRAENESTO\n");
	}
	return (0);
}

void	add_var_env(char *arg, char ***env)
{
	char	**varval;
	int		i;

	printf("nocrash\n");
	if (ft_set_varval(&varval, arg))
		return;
	if (check_valid_env_var(varval, arg, env))
		return ;
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
}

int	ft_export(char ***env, t_term *g_term)
{
	int	i;
	int	j;

	if (!g_term->args[1])
		ft_print_env_ordered(*env);
	else
	{
		j = 0;
		while (g_term->args[j])
		{
			i = 0;
			while (g_term->args[j][i])
			{
				if (g_term->args[j][i] == '=')
				{
					add_var_env(g_term->args[j], env);
				}
				i++;
			}
			j++;
		}
	}
	return (0);
}

int	ft_env(char **env)
{
	apply_dblptr(env, print_dblptr);
	return (0);
}

/// unset

void	rm_env_var(char ***env, int i)
{
	int		size;
	t_list	*lst;
	t_list	*todel;
	t_list	*prev;

	size = ft_dblptrlen((void **)*env);
	lst = ft_arrtolst((void **)*env, size, NULL);
	todel = lst;
	while (i--)
	{
		prev = todel;
		todel = todel->next;
	}
	prev->next = todel->next;
	ft_lstdelone(todel, free, free);
	size--;
	*env = (char **)ft_lsttoarr(lst, &size);
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

int	ft_unset(char ***env, t_term *g_term)
{
	int	i;

	i = 0;
	while (g_term->args[i])
	{
		if (check_env_var(g_term->args[i], env))
			i++;
	}
	return (0);
}

//exit

void	check_exit_arg(int num, t_term *g_term)
{
	int	i;

	i = 0;
	if (ft_strncmp(g_term->args[1], "-", 1) == 0)
		i++;
	while (g_term->args[1][i])
	{
		if (ft_isdigit(g_term->args[1][i]) != 1)
		{
			printf("bash: exit: %s: numeric argument required\n",
				g_term->args[1]);
			exit(255);
		}
		i++;
	}
	i = 0;
	while (g_term->args[++i])
		;
	if (i > 2)
		printf("bash: exit: too many arguments\n");
	else
		exit (num);
}

int	ft_exit(t_term *g_term)
{
	int	i;

	printf("exit\n");
	if (g_term->args[1])
	{
		i = ft_atoi(g_term->args[1]);
		check_exit_arg(i, g_term);
	}
	else
//exit con el estado actual, para hacer
		exit (0);
	return (0);
}
