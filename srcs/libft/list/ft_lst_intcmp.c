int	ft_lst_intcmp(void *data0, void *data1)
{
	int	*len0;
	int	*len1;

	len0 = data0;
	len1 = data1;
	return (*len0 - *len1);
}
