# Define the function that will generate each rule
define generateRules
$(1)/%.o: %.c
	@echo Building $$@
	$(HIDE)$(CC) -c $(CFLAGS) $(INCLUDES) -o $$@ $$< -MMD $(LDLIBS)
endef

# Define the function that will generate each build directory
define generateDirs
$(1):
	@echo Creating dir $$@
	$(HIDE)$(MKDIR) $$@ $(ERRIGNORE)
endef

# $(CURDIR) is a GNU make variable containing the path to the current working
# directory
PROJDIR := $(CURDIR)
SOURCEDIR := $(PROJDIR)/srcs
BUILDDIR := $(PROJDIR)/bld
NAME = minishell
# source directories with $(SOURCEDIR) as root
LIBFTD = libft/noassign libft/memory libft/polyarray libft/btree			   \
	   libft/list libft/mytinygc libft/ctype libft/allocstr libft/strutils	   \
	   libft/atoi libft/output libft/ft_printf libft/ft_printf/srcs			   \
	   libft/string libft/list/dllist libft/dblptr
DIRS = common helpers error_mng input_output executor
DIRS += $(LIBFTD)
LIBFTDSRC = $(foreach dir, $(LIBFTD), $(addprefix $(SOURCEDIR)/, $(dir)))
LIBFTSRC = $(foreach dir,$(LIBFTDSRC),$(wildcard $(dir)/*.c))
LIBFTO := $(subst $(SOURCEDIR),$(BUILDDIR),$(LIBFTSRC:%.c=%.o))
SOURCEDIRS = $(foreach dir, $(DIRS), $(addprefix $(SOURCEDIR)/, $(dir)))
TARGETDIRS = $(foreach dir, $(DIRS), $(addprefix $(BUILDDIR)/, $(dir)))
SOURCES = $(SOURCEDIR)/executor/make_cmd_table.c							   \
		  $(SOURCEDIR)/executor/executor.c									   \
		  $(SOURCEDIR)/executor/executor2.c									   \
		  $(SOURCEDIR)/error_mng/error_msg.c								   \
		  $(SOURCEDIR)/error_mng/exit_handlers.c							   \
		  $(SOURCEDIR)/helpers/get_vars.c $(SOURCEDIR)/common/main.c		   \
		  $(SOURCEDIR)/helpers/get_tokens.c $(SOURCEDIR)/helpers/env.c		   \
		  $(SOURCEDIR)/helpers/pwd.c $(SOURCEDIR)/helpers/misc.c			   \
		  $(SOURCEDIR)/helpers/cd.c $(SOURCEDIR)/helpers/wstrcmp.c			   \
		  $(SOURCEDIR)/helpers/get_args.c $(SOURCEDIR)/helpers/ft_wstr2.c	   \
		  $(SOURCEDIR)/helpers/read_path.c									   \
		  $(SOURCEDIR)/helpers/get_quotes.c $(SOURCEDIR)/helpers/echo.c		   \
		  $(SOURCEDIR)/input_output/heredoc.c								   \
		  $(SOURCEDIR)/input_output/get_redirs2.c							   \
		  $(SOURCEDIR)/input_output/get_redirs.c							   \
		  $(SOURCEDIR)/helpers/exit.c										   \
		  $(SOURCEDIR)/helpers/export.c										   \
		  $(SOURCEDIR)/helpers/get_env.c									   \
		  $(SOURCEDIR)/helpers/read_path2.c									   \
		  $(SOURCEDIR)/helpers/unset.c
OBJS := $(subst $(SOURCEDIR),$(BUILDDIR),$(SOURCES:%.c=%.o))
DEPS = $(OBJS:%.o=%.d)
INCLUDES += -I $(SOURCEDIR)/incs -I $(SOURCEDIR)/libft/incs					   \
			-I $(SOURCEDIR)/libft/ft_printf/incs
VPATH = $(SOURCEDIRS)
CC = clang
CFLAGS = -Wall -Wextra -Werror -g # -fsanitize=address
LDLIBS_LINK = -lreadline -lft

RM = rm -rf
MKDIR = mkdir -p
VERBOSE = TRUE
ERRIGNORE = 2>/dev/null
# Hide or not the calls depending of VERBOSE
ifeq ($(VERBOSE),TRUE)
	HIDE =
else
	HIDE = @
endif

all: $(NAME)

$(BUILDDIR)/libft.a: $(TARGETDIRS) $(LIBFTSRC)
	make -C srcs/libft
	mv srcs/libft/libft.a bld/

# Generate directory rules
$(foreach targetdir, $(TARGETDIRS), $(eval $(call generateDirs, $(targetdir))))

$(NAME): $(TARGETDIRS) $(OBJS) $(BUILDDIR)/libft.a
	$(HIDE)$(CC) $(CFLAGS) $(OBJS) $(BUILDDIR)/libft.a -o $(NAME) \
	-Lbld $(LDLIBS_LINK)

# Include dependencies
-include $(DEPS)

# Generate obj rules
$(foreach targetdir, $(TARGETDIRS), $(eval $(call generateRules, $(targetdir))))

clean:
	$(HIDE)$(RM) $(BUILDDIR)
	make clean -C srcs/libft

fclean: clean
	$(HIDE)$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
