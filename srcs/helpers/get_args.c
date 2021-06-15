#include <minishell0.h>

char	cmp_space(const unsigned short str, char is_untilspace)
{
	if (is_untilspace < UNTIL_ANY_SPACE)
		return (1);
	else
		return (!ft_isspace(str & 0xFF));
}

size_t	ft_wstrlen(const unsigned short *str, char is_untilspace)
{
	size_t			i;
	size_t			len;
	unsigned short	bitmask;

	bitmask = 0xFFFFU;
	if (is_untilspace == UNTIL_NON_QUOTED_SPACE)
		bitmask = 0xFF00U;
	i = 0;
	len = 0;
	while (str[i] & bitmask && cmp_space(str[i], is_untilspace))
	{
		if (!(str[i] & FLAG_CIGNORE))
			len++;
		i++;
	}
	return (len);
}

unsigned short	*ft_wstrdup(const unsigned short *str, char is_untilspace)
{
	unsigned short	*result;
	size_t			len;
	size_t			i;
	unsigned short	bitmask;

	len = ft_wstrlen(str, is_untilspace);
	if (!na_calloc(sizeof(*result), len + 1, (void **)&result))
		return (NULL);
	i = 0;
	len = 0;
	bitmask = 0xFFFFU;
	if (is_untilspace == UNTIL_NON_QUOTED_SPACE)
		bitmask = 0xFF00U;
	while (str[i] & bitmask && cmp_space(str[i], is_untilspace))
	{
		if (!(str[i] & FLAG_CIGNORE))
			result[len++] = str[i];
		i++;
	}
	return (result);
}

char	isquote_not_nested_not_escaped(unsigned short c, char is_dblquotes)
{
	char			cmp;
	unsigned short	flag;

	cmp = '\'';
	flag = FLAG_SNGQUOT;
	if (is_dblquotes)
	{
		cmp = '"';
		flag = FLAG_DBLQUOT;
	}
	if ((((c & 0xFF00) == (FLAG_NOTSPCE | flag))
			|| ((c & 0xFF00) == FLAG_NOTSPCE)) && ((c & 0xFF) == (short)cmp))
		return (1);
	return (0);
}

