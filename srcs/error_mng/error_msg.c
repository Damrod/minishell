#include <error_mng.h>

int	error_syntax(char *token, int *prunepattern)
{
	free(prunepattern);
	ft_dprintf(2, "%s: syntax error near unexpected token"
		" `%s'\n", EXENAME, token);
	return (1);
}

int	warning_shell(char *token, uint32_t line)
{
	ft_dprintf(1, "%s: warning: here-document at line %u delimited by "
		"end-of-file (wanted `%s')\n", EXENAME, line, token);
	return (1);
}

int	error_file(char *file, int *prunepattern)
{
	int		error;

	error = errno;
	free(prunepattern);
	ft_dprintf(2, "%s: %s: %s\n", EXENAME, file, strerror(error));
	free(file);
	return (1);
}

int	error_custom(void **freeme0, void **freeme1, void **freeme2, char *message)
{
	free_and_nullify(freeme0);
	free_and_nullify(freeme1);
	free_and_nullify(freeme2);
	ft_dprintf(2, "%s: %s\n", EXENAME, message);
	return (1);
}
