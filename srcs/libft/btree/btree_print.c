#include <libft.h>
#include "btree_print.h"

static t_popts	fright(t_popts opts, int left, int width)
{
	opts.is_left = 0;
	opts.offset += left + width;
	opts.depth += 1;
	return (opts);
}

static t_popts	fleft(t_popts opts)
{
	opts.depth += 1;
	opts.is_left = 1;
	return (opts);
}

static int	pprint(t_popts opts, char s[20][255])
{
	unsigned int	i;

	if (opts.depth && opts.is_left)
	{
		i = 0;
		while (i < opts.width + opts.right)
			s[2 * opts.depth - 1][opts.offset + opts.left + opts.width
				/ 2 + i++] = '-';
		s[2 * opts.depth - 1][opts.offset + opts.left + opts.width / 2] = '^';
		s[2 * opts.depth - 1][opts.offset + opts.left + opts.width
			+ opts.right + opts.width / 2] = '<';
	}
	else if (opts.depth && !opts.is_left)
	{
		i = 0;
		while (i < opts.left + opts.width)
			s[2 * opts.depth - 1][opts.offset - opts.width / 2 + i++] = '-';
		s[2 * opts.depth - 1][opts.offset + opts.left + opts.width / 2] = '&';
		s[2 * opts.depth - 1][opts.offset - opts.width / 2 - 1] = '>';
	}
	return (opts.left + opts.width + opts.right);
}

static int	_print_t(t_btree *tree, t_popts opts, char s[20][255])
{
	char			b[20];
	unsigned int	i;

	opts.width = 7;
	if (opts.type)
		opts.width = 5;
	if (!tree)
		return (0);
	if (opts.type)
		ft_sprintf(b, "(%03d)", *(int *)tree->item);
	else
		ft_sprintf(b, "(%.*s)", (int)ft_strlen((char *)tree->item),
			(char *)tree->item);
	opts.left = _print_t(tree->left, fleft(opts), s);
	opts.right = _print_t(tree->right, fright(opts, opts.left, opts.width), s);
	i = 0;
	while (i < opts.width)
	{
		s[2 * opts.depth][opts.offset + opts.left + i] = b[i];
		i++;
	}
	return (pprint(opts, s));
}

void	btree_print(t_btree *tree, int type)
{
	t_popts			opts;
	char			str[20][255];
	unsigned int	i;

	opts.depth = 0;
	opts.is_left = 0;
	opts.offset = 0;
	opts.type = type;
	i = 0;
	while (i < 20)
		ft_sprintf(str[i++], "%80s", " ");
	_print_t(tree, opts, str);
	i = 0;
	while (i < 20)
		ft_printf("%s\n", str[i++]);
}
