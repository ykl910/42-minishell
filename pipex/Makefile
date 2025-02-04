NAME = pipex

SRCDIR = src
OBJDIR = obj
INCDIR = inc


SRC_MAIN = src/main.c
SRC_ERRORS = src/error.c
SRC_PARSING = src/parsing/absolute_path_arg.c src/parsing/check_args.c src/parsing/create_cmd_lst.c \
					src/parsing/parsing_utils.c src/parsing/put_here_doc.c src/parsing/relative_path_arg.c \
					src/parsing/urandom_parsing.c
SRC_STRUCT = src/struct/data_cleanup.c src/struct/data_init.c src/struct/lst_init.c src/struct/lst_utils.c
SRC_PROCESS = src/process/run_cmds.c src/process/pipes_redirections.c

SRC = $(SRC_MAIN) $(SRC_ERRORS) $(SRC_PARSING) $(SRC_STRUCT) $(SRC_PROCESS)

OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))

LIBFT_DIR := ../libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE := $(LIBFT_DIR)/includes
LDFLAGS = -L$(LIBFT_DIR)
LIBS = $(LIBFT)

AR = ar
ARFLAGS = rcs

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -g3 -I$(LIBFT_INCLUDE)

all: $(OBJDIR) $(LIBFT) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR) || true

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(OBJ:.o=.d)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) --silent -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) --silent -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
.DEFAULT_GOAL := all
