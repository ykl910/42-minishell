/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:17:29 by kyang             #+#    #+#             */
/*   Updated: 2025/02/11 15:55:18 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
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

# define SIGINT  2
# define SIGQUIT 3

extern volatile sig_atomic_t	g_sigint_flag;

typedef enum
{
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HERE_DOC,
	TOKEN_REDIRECT_APPEND,
	TOKEN_TEXT,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
}						e_token;

typedef enum e_node_type
{
	COMMAND_SIMPLE,
	COMMAND_PIPE,
	COMMAND_AND,
	COMMAND_OR,
	// COMMAND_REDIRECT_IN,
	// COMMAND_REDIRECT_OUT,
	// COMMAND_HERE_DOC,
	// COMMAND_REDIRECT_APPEND,
	COMMAND_SUBSHELL,
}						e_command;

typedef struct s_wildcard
{
	char				*file;
	int					index;
	struct s_wildcard	*next;
}						t_wildcards;

typedef struct s_token
{
	e_token				token_type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_ast_node
{
	e_command			node_type;
	char				**value;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_shell
{
	t_env				*shell_env;
	t_token				*token_lst;
	t_ast_node			*ast;
	int					status;
}						t_shell;

// builtin
void					builtin_cd(char **cmd, t_shell *shell);
void					builtin_echo(char **cmd, int *status);
void					builtin_pwd(int *status);
void					builtin_export(char *line, t_env **env, int *status);
void					builtin_unset(char *target, t_env **env, int *status);
void					builtin_env(t_env **env, int *status);
void					builtin_exit(char **args, int *status);
char					*get_var_name(char *env_line);
char					*get_var_value(char *env_line);
bool					create_head_env_lst(char **name, char **value,
							t_env **env);
bool					create_node_env_lst(char **name, char **value,
							t_env **env);
bool					is_numerical(char *str);

// env
void					import_env(t_env **env, char **envp, int *status);
void					update_env(t_env **env);

// lexer
t_token					*init_token(e_token type, char *av);
int						ft_issep(char c);
int						is_token_separator(char *av, int i);
int						is_token_separator(char *av, int i);
int						count_redir_text(char *av, int *i);
int						count_logical_ops_parantheses(char *av, int *i);
int						count_input(char *av);
t_token					*create_redir(char *av, int *i);
t_token					*create_logical_ops_parantheses(char *av, int *i);
t_token					*create_pipe_text(char *av, int *i);
t_token					*create_token(char *av, int *i);
t_token					*lexer(char *av);
void					check_lexer(t_token **tokens);
t_wildcards				*wildcard_expension(char *pattern);
void					free_wc_struct(t_wildcards **head);
int						create_head_wc(t_wildcards **head, char *file,
							int index);
int						create_node_wc(t_wildcards **head, char *file,
							int index);
int						wc_struct(t_wildcards **node, char *file, int index);
int						occurence_count(char *str, char occurence);
bool					match_prefix(char *file, char *pattern, int p_size);
bool					match_suffix(char *file, char *pattern, int f_size,
							int p_size);
bool					match_subpatterns(char **sub_patterns, char *file,
							int f_size);

// parser
int						get_precedence(e_token token);
e_command				get_command_type(e_token token_type);
t_ast_node				*create_node(e_command type, t_ast_node *left,
							t_ast_node *right, char *value);
char					**append_args(char **origin_args, char *new_arg);
t_ast_node				*parse_primary(t_token **tokens);
t_ast_node				*parse_expression(t_token **tokens, int min_precedence);

// exec

// signal
void					handle_sigint(int sig);
void					handle_sigquit(int sig);

#endif
