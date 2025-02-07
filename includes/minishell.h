/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:17:29 by kyang             #+#    #+#             */
/*   Updated: 2025/02/07 12:39:35 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef enum
{
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HERE_DOC,
	TOKEN_REDIRECT_APPEND,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_TEXT,
}			e_token;

typedef enum e_node_type
{
	COMMAND_SIMPLE,
	COMMAND_PIPE,
	COMMAND_AND,
	COMMAND_OR,
	COMMAND_REDIRECT_IN,
	COMMAND_REDIRECT_OUT,
	COMMAND_HERE_DOC,
	COMMAND_REDIRECT_APPEND,
	COMMAND_SUBSHELL,
}							e_command;

typedef struct s_token		t_token;

typedef struct s_token
{
	e_token					token_type;
	char					*value;
	t_token					*next;
}							t_token;

typedef struct s_ast_node	t_ast_node;

typedef struct s_ast_node
{
	e_command				node_type;
	char					**value;
	t_ast_node				*left;
	t_ast_node				*right;
}							t_ast_node;

// lexer
t_token						*init_token(e_token type, char *av);
int							ft_issep(char c);
int							count_redir_text(char *av, int *i);
int							count_logical_ops_parantheses(char *av, int *i);
int							count_input(char *av);
t_token						*create_redir(char *av, int *i);
t_token						*create_logical_ops_parantheses(char *av, int *i);
t_token						*create_pipe_text(char *av, int *i);
t_token						*create_token(char *av, int *i);
t_token						*lexer(char *av);

// parser
int							get_precedence(e_token token);
e_command					get_command_type(e_token token_type);
t_ast_node					*create_node(e_command type, t_ast_node *left,
								t_ast_node *right, char *value);
char						**append_args(char **origin_args, char *new_arg);
t_ast_node					*parse_primary(t_token **tokens);
t_ast_node					*parse_expression(t_token **tokens,
								int min_precedence);

// exec

#endif
