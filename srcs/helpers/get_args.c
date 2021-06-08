#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <libft.h>

#define FLAG_ESCAPED (0b10000000 << 8)
#define FLAG_SNGQUOT (0b01000000 << 8)
#define FLAG_DBLQUOT (0b00100000 << 8)
#define FLAG_NOTSPCE (0b00010000 << 8)
#define FLAG_CIGNORE (0b00001000 << 8)

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

size_t	ft_wstrlen(const unsigned short *str)
{
	size_t i;
	size_t len;

	i = 0;
	len = 0;
	while (str[i] & 0xFF00U)
	{
		if (!(str[i] & FLAG_CIGNORE))
			len++;
		i++;
	}
	return (len);
}

unsigned short	*ft_wstrdup(const unsigned short *str)
{
	unsigned short	*result;
	size_t			len;
	size_t			i;

	len = ft_wstrlen(str);
	if (!na_calloc(sizeof(*result), len + 1, (void **)&result))
		return (NULL);
	i = 0;
	len = 0;
	while (str[i] & 0xFF00U)
	{
		if (!(str[i] & FLAG_CIGNORE))
			result[len++] = str[i];
		i++;
	}
	return (result);
}

char *downcast_wstr(const unsigned short *str)
{
	char	*result;
	size_t	i;

	if (!na_calloc(sizeof(*result), ft_wstrlen(str) + 1, (void **)&result))
		return (NULL);
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	return (result);
}

#include <stdbool.h>

unsigned short *get_args(const char *args)
{
	size_t len;
	unsigned short *bitmap;
	unsigned int i;
	unsigned int j;
	char insidedbl;
	char insidesng;

	check_escaped('\0', 1);
	bitmap = malloc(sizeof(*bitmap) * (ft_strlen(args) + 1));
	ft_memset(bitmap, '\0', ft_strlen(args) + 1);
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
		if (((((bitmap[i] & 0xFF00) == (FLAG_DBLQUOT | FLAG_NOTSPCE))
			  || ((bitmap[i] & 0xFF00) == FLAG_NOTSPCE))
				&& ((bitmap[i] & 0xFF) == (short)'"'))
			|| ((((bitmap[i] & 0xFF00) == (FLAG_SNGQUOT | FLAG_NOTSPCE))
				 || ((bitmap[i] & 0xFF00) == FLAG_NOTSPCE))
				&& ((bitmap[i] & 0xFF) == (short)'\'')))
			bitmap[i] |= FLAG_CIGNORE;
		i++;
	}
	i = 0;
	while (i < len)
	{
		ft_printf("%.2u binary is 0b%.8b char is: %c\n", i, bitmap[i] >> 8,
				  bitmap[i] & 0xFF);
		i++;
	}
	check_escaped('\0', 1);
	return ft_wstrdup(bitmap);
}

int main(int argc, char **argv)
{
	unsigned short *str;
	char *normalstring;
	(void)argc;
	str = get_args(argv[1]);
	normalstring = downcast_wstr(str);
	ft_printf("---%s---\n", normalstring);
	free (str);
	free (normalstring);
	return (0);
}


// gcc -L. -lft get_args.c libft.a -I ../incs/ -I ../libft/incs/ -I ../libft/ft_printf/incs/
