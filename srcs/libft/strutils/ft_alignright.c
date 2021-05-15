#include "libft.h"

char	*align_right(char *field, const char *content)
{
	const char	*contstart;
	char		*fistart;
	size_t		size;

	size = ft_strlen(field);
	contstart = content;
	fistart = field;
	content += ft_strlen(content);
	if (content == contstart)
		return (fistart);
	field += size;
	while (size)
	{
		*field = *content;
		content--;
		field--;
		size--;
		if (field == fistart || content == contstart)
		{
			*field = *content;
			break ;
		}
	}
	return (fistart);
}
