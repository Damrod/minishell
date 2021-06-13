#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <libft.h>
#include <readline/readline.h>
#include <readline/history.h>

#define FLAG_ESCAPED (0b01000000 << 8)
#define FLAG_SNGQUOT (0b00100000 << 8)
#define FLAG_DBLQUOT (0b00010000 << 8)
#define FLAG_NOTSPCE (0b00001000 << 8)
#define FLAG_CIGNORE (0b00000100 << 8)

# define NUL 0x00
# define SOH 0x01
# define STX 0x02
# define ETX 0x03
# define EOT 0x04
# define ENQ 0x05
# define ACK 0x06
# define BEL 0x07
# define BS 0x08
# define HT 0x09
# define LF 0x0A
# define VT 0x0B
# define FF 0x0C
# define CR 0x0D
# define SO 0x0E
# define SI 0x0F
# define DLE 0x10
# define DC1 0x11
# define DC2 0x12
# define DC3 0x13
# define DC4 0x14
# define NAK 0x15
# define SYN 0x16
# define ETB 0x17
# define CAN 0x18
# define EM 0x19
# define SUB 0x1A
# define FS 0x1C
# define GS 0x1D
# define RS 0x1E
# define US 0x1F
# define DEL 0x7F

size_t	ft_wstrlen(const unsigned short *str, char is_untilspace)
{
	size_t			i;
	size_t			len;
	unsigned short	bitmask;

	bitmask = 0xFFFFU;
	if (is_untilspace)
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

unsigned short	*ft_wstrdup(const unsigned short *str, char is_untilspace)
{
	unsigned short	*result;
	size_t			len;
	size_t			i;
	unsigned short	bitmask;

	len = ft_wstrlen(str, is_untilspace);
	if (!na_calloc(sizeof(*result), len + 1, (void **)&result))
		return (NULL);
	i = 0;
	len = 0;
	bitmask = 0xFFFFU;
	if (is_untilspace)
		bitmask = 0xFF00U;
	while (str[i] & bitmask)
	{
		if (!(str[i] & FLAG_CIGNORE))
			result[len++] = str[i];
		i++;
	}
	return (result);
}

char	*downcast_wstr(const unsigned short *str, char is_low)
{
	char	*result;
	size_t	i;

	if (!na_calloc(sizeof(*result), ft_wstrlen(str, 0) + 1, (void **)&result))
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (is_low)
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
			|| ((c & 0xFF00) == FLAG_NOTSPCE)) && ((c & 0xFF) == (short)cmp))
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
		newptr = ft_calloc(newsize, sizeof(char));
		if (newptr)
		{
			ft_memcpy(newptr, ptr, originalsize);
			free(ptr);
		}
		return (newptr);
	}
}

void	freedblptr(void **ptrs)
{
	void	**orig;

	orig = ptrs;
	while (*ptrs)
	{
		free (*ptrs);
		ptrs++;
	}
	free(orig);
	return ;
}

unsigned short	**ft_wstrsplit(unsigned short *bitmap)
{
	size_t			i;
	size_t			size;
	unsigned short	**ret;
	unsigned short	**tmp;

	ret = NULL;
	size = 1;
	i = 0;
	while (bitmap[i])
	{
		tmp = ft_realloc(ret, size * sizeof(*tmp), (size + 1) * sizeof(*tmp));
		if (!tmp)
		{
			freedblptr((void **)ret);
			return (NULL);
		}
		ret = tmp;
		ret[size - 1] = ft_wstrdup(&bitmap[i], 1);
		i += ft_wstrlen(ret[size - 1], 1);
		while (bitmap[i] && !(bitmap[i] & 0xFF00))
			i++;
		size++;
		ret[size - 1] = NULL;
	}
	return (ret);
}

void	config_quotes(unsigned short *map, unsigned short *prev_dbl,
			unsigned short *prev_sng, size_t sz)
{
	size_t	i;

	if (sz > 0 && (map[sz - 1] & 0xFF) != '"' && (map[sz - 1] & FLAG_DBLQUOT))
	{
		(*prev_dbl) |= FLAG_ESCAPED;
		i = 0;
		while (prev_dbl[i])
			prev_dbl[i++] &= ~FLAG_DBLQUOT;
	}
	if (sz > 0 && (map[sz - 1] & 0xFF) != '\'' && (map[sz - 1] & FLAG_SNGQUOT))
	{
		(*prev_sng) |= FLAG_ESCAPED;
		i = 0;
		while (prev_sng[i])
			prev_sng[i++] &= ~FLAG_SNGQUOT;
	}
	i = 0;
	while (map[i])
	{
		if (isquote_not_nested_not_escaped(map[i], 0)
			|| isquote_not_nested_not_escaped(map[i], 1))
			map[i] |= FLAG_CIGNORE;
		i++;
	}
}

