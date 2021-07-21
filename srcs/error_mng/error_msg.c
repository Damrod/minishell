#include <error_mng.h>

int	error_syntax(char *token)
{
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

int	error_cmd(char *builtin, char *arg, char *msg, int nbr)
{
	char	*int_msg;
	char	*optcolon;

	optcolon = ": ";
	if (!arg)
	{
		arg = "";
		optcolon = "";
	}
	int_msg = "";
	if (errno)
		int_msg = strerror(errno);
	if (msg)
		int_msg = msg;
	dprintf(2, "%s: %s: %s%s%s\n",
		EXENAME, builtin, arg, optcolon, int_msg);
	return (nbr);
}

int	error_file(char *file)
{
	int		error;

	error = errno;
	ft_dprintf(2, "%s: %s: %s\n", EXENAME, file, strerror(error));
	free(file);
	return (1);
}

int selfassignment(int *retnbr, int nbr, int retval)
{
	*retnbr = nbr;
	return (retval);
}

int	error_custom(void **freeme0, void **freeme1, void **freeme2, char *message)
{
	free_and_nullify(freeme0, freeme1, freeme2, 1);
	ft_dprintf(2, "%s: %s\n", EXENAME, message);
	return (1);
}
