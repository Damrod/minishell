#include <libft.h>
#include <minishell0.h>
#include <stdbool.h>

char	*downcast_wstr(const unsigned short *str, char is_low)
{
	char	*result;
	size_t	i;

	if (!str)
		return (NULL);
	if (!na_calloc(sizeof(*result), ft_wstrlen(str, UNTIL_END_OF_STRING) + 1,
			(void **)&result))
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (is_low)
			result[i] = (char)str[i];
		else
			result[i] = (char)(str[i] >> 8);
		i++;
	}
	return (result);
}

static void	config_bitmasks(unsigned short *bitmask, unsigned short *bitmask2,
			char checkdepth)
{
	*bitmask2 = 0;
	*bitmask = 0;
	if (checkdepth == CHECK_ONLY_LOW)
	{
		*bitmask = 0xFF00U;
		*bitmask2 = 0;
	}
	if (checkdepth == CHECK_SNGQUOTE)
	{
		*bitmask = (FLAG_CIGNORE | FLAG_ESCAPED | FLAG_NOTSPCE | FLAG_DBLQUOT);
		*bitmask2 = FLAG_SNGQUOT;
	}
	if (checkdepth == CHECK_DBLQUOTE)
	{
		*bitmask = (FLAG_CIGNORE | FLAG_ESCAPED | FLAG_NOTSPCE | FLAG_SNGQUOT);
		*bitmask2 = FLAG_DBLQUOT;
	}
	if (checkdepth == CHECK_ANYQUOTE)
	{
		*bitmask2 = 0;
		*bitmask = 0;
	}
}

static char	cmp_chars(unsigned short a, unsigned short b, char checkdepth)
{
	unsigned short	bitmask;
	unsigned short	bitmask2;
	bool			aggregate;

	if (checkdepth == CHECK_ANYQUOTE || checkdepth == CHECK_NOTQUOTE)
	{
		aggregate = ((a & FLAG_DBLQUOT) | (a & FLAG_SNGQUOT));
		if (checkdepth == CHECK_NOTQUOTE)
			aggregate = !aggregate;
		aggregate &= ((a & 0xFF) == (b & 0xFF));
		return (aggregate);
	}
	config_bitmasks(&bitmask, &bitmask2, checkdepth);
	return ((a & ~bitmask) == (b | bitmask2));
}

int	ft_wstrncmp(unsigned short *s1, const char *str2, char checkdepth, size_t n)
{
	int					a;
	size_t				i;
	unsigned short		*s2;

	if (n == 0)
		return (0);
	s2 = upcast_str(str2);
	if (!s2)
		return (-0xFFFFF);
	i = 0;
	while (s1[i] && cmp_chars(s1[i], s2[i], checkdepth) && (i < n - 1))
		i++;
	a = (int)s1[i] - (int)s2[i];
	free (s2);
	return (a);
}
