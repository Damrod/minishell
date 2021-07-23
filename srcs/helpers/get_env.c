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

char	*ft_getenv(const char *name)
{
	size_t	i;

	i = 0;
	while (g_term.environ[i])
	{
		if (ft_getvalue(name, g_term.environ[i]) == 0)
			return (ft_strchr(g_term.environ[i], '=') + 1);
		i++;
	}
	return (NULL);
}
