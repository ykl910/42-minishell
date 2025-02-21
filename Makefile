NAME = minishell

SRCDIR = src
OBJDIR = obj
INCDIR = includes

SRC_MAIN = src/main.c
SRC_ERROR = src/errors.c
SRC_ENV = src/env/import_env.c src/env/var_expension.c src/env/env_array.c src/env/create_shell.c
SRC_BUILTIN = src/builtin/builtin.c src/builtin/builtin_utils.c
SRC_LEXER = src/lexer/lexer.c src/lexer/lexer_utils.c src/lexer/wildcards.c src/lexer/wildcards2.c src/lexer/wildcards_utils.c src/lexer/lexer_errors.c src/lexer/expand.c src/lexer/expand_utils.c
SRC_PARSER = src/parser/create_ast.c src/parser/parser_utils.c src/parser/quotes_handler.c
SRC_SIGNAL = src/signal/signal.c
SRC_EXECUTOR = src/executor/execution.c src/executor/pipes_exe.c src/executor/pipes_redir.c src/executor/pipes_utils.c src/executor/simple_exe.c src/executor/put_heredoc.c src/executor/pipes_redir_utils.c
SRC_CLEANUP = src/cleanup/structs_free.c

SRC = $(SRC_MAIN) $(SRC_ERROR) $(SRC_ENV) $(SRC_BUILTIN) $(SRC_LEXER) $(SRC_PARSER) $(SRC_SIGNAL) $(SRC_EXECUTOR) $(SRC_CLEANUP)
OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE := $(LIBFT_DIR)/includes
LDFLAGS = -L$(LIBFT_DIR)
LIBS = $(LIBFT)

READ_LIB = -lreadline

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
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LIBS) $(READ_LIB) -o $(NAME)

$(LIBFT):
	$(MAKE) --silent -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) --silent -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
.DEFAULT_GOAL := all
