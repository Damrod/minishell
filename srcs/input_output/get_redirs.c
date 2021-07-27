#include <get_redirs.h>

static int	get_redirs2(t_list **list, t_simplcmd *simple, char **clpatt,
			uint32_t *lineno)
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
		if (to_input(&simple->infd, file, is_last))
			return (1);
	if (type == TYPE_HEREDOC)
		if (to_heredoc(&simple->infd, file, is_last, lineno))
			return (1);
	if (type == TYPE_APP)
		if (to_append(&simple->outfd, file, is_last))
			return (1);
	if (type == TYPE_OUT)
		if (to_output(&simple->outfd, file, is_last))
			return (1);
	free(file);
	*clpatt = ft_memset(*clpatt, 1, sizeof(**clpatt) * 2) + 2;
	*list = (*list)->next->next;
	return (0);
}

static int	get_redirs3(t_list **args, char *clptt, t_simplcmd *simple)
{
	ft_lstcullpat(args, clptt, free, free);
	free(clptt);
	if (!*args)
	{
		if (simple->infd > STDIN_FILENO)
			if (close(simple->infd))
				return (error_file(NULL));
		if (simple->outfd > STDOUT_FILENO)
			if (close(simple->outfd))
				return (error_file(NULL));
		return (1);
	}
	return (0);
}

int	get_redirs(t_list **args, t_simplcmd *simple, uint32_t *lineno)
{
	char	*clpatt;
	char	*clptt;
	t_list	*list;

	if (!na_calloc(ft_lstsize(*args) + 1, sizeof(*clptt), (void **)&clptt))
		return (g_lastret = 1);
	clpatt = clptt;
	list = *args;
	while (list)
	{
		if (is_redir((unsigned short *)list->content))
		{
			if (get_redirs2(&list, simple, &clpatt, lineno))
				return (g_lastret = free_and_nullify((void **)&clptt, NULL,
						NULL, 1));
		}
		else
		{
			clpatt++;
			list = list->next;
		}
	}
	return (g_lastret = get_redirs3(args, clptt, simple));
}
