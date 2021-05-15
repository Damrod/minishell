#include <libft.h>

void	btree_apply_sufix(t_btree *root, void (*applyf)(void *))
{
	if (!root)
		return ;
	btree_apply_sufix(root->left, applyf);
	btree_apply_sufix(root->right, applyf);
	if (applyf)
		applyf(root->item);
}

void	btree_apply_cnt(t_btree *root, void (*applyc)(void *),
						void (*applyn)(void *))
{
	if (!root)
		return ;
	btree_apply_cnt(root->left, applyc, applyn);
	btree_apply_cnt(root->right, applyc, applyn);
	if (applyc)
		applyc(root->item);
	if (applyn)
		applyn(root);
}
