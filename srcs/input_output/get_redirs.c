#include <libft.h>
#include <minishell0.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <error_mng.h>
#include <wstrcmp.h>
#include <get_tokens.h>
#include <heredoc.h>
#include <get_redirs.h>
#include <get_redirs2.h>
#include <stdint.h>

static int	get_redirs2(t_list **list, int *input, int *output, char **clpatt)
{
	bool			is_last;
	unsigned char	type;
	char			*file;

	is_last = 1;
	type = get_type((unsigned short *)(*list)->content);
	if ((*list)->next && (*list)->next->content)
		if (get_io_file(&file, (*list)->next->content, &is_last))
			return (1);
	if (type == TYPE_IN)
		if (to_input(input, file, is_last))
			return (1);
	if (type == TYPE_HEREDOC)
		if (to_heredoc(input, file, is_last))
			return (1);
	if (type == TYPE_APP)
		if (to_append(output, file, is_last))
			return (1);
	if (type == TYPE_OUT)
		if (to_output(output, file, is_last))
			return (1);
	free(file);
	*clpatt = ft_memset(*clpatt, 1, sizeof(**clpatt) * 2) + 2;
	*list = (*list)->next->next;
	return (0);
}

int	get_redirs(t_list **args, int *input, int *output)
{
	char	*clpatt;
	char	*clptt;
	t_list	*list;

	if (!na_calloc(ft_lstsize(*args) + 1, sizeof(*clptt), (void **)&clptt))
		return (1);
	clpatt = clptt;
	list = *args;
	while (list)
	{
		if (is_redir((unsigned short *)list->content))
		{
			if (get_redirs2(&list, input, output, &clpatt))
				return (free_and_nullify((void **)&clptt, NULL, NULL, 1));
		}
		else
		{
			clpatt++;
			list = list->next;
		}
	}
	ft_lstcullpat(args, clptt, free, free);
	free(clptt);
	if (!*args)
	{
		if (*input > STDIN_FILENO)
			close(*input);
		if (*output > STDOUT_FILENO)
			close(*output);
		return (1);
	}
	return (0);
}

/* int	get_redirs0(t_list **args, int *input, int *output) */
/* { */
/* 	return 1; */
/* } */
