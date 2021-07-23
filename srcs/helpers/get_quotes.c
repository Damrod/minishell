#include <libft.h>
#include <minishell0.h>
#include <wstrcmp.h>

unsigned short	*get_token(unsigned short *bitmap)
{
	unsigned short	*token;
	size_t			j;
	size_t			len;

	len = 0;
	while (bitmap[len] && is_anytoken(bitmap[len]))
		len++;
	if (!na_calloc(len + 1, sizeof(*token), (void **)&token))
		return (NULL);
	j = 0;
	while (bitmap[j] && is_anytoken(bitmap[j]))
	{
		token[j] = bitmap[j];
		j++;
	}
	return (token);
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
