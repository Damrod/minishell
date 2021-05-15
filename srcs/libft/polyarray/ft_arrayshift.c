#include <libft.h>

void	*ft_arrayshift(void *currpos, t_array *arr, int tms)
{
	unsigned char	*lastchar;
	t_byte			*ret;
	int				i;

	if (tms >= 0)
	{
		i = ((t_byte *)currpos - (t_byte *)arr->cset) / arr->usz;
		ret = ((t_byte *)arr->cset + ((i + tms) * arr->usz)
				% (arr->setsz * arr->usz));
		return (ret);
	}
	lastchar = (t_byte *)arr->cset + (arr->setsz - 1) * arr->usz;
	i = (lastchar - (t_byte *)currpos) / arr->usz;
	return ((lastchar - ((i - tms) * arr->usz) % (arr->setsz * arr->usz)));
}
