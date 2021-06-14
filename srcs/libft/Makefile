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
SRCS	= noassign/na_malloc.c memory/ft_bzero.c memory/ft_memcmp.c			   \
		  memory/ft_memset.c memory/ft_memcpy.c memory/ft_memchr.c			   \
		  memory/ft_memmove.c memory/ft_memccpy.c polyarray/ft_arrayshift.c	   \
		  polyarray/ft_arrkey.c polyarray/ft_array.c polyarray/ft_arrkey2.c	   \
		  polyarray/ft_alloc_matrix.c polyarray/ft_arrbyte.c				   \
		  btree/btree_apply_by_level.c btree/btree_search_item.c			   \
		  btree/btree_print.c btree/btree_level_count.c						   \
		  btree/btree_insert_data.c btree/btree_apply_suffix.c				   \
		  btree/btree_apply_prefix.c btree/btree_create_node.c				   \
		  btree/btree_apply_infix.c list/ft_list_sort.c list/ft_lstpop_back.c  \
		  list/ft_lstmerge.c list/ft_lstdisplay.c list/ft_lstclear.c		   \
		  list/ft_lstpop_front.c list/ft_lst_reverse.c list/ft_lstpush_front.c \
		  list/ft_lstsize.c list/ft_arrtolst.c list/ft_lstmap.c				   \
		  list/ft_lstadd_front.c list/ft_lstdelmany.c list/ft_lstlast.c		   \
		  list/ft_lstdup.c list/ft_lstpush_back.c list/ft_lsttoarr.c		   \
		  list/ft_lstadd_back.c list/na_lstnew.c list/ft_lstsplit.c			   \
		  list/ft_lstiter.c list/ft_lstcullpattern.c list/ft_lstdelone.c	   \
		  list/ft_lstsortedmerge.c list/ft_lstnew.c list/ft_lst_intcmp.c	   \
		  mytinygc/ft_advalloc.c mytinygc/ft_mperror.c mytinygc/ft_myalloc.c   \
		  ctype/ft_isalpha.c ctype/ft_isprint.c ctype/ft_toupper.c			   \
		  ctype/ft_isdigit.c ctype/ft_isascii.c ctype/ft_isalnum.c			   \
		  ctype/ft_isspace.c ctype/ft_tolower.c allocstr/ft_strtrim.c		   \
		  allocstr/ft_itoa.c allocstr/ft_calloc.c allocstr/ft_strjoin.c		   \
		  allocstr/ft_strjoin_ult.c allocstr/ft_split.c allocstr/ft_strdup.c   \
		  allocstr/ft_split_ultimate.c allocstr/ft_substr.c					   \
		  strutils/ft_reverse_string.c strutils/ft_wrtptr.c					   \
		  strutils/ft_alignright.c strutils/ft_findptrinarray.c				   \
		  strutils/ft_isspace_adv.c strutils/ft_strmapi.c					   \
		  strutils/get_next_line.c atoi/ft_atoi.c output/ft_putendl_fd.c	   \
		  output/ft_putchar_fd.c output/ft_putstr_fd.c output/ft_putnbr_fd.c   \
		   string/ft_strlcpy.c			   \
		  string/ft_strnstr.c string/ft_strchr.c string/ft_strlen.c			   \
		  string/ft_strlcat.c string/ft_strncmp.c string/ft_strrchr.c
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
INCS	= incs/libft.h mytinygc/advice.h list/ft_lstdelmany.h				   \
		  polyarray/ft_arrkey.h ft_printf/incs/ft_vprintf.h
SRC_T	= main.c
SRC_TB	= bonus_main.c
OBJ_T	= ${SRC_T:%.c=%.o}
OBJ_TB	= ${SRC_TB:%.c=%.o}
OBJS	= ${SRCS:%.c=%.o}
OBJS_B	= ${SRC_B:%.c=%.o}
OBJ_PFT	= ${SRC_PFT:%.c=%.o}
CFLAGS	= -Wall -Wextra -Werror -g
CC		= gcc
AR		= ar
ARFLAGS	= rc
INDEXER	= ranlib
RM		= rm -f
LDLIBS	= -lft
LDFLAGS	= -L
DCFLAGS = -shared
DEPS	= $(OBJS:%.o=%.d)

all : ${NAME}

%.o : %.c
	${CC} -c ${CFLAGS} -I incs -I ft_printf/incs $< -o $@ -MMD

-include $(DEPS)

${NAME} : ${OBJS} ${OBJ_PFT} ${INCS}
	${AR} ${ARFLAGS} $@ $^
	${INDEXER} ${NAME}

clean :
	${RM} ${OBJS} ${OBJS_B} ${OBJ_T} ${OBJ_TB} ${OBJ_PFT} ${DEPS}

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