ssize_t	toggle_inside_quote(ssize_t insideother, ssize_t *selfinside,
			unsigned short bitmap, char is_single)
{
	char	cmp;

	cmp = '"';
	if (is_single)
		cmp = '\'';
	if (!insideother && (bitmap & ~FLAG_NOTSPCE) == (short) cmp)
		*selfinside ^= 1;
	return (*selfinside);
}

void	upcast_config(unsigned short *bitmap, char *args, ssize_t inside_sng,
			ssize_t inside_dbl)
{
	ssize_t			i;
	unsigned short	*prev_dbl;
	unsigned short	*prev_sng;

	i = 0;
	while (args[i])
	{
		bitmap[i] |= args[i];
		if (!ft_isspace(bitmap[i] & 0xFF))
			bitmap[i] |= FLAG_NOTSPCE;
		if (!toggle_inside_quote(inside_sng, &inside_dbl, bitmap[i], 0))
			toggle_inside_quote(inside_dbl, &inside_sng, bitmap[i], 1);
		if (inside_dbl)
			bitmap[i] |= FLAG_DBLQUOT;
		if (inside_sng)
			bitmap[i] |= FLAG_SNGQUOT;
		if ((bitmap[i] & 0xFF) == '\'')
			prev_sng = &bitmap[i];
		if ((bitmap[i] & 0xFF) == '"')
			prev_dbl = &bitmap[i];
		i++;
	}
	config_quotes(bitmap, prev_dbl, prev_sng, i);
}

unsigned short	**get_args(const char *arg)
{
	size_t			len;
	unsigned short	*bitmap;
	char			*args;
	unsigned short	*tmp;
	unsigned short	**retreal;

	if (!arg)
		return (NULL);
	args = ft_strtrim(arg, " \f\n\r\t\v");
	if (!args)
		return (NULL);
	len = ft_strlen(args);
	if (len == 0 || !na_calloc(len + 1, sizeof(*bitmap), (void **)&bitmap))
		return (NULL);
	upcast_config(bitmap, args, 0, 0);
	free (args);
	tmp = ft_wstrdup(bitmap, 0);
	if (!tmp)
		return (NULL);
	free(bitmap);
	bitmap = tmp;
	retreal = ft_wstrsplit(bitmap);
	free (bitmap);
	return (retreal);
}

#include <signal.h>

typedef struct s_term {
	char	*inputstring;
}	t_term;

void specialfree(void **tofree)
{
	free(*tofree);
	*tofree = NULL;
}

t_term	g_term = {.inputstring = NULL };

void	handle_eot(int sig)
{
	(void) sig;
	specialfree((void**)&g_term.inputstring);
	ft_printf("\n");
	exit(0);
}

int main(int argc, char **argv)
{
	unsigned short **str;
	unsigned short **origstr;

	(void)argc;
	(void)argv;
	str = NULL;
	signal(SIGINT, handle_eot);
	signal(SIGQUIT, handle_eot);
	while (1)
	{
		g_term.inputstring = readline("marishell% ");
		if (g_term.inputstring && g_term.inputstring[0] == STX)
		{
			specialfree((void **)&g_term.inputstring);
			break ;
		}
		str = get_args(g_term.inputstring);
		specialfree((void **)&g_term.inputstring);
		if (!str)
			continue ;
		origstr = str;
		while (*str)
		{
			g_term.inputstring = downcast_wstr(*str, 1);
			ft_printf("---%s---\n", g_term.inputstring);
			free (*str);
			specialfree ((void **)&g_term.inputstring);
			str++;
		}
		free(origstr);
	}
	ft_printf("\n");
	return (0);
}


// gcc -L. -lft get_args.c libft.a -I ../incs/ -I ../libft/incs/ -I ../libft/ft_printf/incs/ -lreadline
// is this a bug ./a.out "\\\' \\\" " ?
// bug marishell% "h'" 'a VS "h" 'a
// bug "s'd'd" 'd
