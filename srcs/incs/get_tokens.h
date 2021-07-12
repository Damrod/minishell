#ifndef GET_TOKENS_H
# define GET_TOKENS_H

char			is_redir(unsigned short *arg);
char			is_pipe(unsigned short *arg);
char			is_symbol(unsigned short *arg);
unsigned char	get_type(unsigned short *arg);

#endif
