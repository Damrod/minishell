#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <libft.h>

#define FLAG_ESCAPED (0b10000000 << 8)
#define FLAG_SNGQUOT (0b01000000 << 8)
#define FLAG_DBLQUOT (0b00100000 << 8)
#define FLAG_NOTSPCE (0b00010000 << 8)

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)					\
	(byte & 0x80 ? '1' : '0'),					\
		(byte & 0x40 ? '1' : '0'),				\
		(byte & 0x20 ? '1' : '0'),				\
		(byte & 0x10 ? '1' : '0'),				\
		(byte & 0x08 ? '1' : '0'),				\
		(byte & 0x04 ? '1' : '0'),				\
		(byte & 0x02 ? '1' : '0'),				\
		(byte & 0x01 ? '1' : '0')

char check_escaped(char c)
{
	static char escaped = 0;

	if (c == '\\' && !escaped)
		return (++escaped);
	escaped = 0;
	return (0);
}


char **get_args(const char *args)
{
	size_t len;
	unsigned short *bitmap;
	unsigned int i;
	unsigned int j;
	char insidedbl;
	char insidesng;

	bitmap = malloc(sizeof(*bitmap) * (ft_strlen(args) + 1));
	ft_memset(bitmap, '\0', ft_strlen(args) + 1);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (check_escaped(args[i]))
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
		i++;
	}
	i = 0;
	while (i < len)
	{
		ft_printf("%.2u binary is 0b%.8b char is: %c\n", i, bitmap[i] >> 8,
				  bitmap[i] & 0xFF);
		i++;
	}
	return NULL;
}

int main(int argc, char **argv)
{
	(void)argc;
	get_args(argv[1]);
	return (0);
}
