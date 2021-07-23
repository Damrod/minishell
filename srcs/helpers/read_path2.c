#include <read_path.h>

char	*ft_cat_path(char *path, char *arg)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (!na_calloc((ft_strlen(path) + ft_strlen(arg) + 2),
			sizeof (char*), (void **)&ret))
		return (NULL);
	while (*path)
		ret[i++] = *path++;
	ret[i++] = '/';
	while (*arg)
		ret[i++] = *arg++;
	ret[i++] = 0;
	return (ret);
}

char	*ft_cat_rel_path(char *path, char *arg)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (!na_calloc((ft_strlen(path) + ft_strlen(arg)),
			sizeof(char*), (void **)&ret))
		return (NULL);
	while (*path)
		ret[i++] = *path++;
	arg += 1;
	while (*arg)
		ret[i++] = *arg++;
	ret[i++] = 0;
	return (ret);
}

void	ft_makerelat(char **args)
{
	char	*tmp;

	tmp = args[0];
	args[0] = ft_strjoin("./", args[0]);
	free(tmp);
}
