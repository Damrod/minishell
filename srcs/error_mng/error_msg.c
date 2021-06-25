#include <libft.h>
#include <minishell0.h>

int error_syntax(char *token, int *prunepattern, t_list **args)
{
	free(prunepattern);
	ft_lstclear(args, free, free);
	ft_dprintf(2, "%s: syntax error near unexpected token"
			   " `%s'\n", EXENAME, token);
	return (1);
}

int warning_shell(char *token, uint32_t line)
{
	ft_dprintf(1, "%s: warning: here-document at line %u delimited by "
			   "end-of-file (wanted `%s')\n", EXENAME, line, token);
	return (1);
}

int error_file(char *file, int *prunepattern, t_list **args)
{
	int		error;

	error = errno;
	free(prunepattern);
	ft_lstclear(args, free, free);
	ft_dprintf(2, "%s: %s: %s\n", EXENAME, file, strerror(error));
	free(file);
	return (1);
}
