#include <minishell0.h>
#include <wstrcmp.h>
#include <libft.h>
#include <get_redirs.h>

void	ft_dblptr_display(char **dblptr, void (*p)());
void	print_dblptr(const char *input);
void	display(void *str, int i);

/* void	display(void *str, int i) */
/* { */
/* 	char *arg; */

/* 	arg = downcast_wstr(str, 1); */
/* 	/\* ft_printf("%d, %s\n", i, str); *\/ */
/* 	ft_printf("%d, %s\n", i, arg); */
/* 	free (arg); */
/* } */

void	lstoflst_clear(t_dlist **list)
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

char	**downcast_dblwstr(t_dlist **args)
{
	t_dlist	*head;
	char	**ret;
	size_t	i;

	head = *args;
	if (!na_calloc(ft_lstsize((t_list *)head) + 1, sizeof(*ret),
			(void **)&ret))
		return (NULL);
	i = 0;
	while (head)
	{
		ret[i] = downcast_wstr(head->content, 1);
		head = head->next;
		i++;
	}
	ret[i] = NULL;
	ft_lstclear((t_list **)args, free, free);
	return (ret);
}

// while (g_term.simplecmds && g_term.simplecmds->content)
// {
// ft_lstdisplay(g_term.simplecmds->content, display);
// ft_lstclear((t_list **)&g_term.simplecmds->content, free, free);
/* if (!g_term.simplecmds->next) */
/* { */
/* 	ft_dlstrewind(&g_term.simplecmds); */
/* 	break ; */
/* } */
// g_term.simplecmds = g_term.simplecmds->next;
// }
/* printf("\nantepenul: %s\n", downcast_wstr(((t_list *)(g_term.simplecmds->content))->content, 1)); */
// ft_dlstrewind(&g_term.simplecmds);
// ft_lstclear((t_list **)&g_term.simplecmds, NULL, free);

t_simplcmd	*simple_ctor(t_dlist *head)
{
	t_simplcmd	*simple;

	if (!na_calloc(1, sizeof(*simple), (void **)&simple))
		return (NULL);
	simple->type = TYPE_END;
	simple->infd = STDIN_FILENO;
	simple->outfd = STDOUT_FILENO;
	if (get_redirs((t_list **)&head->content, &simple->infd, &simple->outfd))
	{
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

void	simple_dtor(t_simplcmd *simple)
{
	/* for (size_t i = 0; i < ft_dblptrlen((void **)simple->args); i++) */
	/* 	ft_printf("%d : %s\n", i, simple->args[i]); */
	if (!simple)
		return ;
	ft_dblptr_free((void **)simple->args);
	if (simple->infd > STDIN_FILENO)
		close(simple->infd);
	if (simple->outfd > STDOUT_FILENO)
		close(simple->outfd);
	free (simple);
}

int	error_syntax(char *token);

void	*comp_dtor(t_dlist **compcmd, t_dlist **simplecmds, bool isprintsynerr)
{
	t_dlist		*head;

	head = *compcmd;
	while (head && head->content)
	{
		simple_dtor(head->content);
		head = head->next;
	}
	if (simplecmds) {
		ft_printf("%p hello0\n", *simplecmds);
		while (simplecmds && (*simplecmds)->content)
		{
			ft_lstclear((t_list **)&(*simplecmds)->content, free, free);
			*simplecmds = (*simplecmds)->next;
		}
	}
	if (isprintsynerr)
	{
		ft_printf("%p hello1\n", *simplecmds);
		error_syntax("|");
	}
	return (NULL);
}

t_dlist	*build_cmd_table(t_dlist **simplecmds)
{
	t_dlist		*cmdtable;
	t_dlist		*head;
	t_simplcmd	*simplecmd;

	head = *simplecmds;
	cmdtable = NULL;
	while (head && head->content)
	{
		simplecmd = simple_ctor(head);
		if (!simplecmd || (!ft_dblptrlen((void **)simplecmd->args)
				&& simplecmd->type == TYPE_PIPE))
			return (comp_dtor(&cmdtable, simplecmds, simplecmd
					&& !ft_dblptrlen((void **)simplecmd->args)
					&& (simplecmd->type == TYPE_PIPE)));
		ft_dlstpush_back(&cmdtable, simplecmd);
		head = head->next;
	}
	lstoflst_clear((t_dlist **) simplecmds);
	if (((t_simplcmd *)ft_dlstlast(cmdtable)->content)->type == TYPE_PIPE)
	{
		error_syntax("|");
		return (NULL);
	}
	return (cmdtable);
}
