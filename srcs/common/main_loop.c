#include <curses.h>
#include <term.h>
#include <libft.h>

/*  Emacs termcaps :  */
/* li#46co#83 */
/* cl              \E[H\E[J */
/* cd              \E[J */
/* bs               */
/* am               */
/* xn               */
/* cm              \E[%i%d;%dH */
/* nd              \E[C */
/* up              \E[A */
/* ce              \E[K */
/* ho              \E[H */
/* pt               */
/* al              \E[L */
/* dl              \E[M */
/* DL              \E[%dM */
/* AL              \E[%dL */
/* cs              \E[%i%d;%dr */
/* sf              ^J */
/* dc              \E[P */
/* DC              \E[%dP */
/* IC              \E[%d@ */
/* im              \E[4h */
/* ei              \E[4l */
/* mi               */
/* so              \E[7m */
/* se              \E[m */
/* us              \E[4m */
/* ue              \E[m */
/* md              \E[1m */
/* mr              \E[7m */
/* me              \E[m */
/* UP              \E[%dA */
/* DO              \E[%dB */
/* LE              \E[%dD */
/* RI              \E[%dC */
/* kl              \EOD */
/* kd              \EOB */
/* kr              \EOC */
/* ku              \EOA */
/* kN              \E[6~ */
/* kP              \E[5~ */
/* :@7             \E[4~ */
/* kh              \E[1~ */
/* mk              \E[8m */
/* cb              \E[1K */
/* op              \E[39;49m */
/* Co              #8 */
/* pa              #64 */
/* AB              \E[4%dm */
/* AF              \E[3%dm */
/* cr              ^M */
/* bl              ^G */
/* do              ^J */
/* le              ^H */
/* ta              ^I */
/* se              \E[27m */
/* ue              \E[24m */
/* kb              ^? */
/* kD              ^[[3~ */
/* sc              \E7 */
/* rc              \E8 */
/* r1				\Ec */

typedef struct s_termcaps {
	char	buf[1024];
	char *cl;  // clear screen
	char *cd;  // clear line
	bool bs;  // Obsolete flag: ASCII backspace may be used for left move
	bool am;  // output wraps to next line
	bool xn;  // cursor wraps in strange way
	char *cm;  // 
	char *nd;  // 
	char *up;  // 
	char *ce;  // 
	char *ho;  // 
	char *pt;  // 
	char *al;  // 
	char *dl;  // 
	char *DL;  // 
	char *AL;  // 
	char *cs;  // 
	char *sf;  // 
	char *dc;  // 
	char *DC;  // 
	char *IC;  // 
	char *im;  // 
	char *ei;  // 
	char *mi;  // 
	char *so;  // 
	char *se;  // 
	char *us;  // 
	char *ue;  // 
	char *md;  // 
	char *mr;  // 
	char *me;  // 
	char *UP;  // 
	char *DO;  // 
	char *LE;  // 
	char *RI;  // 
	char *kl;  // 
	char *kd;  // 
	char *kr;  // 
	char *ku;  // 
	char *kN;  // 
	char *kP;  // 
	char *kh;  // 
	char *mk;  // 
	char *cb;  // 
	char *op;  // 
	char *Co;  // 
	char *pa;  // 
	char *AB;  // 
	char *AF;  // 
	char *cr;  // 
	char *bl;  // 
	char *Do;  // 
	char *le;  // 
	char *ta;  // 
	char *kb;  // 
	char *kD;  // 
	char *sc;  // 
	char *rc;  // 
	char *r1;  // 
}	t_termcaps;

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

struct termios orig_termios;

void disableRawMode()
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode(char **argv)
{
	tcgetattr(STDIN_FILENO, &orig_termios);
	struct termios raw = orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void ft_dlstdisplay(void *src, int ordinal)
{
	char *str;

	str = src;
	ft_printf("%d - %s\n", ordinal, str);
}

void ft_puts(char *str)
{
	write(1, str, ft_strlen(str));
}

void	ft_lstdisplay(t_list *list, void (*disp)(void *, int));

int	main(int argc, char **argv)
{
	int nbr;
	t_termcaps caps;

	tgetent(caps.buf, getenv("TERM"));
	enableRawMode(argv);
	caps.kd = tgetstr("kd", NULL); // down
	caps.ku = tgetstr("ku", NULL); // up
	caps.kl = tgetstr("kl", NULL); // left
	caps.kr = tgetstr("kr", NULL); // right
	caps.cl = tgetstr("cl", NULL); // clear screen
	(void)nbr;
	(void) argc;
	(void) argv;
	write(1, caps.cl, ft_strlen(caps.cl));
	write(1, "\n", 1);
	ft_printf("\"%s\"\n\"%s\"\n"
			  "\"%s\"\n\"%s\"\n", caps.kl, caps.kr, caps.ku, caps.kd);
	/* tputs(tgoto(caps.up, 1, 1), ft_strlen(caps.up), ft_putchar); */
	/* fputs(caps.cls, stdout); */
	disableRawMode();
}
/* 	t_dlist *list = NULL; */
/* 	int i = 1; */
/* 	while (i < argc) */
/* 	{ */
/* 		ft_dlstpush_back(&list, argv[i]); */
/* 		i++; */
/* 	} */
/* 	ft_lstdisplay((t_list *)list, ft_dlstdisplay); */
/* 	ft_printf("%b\n", ft_dlstsize(list)); */
/* 	return (0); */
/* } */


/* int	main() */
/* { */
/* 	char *line; */

/* 	while(get_next_line_check_input(0, &line, "\n\0|\"\' ;", 7) > 0) */
/* 	{ */
/* 		printf("%s\n", line); */
/* 		free(line); */
/* 	} */
/* 	free(line); */
/* 	return (0); */
/* } */
