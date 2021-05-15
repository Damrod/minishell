#include "libft.h"

static void	btree_level_count2(t_btree *root, int i, int *result)
{
	if (!root)
	{
		i--;
		if (*result <= i)
			*result = i;
		return ;
	}
	btree_level_count2(root->right, i + 1, result);
	btree_level_count2(root->left, i + 1, result);
}

int	btree_level_count(t_btree *root)
{
	int	result;

	result = 0;
	btree_level_count2(root, 1, &result);
	return (result);
}
