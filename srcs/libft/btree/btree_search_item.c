#include <libft.h>

t_btree	*btree_search_item(t_btree *root, void *data_ref, int (*cmpf)
															(void *, void *))
{
	int	solution;

	if (!(root))
		return (NULL);
	solution = cmpf(root->item, data_ref);
	if (solution > 0)
		return (btree_search_item(root->left, data_ref, cmpf));
	else
	{
		if (solution == 0)
			return (root);
		else
			return (btree_search_item(root->right, data_ref, cmpf));
	}
}
