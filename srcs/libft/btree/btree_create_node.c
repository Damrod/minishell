#include <libft.h>

t_btree	*btree_create_node(void *item)
{
	t_btree	*btree;

	btree = malloc(sizeof(*btree));
	if (!btree)
		return (NULL);
	btree->left = NULL;
	btree->right = NULL;
	btree->item = item;
	return (btree);
}
