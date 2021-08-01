#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

int	get_value(char queried, int base, int *retval)
{
	static const char	lookupl[37] = "0123456789abcdefghijklmnopqrstuvwxyz";
	static const char	lookupu[37] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int					i;

	i = 0;
	while ((int)i < base && lookupl[i])
	{
		if (queried == lookupl[i] || queried == lookupu[i])
		{
			if (retval)
				return (*retval = i);
			return (i);
		}
		i++;
	}
	if (retval)
		*retval = -1;
	return (-1);
}

static int is_multiplication_overflow(long int a, long int b)
{
	long int	result;

	if (a == 0 || b == 0)
		return 0;
	result = a * b;
	if (a == result / b)
		return 0;
	else
		return 1;
}


static long int	loop_strtol(int sign, char **endptr, int base)
{
	long int	oldresul;
	long int	resul;
	int			retval;

	resul = 0;
	while (get_value(**endptr, base, &retval) >= 0)
	{
		oldresul = resul;
		resul = base * resul + retval;
		(*endptr)++;
		if (resul < 0 || is_multiplication_overflow(oldresul, base))
		{
			if (!(resul == LONG_MIN
				  && get_value(**endptr, base, NULL) < 0) || sign > 0)
				errno = ERANGE;
			while (get_value(**endptr, base, NULL) >= 0)
				(*endptr)++;
			if (sign < 0)
				return (LONG_MIN);
			return (LONG_MAX);
		}
	}
	while (get_value(**endptr, base, NULL) >= 0)
		(*endptr)++;
	return (sign * resul);
}

static void	config_strtol(int *sign, char ***endptr, int *base)
{
	(*sign) = 1;
	while (***endptr == '\t' || ***endptr == '\n' || ***endptr == '\v'
		   || ***endptr == '\f' || ***endptr == '\r' || ***endptr == ' ')
		(**endptr)++;
	if (***endptr == '-')
	{
		(*sign) = -1;
		(**endptr)++;
	}
	else if (***endptr == '+')
		(**endptr)++;
	if (*base == 0)
	{
		if (***endptr == '0')
		{
			*base = 8;
			if ((**endptr)[1] == 'x' || (**endptr)[1] == 'X')
				*base = 16;
		}
		else
			*base = 10;
	}
}

long int	ft_strtol(const char *nptr, char **endptr, int base)
{
	int			sign;

	if (!endptr)
		endptr = (char **)&nptr;
	*endptr = (char *)nptr;
	if (base != 0 && (base < 2 || base > 36))
	{
		errno = EINVAL;
		return (0);
	}
	config_strtol(&sign, &endptr, &base);
	if (base == 16)
		if (**endptr == '0' && ((*endptr)[1] == 'x' || (*endptr)[1] == 'X'))
			(*endptr) += 2;
	return (loop_strtol(sign, endptr, base));
}



/* long int	ft_strtol(const char *nptr, char **endptr, int base) */
/* { */
/* 	int			sign; */
/* 	long int	resul; */
/* 	long int	oldresul; */
/* 	int			retval; */

/* 	if (!endptr) */
/* 		endptr = (char **)&nptr; */
/* 	*endptr = (char *)nptr; */
/* 	if (base != 0 && (base < 2 || base > 36)) */
/* 	{ */
/* 		errno = EINVAL; */
/* 		return (0); */
/* 	} */
/* 	sign = 1; */
/* 	while (**endptr == '\t' || **endptr == '\n' || **endptr == '\v' */
/* 		   || **endptr == '\f' || **endptr == '\r' || **endptr == ' ') */
/* 		(*endptr)++; */
/* 	if (**endptr == '-') */
/* 	{ */
/* 		sign = -1; */
/* 		(*endptr)++; */
/* 	} */
/* 	else if (**endptr == '+') */
/* 		(*endptr)++; */
/* 	if (base == 0) */
/* 	{ */
/* 		if (**endptr == '0') */
/* 		{ */
/* 			base = 8; */
/* 			if ((*endptr)[1] == 'x' || (*endptr)[1] == 'X') */
/* 				base = 16; */
/* 		} */
/* 		else */
/* 			base = 10; */
/* 	} */
/* 	if (base == 16) */
/* 		if (**endptr == '0' && ((*endptr)[1] == 'x' || (*endptr)[1] == 'X')) */
/* 			(*endptr) += 2; */
/* 	resul = 0; */
/* 	while (get_value(**endptr, base, &retval) >= 0) */
/* 	{ */
/* 		oldresul = resul; */
/* 		resul = base * resul + retval; */
/* 		(*endptr)++; */
/* 		if (resul < 0 || is_multiplication_overflow(oldresul, base)) */
/* 		{ */
/* 			if (!(resul == LONG_MIN */
/* 				  && get_value(**endptr, base, NULL) < 0) || sign > 0) */
/* 				errno = ERANGE; */
/* 			if (sign > 0) */
/* 				resul = LONG_MAX; */
/* 			else */
/* 				resul = LONG_MIN; */
/* 			break ; */
/* 		} */
/* 	} */
/* 	while (get_value(**endptr, base, &retval) >= 0) */
/* 		(*endptr)++; */
/* 	return (sign * resul); */
/* } */