void	*ft_realloc(void *ptr, size_t originalsize, size_t newsize)
{
	void	*newptr;

	if (newsize == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return (malloc(newsize));
	else if (newsize <= originalsize)
		return (ptr);
	else
	{
		newptr = ft_calloc(newsize, sizeof(char));
		if (newptr)
		{
			ft_memcpy(newptr, ptr, originalsize);
			free(ptr);
		}
		return (newptr);
	}
}

void	freedblptr(void **ptrs)
{
	void	**orig;

	orig = ptrs;
	while (*ptrs)
	{
		free (*ptrs);
		ptrs++;
	}
	free(orig);
	return ;
}

unsigned short	**ft_wstrsplit(unsigned short *bitmap)
{
	size_t			i;
	size_t			size;
	unsigned short	**ret;
	unsigned short	**tmp;

	ret = NULL;
	size = 1;
	i = 0;
	while (bitmap[i])
	{
		tmp = ft_realloc(ret, size * sizeof(*tmp), (size + 1) * sizeof(*tmp));
		if (!tmp)
		{
			freedblptr((void **)ret);
			return (NULL);
		}
		ret = tmp;
		ret[size - 1] = ft_wstrdup(&bitmap[i], UNTIL_NON_QUOTED_SPACE);
		i += ft_wstrlen(ret[size - 1], UNTIL_NON_QUOTED_SPACE);
		while (bitmap[i] && !(bitmap[i] & 0xFF00))
			i++;
		size++;
		ret[size - 1] = NULL;
	}
	return (ret);
}

void	config_quotes(unsigned short *map, unsigned short *prev_dbl,
			unsigned short *prev_sng, size_t sz)
{
	size_t	i;

	if (sz > 0 && (map[sz - 1] & 0xFF) != '"' && (map[sz - 1] & FLAG_DBLQUOT))
	{
		(*prev_dbl) |= FLAG_ESCAPED;
		i = 0;
		while (prev_dbl[i])
			prev_dbl[i++] &= ~FLAG_DBLQUOT;
	}
	if (sz > 0 && (map[sz - 1] & 0xFF) != '\'' && (map[sz - 1] & FLAG_SNGQUOT))
	{
		(*prev_sng) |= FLAG_ESCAPED;
		i = 0;
		while (prev_sng[i])
			prev_sng[i++] &= ~FLAG_SNGQUOT;
	}
	i = 0;
	while (map[i])
	{
		if (isquote_not_nested_not_escaped(map[i], 0)
			|| isquote_not_nested_not_escaped(map[i], 1))
			map[i] |= FLAG_CIGNORE;
		i++;
	}
}

ssize_t	toggle_inside_quote(ssize_t insideother, ssize_t *selfinside,
			unsigned short bitmap, char is_single)
{
	char	cmp;

	cmp = '"';
	if (is_single)
		cmp = '\'';
	if (!insideother && (bitmap & ~FLAG_NOTSPCE) == (short) cmp)
		*selfinside ^= 1;
	return (*selfinside);
}

void	upcast_config(unsigned short *bitmap, char *args, ssize_t inside_sng,
			ssize_t inside_dbl)
{
	ssize_t			i;
	unsigned short	*prev_dbl;
	unsigned short	*prev_sng;

	i = 0;
	while (args[i])
	{
		bitmap[i] |= args[i];
		if (!ft_isspace(bitmap[i] & 0xFF))
			bitmap[i] |= FLAG_NOTSPCE;
		if (!toggle_inside_quote(inside_sng, &inside_dbl, bitmap[i], 0))
			toggle_inside_quote(inside_dbl, &inside_sng, bitmap[i], 1);
		if (inside_dbl)
			bitmap[i] |= FLAG_DBLQUOT;
		if (inside_sng)
			bitmap[i] |= FLAG_SNGQUOT;
		if ((bitmap[i] & 0xFF) == '\'')
			prev_sng = &bitmap[i];
		if ((bitmap[i] & 0xFF) == '"')
			prev_dbl = &bitmap[i];
		i++;
	}
	config_quotes(bitmap, prev_dbl, prev_sng, i);
}

///potato
int join_var(unsigned short **bitmap, int i, char **var)
{
	int j;
	int flags;
	int lennew;
	int paracortes;
	int varsize;
	unsigned short *tempbitmap;

	paracortes = i;
	varsize = ft_strlen(*var);
	//esto supongo que no es necesario asi
	flags = 0;
	flags |= (*bitmap)[i] >> 8;
	if(!((*var) = getenv((*var))))
		(*var) = ft_strdup("");
	lennew = (((ft_wstrlen(*bitmap, 0)) - (varsize + 1)) + ft_strlen((*var)));
	if (!na_calloc(lennew + 1, sizeof(**bitmap), (void **)&tempbitmap))
			return -1;
	i = 0;
	while(i < paracortes)
	{
		tempbitmap[i] = (*bitmap)[i];
		i++;
	}
	paracortes += ft_strlen((*var));
	j = 0;
	while(i + j < paracortes)
	{
		tempbitmap[i + j] = (*var)[j];
		tempbitmap[i + j] |= flags << 8;
		j++;
	}
	paracortes = lennew;
	while(i + j < paracortes)
	{
		tempbitmap[i + j] = (*bitmap)[i + varsize + 1];
		i++;
	}
	//free
	free(*bitmap);
	(*bitmap) = tempbitmap;
	return(1);
}

int swap_var(unsigned short **bitmap, int i)
{
	unsigned short *tmp;
	char *var;
	int varlen;
	int j;

	tmp = ft_wstrdup((*bitmap) + i + 1, UNTIL_ANY_SPACE);
	varlen = ft_wstrlen(tmp, 0);
	var = malloc(varlen + 1);
	j = 0;
	while(j < varlen)
	{
		var[j] = (char)tmp[j];
		j++;
	}
	var[j] = 0;
	if(!join_var(bitmap, i, &var))
		return(-1);
	return(ft_strlen(var));
}

int substitute_var(unsigned short **bitmap)
{
	int i;

	i = 0;
	while ((*bitmap)[i])
	{
		if((char)(*bitmap)[i] == '$' && !((*bitmap)[i] & FLAG_SNGQUOT))
			i += swap_var(bitmap, i);
		i++;
	}
	return(ft_wstrlen((*bitmap), 0));
}
///potato

unsigned short	**get_args(const char *arg)
{
	size_t			len;
	unsigned short	*bitmap;
	char			*args;
	unsigned short	*tmp;
	unsigned short	**retreal;

	if (!arg)
		return (NULL);
	args = ft_strtrim(arg, " \f\n\r\t\v");
	if (!args)
		return (NULL);
	len = ft_strlen(args);
	if (len == 0 || !na_calloc(len + 1, sizeof(*bitmap), (void **)&bitmap))
		return (NULL);
	upcast_config(bitmap, args, 0, 0);
	free (args);
	tmp = ft_wstrdup(bitmap, UNTIL_END_OF_STRING);
	if (!tmp)
		return (NULL);
	free(bitmap);
	bitmap = tmp;

	///potato
	len = substitute_var(&bitmap);

ft_printf("\n\n");
	size_t i;
	i = 0;
	while (i < len)
	{
		ft_printf("%.2u binary is 0b%.8b char is: %c\n", i, bitmap[i] >> 8,
				  bitmap[i] & 0xFF);
		i++;
	}

	///potato

	retreal = ft_wstrsplit(bitmap);
	free (bitmap);
	return (retreal);
}
