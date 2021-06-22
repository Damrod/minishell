#include <libft.h>

static void	add_item(char **ret, const char *item, char is_deep, ssize_t *j)
{
	if (is_deep)
		ret[(*j)++] = ft_strdup(item);
	else
		ret[(*j)++] = (char *)item;
}

static ssize_t	copy_dblptr2(const char **data, char **ret, char is_deep,
			size_t len)
{
	size_t	j;

	j = 0;
	while (j < len)
	{
		if (is_deep)
			ret[j] = ft_strdup(data[j]);
		else
			ret[j] = (char *)data[j];
		if (!ret[j] && is_deep)
		{
			ft_dblptr_free((void **)ret);
			return (-1);
		}
		j++;
	}
	return (j);
}

char	**ft_dblptr_cpy(const char **data, const char *item, char is_deep)
{
	char		**ret;
	size_t		len;
	ssize_t		j;
	size_t		destsize;

	len = ft_dblptrlen((void **)data);
	destsize = len;
	if (item)
		destsize++;
	if (!na_calloc(destsize + 1, sizeof(*ret), (void **)&ret))
		return (NULL);
	j = 0;
	if (data)
		j = copy_dblptr2(data, ret, is_deep, len);
	if (j < 0)
		return (NULL);
	if (item)
		add_item(ret, item, is_deep, &j);
	ret[j] = NULL;
	return (ret);
}
