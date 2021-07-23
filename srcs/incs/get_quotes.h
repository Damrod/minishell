#ifndef GET_QUOTES_H
# define GET_QUOTES_H

# include <stdlib.h>

unsigned short	*get_token(unsigned short *bitmap);
char			isquote_not_nested_not_escaped(unsigned short c,
					char is_dblquotes);
void			config_quotes(unsigned short *map, unsigned short *prev_dbl,
					unsigned short *prev_sng, size_t sz);
ssize_t			toggle_inside_quote(ssize_t insideother, ssize_t *selfinside,
					unsigned short bitmap, char is_single);
void			upcast_config(unsigned short *bitmap, char *args,
					ssize_t inside_sng, ssize_t inside_dbl);

#endif
