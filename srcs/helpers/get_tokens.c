#include <libft.h>
#include <minishell0.h>
#include <wstrcmp.h>

char	is_redir(unsigned short *arg)
{
	if (ft_wstrncmp(arg, ">", CHECK_NOTQUOTE, 2) == 0
		|| ft_wstrncmp(arg, "<", CHECK_NOTQUOTE, 2) == 0
		|| ft_wstrncmp(arg, ">>", CHECK_NOTQUOTE, 3) == 0
		|| ft_wstrncmp(arg, "<<", CHECK_NOTQUOTE, 3) == 0)
		return (1);
	return (0);
}

char	is_pipe(unsigned short *arg)
{
	if (ft_wstrncmp(arg, "|", CHECK_NOTQUOTE, 2) == 0)
		return (1);
	return (0);
}

char	is_symbol(unsigned short *arg)
{
	return (is_pipe(arg) || is_redir(arg));
}

unsigned char	get_type(unsigned short *arg)
{
	unsigned char	type;

	if (ft_wstrncmp(arg, ">", CHECK_NOTQUOTE, 2) == 0)
		type = TYPE_OUT;
	else if (ft_wstrncmp(arg, ">>", CHECK_NOTQUOTE, 3) == 0)
		type = TYPE_APP;
	else if (ft_wstrncmp(arg, "<", CHECK_NOTQUOTE, 2) == 0)
		type = TYPE_IN;
	else if (ft_wstrncmp(arg, "<<", CHECK_NOTQUOTE, 3) == 0)
		type = TYPE_HEREDOC;
	else if (ft_wstrncmp(arg, "|", CHECK_NOTQUOTE, 2) == 0)
		type = TYPE_PIPE;
	else
		type = TYPE_END;
	return (type);
}
