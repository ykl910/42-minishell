NAME = minishell

SRCDIR = src
OBJDIR = obj
INCDIR = includes

SRC_MAIN = src/main.c
SRC_ENV = src/env/import_env.c src/env/var_expension.c
SRC_BUILTIN = src/builtin/builtin.c src/builtin/builtin_utils.c
SRC_LEXER = src/lexer/lexer.c src/lexer/lexer_utils.c src/lexer/wildcards.c src/lexer/wildcards2.c src/lexer/wildcards_utils.c src/lexer/lexer_errors.c
SRC_PARSER = src/parser/precedence_climbing_2.c src/parser/parser_utils.c

SRC = $(SRC_MAIN) $(SRC_ENV) $(SRC_BUILTIN) $(SRC_LEXER) $(SRC_PARSER)
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
