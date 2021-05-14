#include "libft.h"

static void	applylevel(t_btree *curr, int level, int data[2], void (*applyf)
			(void *, int, int))
{
	if (!curr)
		return ;
	if (level == 1)
	{
		if (data[0])
		{
			applyf(curr->item, data[1], *data);
			data[0] = 0;
		}
		else
			applyf(curr->item, data[1], *data);
	}
	else
	{
		applylevel(curr->left, level - 1, data, applyf);
		applylevel(curr->right, level - 1, data, applyf);
	}
}

/*
** data[0] = is_first
** data[1] = current level
*/

void	btree_apply_by_level(t_btree *root, void (*applyf)(void *, int, int))
{
	int	height;
	int	i;
	int	data[2];

	height = btree_level_count(root);
	i = 1;
	while (i < height + 1)
	{
		data[0] = 1;
		data[1] = i - 1;
		applylevel(root, i, data, applyf);
		i++;
	}
}
