# Set project directory one level above the Makefile directory. $(CURDIR)
#is a GNU make variable containing the path to the current working directory
PROJDIR := $(CURDIR)
SOURCEDIR := $(PROJDIR)/srcs
BUILDDIR := $(PROJDIR)/bld
NAME = minishell
VERBOSE = TRUE

# source directories with $(SOURCEDIR) as root
DIRS = common libft libft/ft_printf/srcs

SOURCEDIRS = $(foreach dir, $(DIRS), $(addprefix $(SOURCEDIR)/, $(dir)))
TARGETDIRS = $(foreach dir, $(DIRS), $(addprefix $(BUILDDIR)/, $(dir)))
# look for includes in the source dirs
INCLUDES = $(foreach dir, $(SOURCEDIRS), $(addprefix -I, $(dir)))
# hardcoded include paths
INCLUDES += -I $(SOURCEDIR)/incs -I $(SOURCEDIR)/libft						   \
			-I $(SOURCEDIR)/libft/ft_printf/incs
VPATH = $(SOURCEDIRS)

# glob sources from sourcedirs. Eventually we should hardcode this
SOURCES = $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c))
OBJS := $(subst $(SOURCEDIR),$(BUILDDIR),$(SOURCES:%.c=%.o))
DEPS = $(OBJS:%.o=%.d)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

# linker libraries
LDLIBS = -lm

RM = rm -rf
MKDIR = mkdir -p
ERRIGNORE = 2>/dev/null
SEP=/

# Remove space after separator
PSEP = $(strip $(SEP))

# Hide or not the calls depending of VERBOSE
ifeq ($(VERBOSE),TRUE)
	HIDE =
else
	HIDE = @
endif

# Define the function that will generate each rule
define generateRules
$(1)/%.o: %.c
	@echo Building $$@
	$(HIDE)$(CC) -c $(CFLAGS) $$(INCLUDES) -o $$(subst /,$$(PSEP),$$@) $$(subst /,$$(PSEP),$$<) -MMD $(LDLIBS)
endef

all: $(NAME)

$(NAME): directories $(OBJS)
	$(HIDE)echo Linking $@
	$(HIDE)$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)

# Include dependencies
-include $(DEPS)

# Generate rules
$(foreach targetdir, $(TARGETDIRS), $(eval $(call generateRules, $(targetdir))))

directories:
	$(HIDE)$(MKDIR) $(subst /,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)

clean:
	$(HIDE)$(RM) $(subst /,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)
	$(HIDE)$(RM) $(NAME) $(ERRIGNORE)
	@echo Cleaning done !

fclean: clean
	$(HIDE)$(RM) $(BUILDDIR)
	$(HIDE)$(RM) $(NAME)

re: fclean all

# Indicate to make which targets are not files
.PHONY: all clean fclean re directories
