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

static int	get_redirs2(t_list **list, int *input, int *output, int **clpattern)
{
	bool			is_last;
	unsigned char	type;
	char			*file;

	(void) clpattern;
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
	/* ft_memset(*clpattern, '1', sizeof(int) * 2); */
	/* (**clpattern) = 1; */
	/* (*clpattern)++; */
	/* (**clpattern) = 1; */
	/* (*clpattern)++; */
	/* *clpattern += 2; */
	if (*list && (*list)->next)
		*list = (*list)->next->next;
	return (0);
}

int	get_redirs(t_list **args, int *input, int *output)
{
	int				**clpatt;
	int				*clpattern;
	t_list			*list;

	clpattern = ft_calloc(ft_lstsize(*args), sizeof(*clpattern));
	clpatt = &clpattern;
	list = *args;
	while (list)
	{
		if (is_redir((unsigned short *)list->content))
		{
			if (get_redirs2(&list, input, output, clpatt))
			{
				free(clpattern);
				return (1);
			}
		}
		else
		{
			clpatt++;
			list = list->next;
		}
	}
	ft_lstcullpat(args, clpattern, free, free);
	free(clpattern);
	return (0);
}
