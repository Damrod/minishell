#include <minishell.h>

char	is_anytoken(unsigned short str)
{
	static unsigned short	prev = 0;

	if (prev == 0
		&& ((str == (FLAG_NOTSPCE | (unsigned short) '>'))
			|| (str == (FLAG_NOTSPCE | (unsigned short) '<'))
			|| (str == (FLAG_NOTSPCE | (unsigned short) '|'))))
		prev = (FLAG_NOTSPCE | str);
	if (prev != 0 && (prev == str))
		return (1);
	prev = 0;
	return (0);
}

unsigned short	cmp_space(const unsigned short str, char is_untilspace)
{
	if (is_untilspace == UNTIL_NON_QUOTED_SPACE)
		return (str && (str & 0xFF00));
	if (is_untilspace == UNTIL_ANY_SPACE)
		return (str && !ft_isspace(str & 0xFF));
	if (is_untilspace == UNTIL_ANY_ENDOFTOKEN)
		return (str && (str & 0xFF00) && !is_anytoken(str));
	return (str);
}

size_t	ft_wstrlen(const unsigned short *str, char is_untilspace)
{
	size_t			i;
	size_t			len;

	i = 0;
	len = 0;
	while (cmp_space(str[i], is_untilspace))
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

	len = ft_wstrlen(str, is_untilspace);
	if (!na_calloc(len + 1, sizeof(*result), (void **)&result))
		return (NULL);
	i = 0;
	len = 0;
	while (cmp_space(str[i], is_untilspace))
	{
		if (!(str[i] & FLAG_CIGNORE))
			result[len++] = str[i];
		i++;
	}
	return (result);
}

unsigned short	*upcast_str(const char *args)
{
	unsigned short	*ret;
	size_t			len;
	size_t			i;

	len = ft_strlen(args);
	if (!na_calloc(len + 1, sizeof(*ret), (void **)&ret))
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] |= args[i];
		i++;
	}
	return (ret);
}
