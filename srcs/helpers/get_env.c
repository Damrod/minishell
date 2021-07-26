#include "env.h"

static int	ft_getvalue(const char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;

	if (!ft_strchr(s2, '='))
		return (-1);
	len1 = ft_strlen(s1);
	len2 = ft_strchr(s2, '=') - s2;
	if (len1 < len2)
		len1 = len2;
	return (ft_strncmp(s1, s2, len1));
}

char	*ft_getenv(const char *name, char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_getvalue(name, env[i]) == 0)
			return (ft_strchr(env[i], '=') + 1);
		i++;
	}
	return (NULL);
}
