#include <libft.h>

void	btree_apply_infix(t_btree *root, void (*applyf)(void *))
{
	if (!root)
		return ;
	btree_apply_infix(root->left, applyf);
	if (applyf)
		applyf(root->item);
	btree_apply_infix(root->right, applyf);
}
