#include <executor.h>

static void	lstoflst_clear(t_dlist **list)
{
	t_dlist	*head;

	head = *list;
	while (head && head->content)
	{
		ft_lstclear((t_list **)&head->content, free, free);
		head = head->next;
	}
	ft_lstclear((t_list **)list, NULL, free);
}

static t_simplcmd	*simple_ctor(t_dlist *head, uint32_t *lineno)
{
	t_simplcmd	*simple;

	if (!na_calloc(1, sizeof(*simple), (void **)&simple))
		return (NULL);
	simple->type = TYPE_END;
	simple->infd = STDIN_FILENO;
	simple->outfd = STDOUT_FILENO;
	if (get_redirs((t_list **)&head->content, simple, lineno))
	{
		g_lastret = 1;
		ft_lstclear((t_list **)&head->content, free, free);
		free (simple);
		return (NULL);
	}
	if (!ft_wstrncmp((unsigned short *)ft_lstlast(head->content)->content,
			"|", CHECK_NOTQUOTE, 2))
	{
		simple->type = TYPE_PIPE;
		ft_lstdelone(ft_lstpop_back((t_list **)&head->content), free, free);
	}
	simple->args = downcast_dblwstr((t_dlist **)&head->content);
	ft_memset(simple->pipes, '\0', 2);
	return (simple);
}

static void	simple_dtor(t_simplcmd *simple)
{
	if (!simple)
		return ;
	ft_dblptr_free((void **)simple->args);
	if (simple->infd > STDIN_FILENO)
		close(simple->infd);
	if (simple->outfd > STDOUT_FILENO)
		close(simple->outfd);
	free (simple);
}

void	*comp_dtor(t_dlist **compcmd, t_dlist *simplecmds, bool isprintsynerr)
{
	t_dlist		*head;
	t_dlist		*tmp;

	if (!compcmd)
		return (NULL);
	head = *compcmd;
	while (head)
	{
		simple_dtor(head->content);
		tmp = head;
		head = head->next;
		free (tmp);
	}
	if (simplecmds)
		lstoflst_clear(&simplecmds);
	if (isprintsynerr)
		error_syntax("|");
	return (NULL);
}

t_dlist	*build_cmd_table(t_dlist **simplecmds, uint32_t *lineno)
{
	t_dlist		*cmdtable;
	t_dlist		*head;
	t_simplcmd	*simplecmd;

	head = *simplecmds;
	cmdtable = NULL;
	while (head && head->content)
	{
		simplecmd = simple_ctor(head, lineno);
		if (!simplecmd || (!ft_dblptrlen((void **)simplecmd->args)
				&& simplecmd->type == TYPE_PIPE))
			return (comp_dtor(&cmdtable, *simplecmds, simplecmd
					&& !ft_dblptrlen((void **)simplecmd->args)
					&& (simplecmd->type == TYPE_PIPE)));
		ft_dlstpush_back(&cmdtable, simplecmd);
		head = head->next;
	}
	lstoflst_clear((t_dlist **)simplecmds);
	if (((t_simplcmd *)ft_dlstlast(cmdtable)->content)->type == TYPE_PIPE)
		return (comp_dtor(&cmdtable, NULL, true));
	return (cmdtable);
}
