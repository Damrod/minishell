#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <libft.h>

#define FLAG_ESCAPED (0b01000000 << 8)
#define FLAG_SNGQUOT (0b00100000 << 8)
#define FLAG_DBLQUOT (0b00010000 << 8)
#define FLAG_NOTSPCE (0b00001000 << 8)
#define FLAG_CIGNORE (0b00000100 << 8)

char	check_escaped(char c, char reset)
{
	static char	escaped = 0;

	if (reset)
		return (escaped = 0);
	if (c == '\\' && !escaped)
		return (++escaped);
	escaped = 0;
	return (0);
}

const unsigned short	*ft_wstrchr(unsigned short c,
									const unsigned short *delim)
{
	while (*delim & 0xFF00U)
	{
		if (*delim == c)
			break ;
		delim++;
	}
	if (*delim != c)
		return (NULL);
	return (delim);
}

size_t	ft_wstrlen(const unsigned short *str, char ignore)
{
	size_t i;
	size_t len;
	unsigned short	bitmask;

	bitmask = 0xFFFFU;
	if (ignore)
		bitmask = 0xFF00U;
	i = 0;
	len = 0;
	while (str[i] & bitmask)
	{
		if (!(str[i] & FLAG_CIGNORE))
			len++;
		i++;
	}
	return (len);
}

unsigned short	*ft_wstrdup(const unsigned short *str, char ignore)
{
	unsigned short	*result;
	size_t			len;
	size_t			i;
	unsigned short	bitmask;

	len = ft_wstrlen(str, ignore);
	if (!na_calloc(sizeof(*result), len + 1, (void **)&result))
		return (NULL);
	i = 0;
	len = 0;
	bitmask = 0xFFFFU;
	if (ignore)
		bitmask = 0xFF00U;
	while (str[i] & bitmask)
	{
		if (!(str[i] & FLAG_CIGNORE))
			result[len++] = str[i];
		i++;
	}
	return (result);
}

char *downcast_wstr(const unsigned short *str, char is_low)
{
	char	*result;
	size_t	i;

	if (!na_calloc(sizeof(*result), ft_wstrlen(str, 0) + 1, (void **)&result))
		return (NULL);
	i = 0;
	while (str[i])
	{
		if(is_low)
			result[i] = (char)str[i];
		else
			result[i] = (char)(str[i] >> 8);
		i++;
	}
	return (result);
}

char	isquote_not_nested_not_escaped(unsigned short c, char is_dblquotes)
{
	char			cmp;
	unsigned short	flag;

	cmp = '\'';
	flag = FLAG_SNGQUOT;
	if (is_dblquotes)
	{
		cmp = '"';
		flag = FLAG_DBLQUOT;
	}
	if ((((c & 0xFF00) == (FLAG_NOTSPCE | flag))
	  || ((c & 0xFF00) == FLAG_NOTSPCE))
	 && ((c & 0xFF) == (short)cmp))
		return (1);
	return (0);
}

void	*ft_realloc(void *ptr, size_t originalsize, size_t newsize)
{
	void	*newptr;

	if (newsize == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return (malloc(newsize));
	else if (newsize <= originalsize)
		return (ptr);
	else
	{
		newptr = malloc(newsize);
		if (newptr)
		{
			ft_memcpy(newptr, ptr, originalsize);
			free(ptr);
		}
		return (newptr);
	}
}

unsigned short *get_args(const char *arg)
{
	size_t len;
	unsigned short *bitmap;
	unsigned int i;
	unsigned int j;
	char insidedbl;
	char insidesng;
	char *args;
	unsigned short *tmp;

	args = ft_strtrim(arg, " \f\n\r\t\v");
	len = ft_strlen(args);
	check_escaped('\0', 1);
	if (len == 0)
		return (NULL);
	if (!na_calloc(len + 1, sizeof(*bitmap), (void **)&bitmap))
		return NULL;
	i = 0;
	j = 0;
	while (args[i])
	{
		if (check_escaped(args[i], 0))
		{
			bitmap[j] |= FLAG_ESCAPED;
			i++;
			bitmap[j] |= args[i];
			continue ;
		}
		bitmap[j] |= args[i];
		if (!ft_isspace(bitmap[j] & 0xFF))
			bitmap[j] |= FLAG_NOTSPCE;
		i++;
		j++;
	}
	free(args);
	len = j;
	i = 0;
	insidedbl = 0;
	insidesng = 0;
	while (i < len)
	{
		if (!insidesng && (bitmap[i] & ~FLAG_NOTSPCE) == (short)'"')
			insidedbl ^= 1;
		if (!insidedbl && (bitmap[i] & ~FLAG_NOTSPCE) == (short)'\'')
			insidesng ^= 1;
		if (insidedbl)
			bitmap[i] |= FLAG_DBLQUOT;
		if (insidesng)
			bitmap[i] |= FLAG_SNGQUOT;
		if (isquote_not_nested_not_escaped(bitmap[i], 0)
			|| isquote_not_nested_not_escaped(bitmap[i], 1))
			bitmap[i] |= FLAG_CIGNORE;
		i++;
	}
	tmp = ft_wstrdup(bitmap, 0);
	free(bitmap);
	bitmap = tmp;
	len = ft_wstrlen(bitmap, 0);
	i = 0;
	while (i < len)
	{
		ft_printf("%.2u binary is 0b%.8b char is: %c\n", i, bitmap[i] >> 8,
				  bitmap[i] & 0xFF);
		i++;
	}
	check_escaped('\0', 1);
	/* size_t originalsize = 2; */
	/* unsigned short **retreal; */
	/* if (!na_calloc(2, sizeof(*retreal), (void **)&retreal)) */
	/* 	return (NULL); */
	/* retreal[originalsize - 1] = ft_wstrdup(bitmap); */
	/* while(i < len) */
	/* { */
	/* 	if ((bitmap[i] & 0xFF00) != 0) */
	/* 	{ */
	/* 		ret */
	/* 	} */
	/* } */
	/* char * normalstring = downcast_wstr(bitmap, 0); */
	/* char **retreal = ft_split(normalstring, '0'); */
	unsigned short *ret = ft_wstrdup(bitmap, 1);
	free (bitmap);
	return (ret);
}

int main(int argc, char **argv)
{
	unsigned short *str;
	char *normalstring;
	(void)argc;
	str = get_args(argv[1]);
	normalstring = downcast_wstr(str, 1);
	ft_printf("---%s---\n", normalstring);
	free (str);
	free (normalstring);
	return (0);
}


// gcc -L. -lft get_args.c libft.a -I ../incs/ -I ../libft/incs/ -I ../libft/ft_printf/incs/