void teststrtol(char *query, int base)
{
	char *location; //= &a;
	long int result;
	char	buffermy[92];
	char	buffertheir[92];

	printf("Testing %s\n", query);
	result = ft_strtol(query, &location, base);
	sprintf(buffermy,
			"%li, errno %d, location char %s\n", result, errno, location);
	errno = EXIT_SUCCESS;
	result = strtol(query, &location, base);
	sprintf(buffertheir, "%li, errno %d, location char %s\n", result, errno, location);
	errno = EXIT_SUCCESS;
	if (strcmp(buffermy, buffertheir))
	{
		dprintf(STDERR_FILENO, "%s", buffermy);
		dprintf(STDERR_FILENO, "%s", buffertheir);
	}
	else
		printf("Success!\n");
	printf("=====================================\n");
}

int main(int argc, char **argv)
{
	/* char a = 'M'; */
	if (argc < 2)
		return 1;
	teststrtol("-92233720368547758191212215a", atoi(argv[1]));
	teststrtol("-9223372036854775818a", atoi(argv[1]));
	teststrtol("-9223372036854775817a", atoi(argv[1]));
	teststrtol("-9223372036854775816a", atoi(argv[1]));
	teststrtol("-9223372036854775815a", atoi(argv[1]));
	teststrtol("-9223372036854775814a", atoi(argv[1]));
	teststrtol("-9223372036854775813a", atoi(argv[1]));
	teststrtol("-9223372036854775812a", atoi(argv[1]));
	teststrtol("-9223372036854775811a", atoi(argv[1]));
	teststrtol("-9223372036854775810a", atoi(argv[1]));
	teststrtol("-9223372036854775809a", atoi(argv[1]));
	teststrtol("-9223372036854775808a", atoi(argv[1]));
	teststrtol("-9223372036854775807a", atoi(argv[1]));
	teststrtol("-9223372036854775806a", atoi(argv[1]));
	teststrtol("-9223372036854775805a", atoi(argv[1]));
	teststrtol("-9223372036854775804a", atoi(argv[1]));
	teststrtol("-9223372036854775803a", atoi(argv[1]));
	teststrtol("-9223372036854775802a", atoi(argv[1]));
	teststrtol("-9223372036854775801a", atoi(argv[1]));
	teststrtol("-92233720368547758081m", atoi(argv[1]));
	teststrtol("-9223372036854775808m1215362m", atoi(argv[1]));
	teststrtol("0a", atoi(argv[1]));
	teststrtol("9223372036854775796a", atoi(argv[1]));
	teststrtol("9223372036854775797a", atoi(argv[1]));
	teststrtol("9223372036854775798a", atoi(argv[1]));
	teststrtol("9223372036854775799a", atoi(argv[1]));
	teststrtol("9223372036854775800a", atoi(argv[1]));
	teststrtol("9223372036854775801a", atoi(argv[1]));
	teststrtol("9223372036854775802a", atoi(argv[1]));
	teststrtol("9223372036854775803a", atoi(argv[1]));
	teststrtol("9223372036854775804a", atoi(argv[1]));
	teststrtol("9223372036854775805a", atoi(argv[1]));
	teststrtol("9223372036854775806a", atoi(argv[1]));
	teststrtol("9223372036854775807a", atoi(argv[1]));
	teststrtol("9223372036854775808a", atoi(argv[1]));
	teststrtol("9223372036854775809a", atoi(argv[1]));
	teststrtol("9223372036854775810a", atoi(argv[1]));
	teststrtol("9223372036854775811a", atoi(argv[1]));
	teststrtol("9223372036854775812a", atoi(argv[1]));
	teststrtol("9223372036854775813a", atoi(argv[1]));
	teststrtol("9223372036854775814a", atoi(argv[1]));
	teststrtol("9223372036854775815a", atoi(argv[1]));
	teststrtol("9223372036854775816a", atoi(argv[1]));
	teststrtol("9223372036854775817a", atoi(argv[1]));
	teststrtol("9223372036854775818a", atoi(argv[1]));

	teststrtol("92233720368547758071m", atoi(argv[1]));
	teststrtol(argv[2], atoi(argv[1]));
	return 0;
}

/* alvaro@r10d10:~/.../aollero-/philo(master)$ valgrind ./a.out 023452345 0==28262== Memcheck, a memory error detector */
/* 	==28262== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al. */
/* 	==28262== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info */
/* 	==28262== Command: ./a.out 023452345 0 */
/* ==28262==  */
/* 23452345, errno 0, location char  */
/* 5133541, errno 0, location char  */
/* ==28262==  */
/* ==28262== HEAP SUMMARY: */
/* ==28262==     in use at exit: 0 bytes in 0 blocks */
/* ==28262==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated */
/* ==28262==  */
/* ==28262== All heap blocks were freed -- no leaks are possible */
/* ==28262==  */
/* ==28262== For lists of detected and suppressed errors, rerun with: -s */
/* ==28262== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0) */
