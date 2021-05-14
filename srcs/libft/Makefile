#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aollero- <aollero@gmail.com>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/29 18:09:31 by aollero-          #+#    #+#              #
#    Updated: 2020/10/13 14:29:30 by aollero-         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= libft.a
SRCS	= btree_apply_by_level.c btree_apply_infix.c btree_apply_prefix.c	   \
		  btree_apply_suffix.c btree_create_node.c btree_insert_data.c		   \
		  btree_level_count.c btree_search_item.c ft_advalloc.c ft_algebra.c   \
		  ft_array.c ft_arrbyte.c ft_arrkey2.c ft_arrkey.c ft_arrtolst.c	   \
		  ft_atoi.c ft_bzero.c ft_calloc.c ft_findptrinarray.c ft_isalnum.c	   \
		  ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c				   \
		  ft_isspace_adv.c ft_isspace.c ft_itoa.c ft_list_sort.c			   \
		  ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c					   \
		  ft_lstcullpattern.c ft_lstdelmany.c ft_lstdelone.c ft_lstdisplay.c   \
		  ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstmerge.c ft_lstnew.c	   \
		  ft_lstpop_back.c ft_lstpop_front.c ft_lstpush_back.c				   \
		  ft_lstpush_front.c ft_lst_reverse.c ft_lstsize.c					   \
		  ft_lstsortedmerge.c ft_lstsplit.c ft_lsttoarr.c ft_memccpy.c		   \
		  ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c		   \
		  ft_mperror.c ft_myalloc.c ft_putchar_fd.c ft_putendl_fd.c			   \
		  ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_split_ultimate.c		   \
		  ft_strchr.c ft_strdup.c ft_strjoin.c ft_strjoin_ult.c ft_strlcat.c   \
		  ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c	   \
		  ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c	   \
		  get_next_line.c misc.c mlx_protect.c na_lstnew.c na_malloc.c		   \
		  btree_print.c ft_reverse_string.c ft_alignright.c ft_lstdup.c		   \
		  ft_lst_intcmp.c ft_arrayshift.c
SRC_PFT	= ft_printf/srcs/ft_formattypes.c ft_printf/srcs/ft_float1.c		   \
		  ft_printf/srcs/ft_nitoa_helpers.c ft_printf/srcs/ft_gettype1.c	   \
		  ft_printf/srcs/ft_vprintf.c ft_printf/srcs/ft_gettype.c			   \
		  ft_printf/srcs/ft_pfmisc0.c ft_printf/srcs/ft_float0.c			   \
		  ft_printf/srcs/ft_outprintf.c ft_printf/srcs/ft_printf.c
INCSPFT	= ft_printf/incs/ft_float1.h ft_printf/incs/ft_gettype.h			   \
		  ft_printf/incs/ft_printf_private.h ft_printf/incs/ft_outprintf.h	   \
		  ft_printf/incs/ft_formattypes.h ft_printf/incs/ft_printf.h		   \
		  ft_printf/incs/ft_gettype1.h ft_printf/incs/ft_vprintf.h			   \
		  ft_printf/incs/ft_nitoa_helpers.h ft_printf/incs/ft_pfmisc0.h		   \
		  ft_printf/incs/ft_float0.h
TEST	= test
TEST_B	= test_bonus
INCS	= libft.h advice.h ft_lstdelmany.h ft_arrkey.h						   \
		  ft_printf/incs/ft_vprintf.h
SRC_T	= main.c
SRC_TB	= bonus_main.c
OBJ_T	= ${SRC_T:%.c=%.o}
OBJ_TB	= ${SRC_TB:%.c=%.o}
OBJS	= ${SRCS:%.c=%.o}
OBJS_B	= ${SRC_B:%.c=%.o}
OBJ_PFT	= ${SRC_PFT:%.c=%.o}
CFLAGS	= -Wall -Wextra -Werror
CC		= gcc
AR		= ar
ARFLAGS	= rc
INDEXER	= ranlib
RM		= rm -f
LDLIBS	= -lft
LDFLAGS	= -L
DCFLAGS = -shared

%.o : %.c
	${CC} -c ${CFLAGS} $< -o $@

${NAME} : ${OBJS} ${OBJ_PFT} ${INCS}
	${AR} ${ARFLAGS} $@ $^
	${INDEXER} ${NAME}

all : ${NAME}

clean :
	${RM} ${OBJS} ${OBJS_B} ${OBJ_T} ${OBJ_TB} ${OBJ_PFT}

fclean : clean
	${RM} ${NAME} ${TEST} ${TEST_B}

re : fclean all

bonus : ${NAME} ${OBJS_B}
	${AR} ${ARFLAGS}s $< ${filter-out $<,$^}

${TEST} : ${NAME} ${OBJ_T}
	${CC} ${CFLAGS} $^ -o $@ ${LDFLAGS}${<D} ${LDLIBS}

${TEST_B} : ${NAME} ${OBJ_TB} ${OBJS_B}
	make bonus
	${CC} ${CFLAGS} ${filter-out ${OBJS_B}, $^} -o $@ ${LDFLAGS}${<D} ${LDLIBS}

libft.so : ${OBJS}
	${CC} ${DCFLAGS} ${CFLAGS} -o libft.so $^

so :
	make libft.so

run :
	./run.sh --no-make --no-valgrind #--no-bonus

.PHONY: all bonus clean fclean re run so
