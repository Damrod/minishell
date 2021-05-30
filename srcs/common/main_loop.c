#include <curses.h>
#include <term.h>
#include <libft.h>

/* typedef struct s_termcaps { */
/* 	char	buf[1024]; */
/* 	char	*up; */
/* 	char	*down; */
/* 	char	*cls; */
/* }	t_termcaps; */

/* int	ft_putchar(int c) */
/* { */
/* 	return (write(1, &c, 1)); */
/* } */

/* struct termios orig_termios; */

/* void disableRawMode() */
/* { */
/* 	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); */
/* } */

/* void enableRawMode(char **argv) */
/* { */
/* 	tcgetattr(STDIN_FILENO, &orig_termios); */
/* 	struct termios raw = orig_termios; */
/* 	raw.c_lflag &= ~(ECHO | ICANON); */
/* 	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); */
/* 	printf("%s %d %s %s\n", __func__, __LINE__, __FILE__, argv[0]); */
/* } */

void ft_dlstdisplay(void *src, int ordinal)
{
	char *str;

	str = src;
	ft_printf("%d - %s\n", ordinal, str);
}

void	ft_lstdisplay(t_list *list, void (*disp)(void *, int));

int	main(int argc, char **argv)
{
	/* int nbr; */
	/* t_termcaps caps; */

	/* tgetent(caps.buf, getenv("TERM")); */
	/* enableRawMode(argv); */
	/* caps.down = tgetstr("kd", NULL); */
	/* caps.up = tgetstr("ku", NULL); */
	/* caps.cls = tgetstr("cl", NULL); */
	/* (void)nbr; */
	/* (void) argc; */
	/* (void) argv; */
	/* /\* write(1, caps.cls, ft_strlen(caps.cls)); *\/ */
	/* tputs(tgoto(caps.up, 1, 1), ft_strlen(caps.up), ft_putchar); */
	/* /\* fputs(caps.cls, stdout); *\/ */
	/* disableRawMode();
	 */
	t_dlist *list = NULL;
	int i = 1;
	while (i < argc)
	{
		ft_dlstpush_back(&list, argv[i]);
		i++;
	}
	ft_lstdisplay((t_list *)list, ft_dlstdisplay);
	ft_printf("%b\n", ft_dlstsize(list));
	return (0);
}
