#include <minishell0.h>
#include <wstrcmp.h>

void	print_dblptr(const char *input)
{
	printf("%s\n", input);
}

int	get_pipes(void *src, void *key)
{
	unsigned short	*a;
	char			*b;

	a = src;
	b = key;
	return (ft_wstrncmp(a, b, CHECK_NOTQUOTE, 2));
}
