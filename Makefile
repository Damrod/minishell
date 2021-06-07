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
	   libft/string libft/list/dllist
DIRS = common
DIRS += $(LIBFTD)
SOURCEDIRS = $(foreach dir, $(DIRS), $(addprefix $(SOURCEDIR)/, $(dir)))
TARGETDIRS = $(foreach dir, $(DIRS), $(addprefix $(BUILDDIR)/, $(dir)))
# glob sources from sourcedirs. Eventually we should hardcode this
SOURCES = $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c))
OBJS := $(subst $(SOURCEDIR),$(BUILDDIR),$(SOURCES:%.c=%.o))
DEPS = $(OBJS:%.o=%.d)
# look for includes in the source dirs
# INCLUDES = $(foreach dir, $(SOURCEDIRS), $(addprefix -I, $(dir)))
# hardcoded include paths
INCLUDES += -I $(SOURCEDIR)/incs -I $(SOURCEDIR)/libft/incs					   \
			-I $(SOURCEDIR)/libft/ft_printf/incs
VPATH = $(SOURCEDIRS)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g # -fsanitize=address
LDLIBS = -lm -lncurses

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

# Generate directory rules
$(foreach targetdir, $(TARGETDIRS), $(eval $(call generateDirs, $(targetdir))))

$(NAME): $(TARGETDIRS) $(OBJS)
	$(HIDE)echo Linking $@
	$(HIDE)$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)

# Include dependencies
-include $(DEPS)

# Generate obj rules
$(foreach targetdir, $(TARGETDIRS), $(eval $(call generateRules, $(targetdir))))

clean:
	$(HIDE)$(RM) $(OBJS) $(ERRIGNORE)

fclean: clean
	$(HIDE)$(RM) $(BUILDDIR)
	$(HIDE)$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
