# Set project directory one level above the Makefile directory. $(CURDIR) is a GNU make variable containing the path to the current working directory
PROJDIR := $(CURDIR)
SOURCEDIR := $(PROJDIR)/srcs
BUILDDIR := $(PROJDIR)/bld

# Name of the final executable
NAME = minishell

# Decide whether the commands will be shown or not
VERBOSE = TRUE

# Create the list of directories
DIRS = common libft libft/ft_printf/srcs

SOURCEDIRS = $(foreach dir, $(DIRS), $(addprefix $(SOURCEDIR)/, $(dir)))
TARGETDIRS = $(foreach dir, $(DIRS), $(addprefix $(BUILDDIR)/, $(dir)))

# Generate the GCC includes parameters by adding -I before each source folder
# INCLUDES = $(foreach dir, $(SOURCEDIRS), $(addprefix -I, $(dir)))
INCLUDES = -I $(SOURCEDIR)/incs $(SOURCEDIR)/libft $(SOURCEDIR)/libft/ft_printf/incs
# Add this list to VPATH, the place make will look for the source files
VPATH = $(SOURCEDIRS)

# Create a list of *.c sources in DIRS
SOURCES = $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c))

# Define objects for all sources
OBJS := $(subst $(SOURCEDIR),$(BUILDDIR),$(SOURCES:%.c=%.o))

# Define dependencies files for all objects
DEPS = $(OBJS:%.o=%.d)

# Name the compiler
CC = gcc

LDLIBS = -lm

RM = rm -rf
RMDIR = rm -rf
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
	$(HIDE)$(CC) -c $$(INCLUDES) -o $$(subst /,$$(PSEP),$$@) $$(subst /,$$(PSEP),$$<) -MMD $(LDLIBS)
endef

all: directories $(NAME)

$(NAME): $(OBJS)
	$(HIDE)echo Linking $@
	$(HIDE)$(CC) $(OBJS) -o $(NAME) $(LDLIBS)

# Include dependencies
-include $(DEPS)

# Generate rules
$(foreach targetdir, $(TARGETDIRS), $(eval $(call generateRules, $(targetdir))))

directories:
	$(HIDE)$(MKDIR) $(subst /,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)

# Remove all objects, dependencies and executable files generated during the build
clean:
	$(HIDE)$(RMDIR) $(subst /,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)
	$(HIDE)$(RM) $(NAME) $(ERRIGNORE)
	@echo Cleaning done !

# Indicate to make which targets are not files
.PHONY: all clean directories
