#include <minishell.h>
#include <env.h>
#include <error_mng.h>
#include <wstrcmp.h>
#include <get_vars.h>
#include <get_quotes.h>

t_list	*ft_wstrsplit(unsigned short *bitmap)
{
	size_t			i;
	size_t			size;
	t_list			*ret;
	unsigned short	*tmp;

	ret = NULL;
	size = 1;
	i = 0;
	while (bitmap[i])
	{
		if (!is_anytoken(bitmap[i]))
			tmp = ft_wstrdup(&bitmap[i], UNTIL_ANY_ENDOFTOKEN);
		else
			tmp = get_token(&bitmap[i]);
		ft_lstpush_back(&ret, tmp);
		i += ft_wstrlen(tmp, UNTIL_END_OF_STRING);
		while (bitmap[i] && !(bitmap[i] & 0xFF00))
			i++;
		size++;
	}
	return (ret);
}

int	substitute_var(unsigned short **bitmap)
{
	int	i;

	i = 0;
	while ((*bitmap)[i])
	{
		if ((char)(*bitmap)[i] == '$' && !((*bitmap)[i] & FLAG_SNGQUOT))
			i += swap_var(bitmap, i);
		if ((*bitmap)[i])
			i++;
	}
	return (ft_wstrlen((*bitmap), UNTIL_END_OF_STRING));
}

t_list	*get_args(const char *arg)
{
	size_t			len;
	unsigned short	*bitmap;
	char			*args;
	unsigned short	*tmp;
	t_list			*retreal;

	if (!arg)
		return (NULL);
	args = ft_strtrim(arg, " \f\n\r\t\v");
	if (!args)
		return (clean_ptr((void **)&args, NULL, NULL, NULL));
	len = ft_strlen(args);
	if (len == 0 || !na_calloc(len + 1, sizeof(*bitmap), (void **)&bitmap))
		return (clean_ptr((void **)&args, NULL, NULL, NULL));
	upcast_config(bitmap, args, 0, 0);
	free (args);
	tmp = ft_wstrdup(bitmap, UNTIL_END_OF_STRING);
	if (!tmp)
		return (NULL);
	free(bitmap);
	bitmap = tmp;
	len = substitute_var(&bitmap);
	retreal = ft_wstrsplit(bitmap);
	free (bitmap);
	return (retreal);
}
