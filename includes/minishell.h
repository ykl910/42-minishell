/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:17:29 by kyang             #+#    #+#             */
/*   Updated: 2025/03/04 13:10:01 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "colors.h"
# include "errors.h"
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
# include <term.h>
# include <termios.h>
# include <unistd.h>

# define SIGINT 2
# define SIGQUIT 3
# define MAX_FILE_SIZE 100000

// extern int				g_signal;

typedef enum e_token_type
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
	char				**cmd;
	char				*cmd_abs_path;
	int					status;
	int					infile_fd;
	int					outfile_fd;
	bool				redir_in;
	bool				redir_out;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

typedef struct s_env
{
	char				*name;
	char				*value;
	char				*key_val;
	struct s_env		*next;
}						t_env;

typedef struct s_cmd
{
	char				*abs_path;
	char				**cmd;
	int					fd_in;
	int					fd_out;
	bool				redir_in;
	bool				redir_out;
	int					status;
	pid_t				pid;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_shell
{
	t_env				*shell_env;
	t_token				*token_lst;
	t_ast_node			*ast;
	t_cmd				*clist;
	char				**paths;
	char				*prompt;
	int					status;
	int					prev_status;
	int					true_stdin;
	int					true_stdout;
}						t_shell;

// error
void					error_msg(char *msg, char *context);

// builtin
int						built_in_exec(t_shell *shell, char **cmd);
void					builtin_cd(char **cmd, t_shell *shell);
void					builtin_echo(char **cmd, t_shell *shell);
void					builtin_pwd(t_shell *shell);
void					builtin_export(char *line, t_shell *shell);
void					builtin_unset(char *target, t_shell *shell);
void					builtin_env(t_shell *shell);
void					builtin_exit(char **args, t_shell *shell);
char					*get_var_name(char *env_line);
char					*get_var_value(char *env_line);
int						put_env_var(char *line, char *name, char *value,
							t_shell *shell);
bool					is_numerical(char *str);
bool					is_cmd(char *prompt, char *cmd);
bool					is_path(char *target);

// env
void					import_env(t_shell *shell, char **envp);
void					update_env(t_env **env);
char					*variable_expension(char *varaible, t_shell *shell);
void					shell_init(t_shell *shell, char **envp);
char					**env_lst_to_array(t_env *env);
void					get_paths(t_shell *shell);

// lexer
t_token					*init_token(e_token type, char *av);
int						ft_issep(char c);
int						is_token_separator(char *av, int i);
int						count_input(char *av);
int						check_unclosed(char *av);
t_token					*create_token(char *av, int *i);
t_token					*lexer(char *av);
int						check_lexer(t_token **tokens);
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
bool					match_subpatterns(char **sub_patterns, char *pattern, char *file,
							int f_size);
bool					is_not_hidden_file(char *file);
void					expand_var(t_token *token, t_shell *shell);
void					expand_wc(t_token *token);
void					expand_token(t_token **token, t_shell *shell);

// parser
int						get_precedence(e_token token);
e_command				get_command_type(e_token token_type);
t_ast_node				*create_node(e_command type, t_ast_node *left,
							t_ast_node *right, char *value);
char					**append_args(char **origin_args, char *new_arg);
t_ast_node				*parse_expression(t_token **tokens, int min_precedence,
							t_shell *shell);
char					**quotes_handler(char **args);

// exec
void					cmd_builder(t_ast_node *node);
void					simple_parse_path(t_ast_node *node, t_shell *shell);
void					put_heredoc(int infile_fd, char *limiter);
void					reopen_heredoc(int *infile_fd, char *file);
void					handle_open_error(int *fd, char *file);
bool					is_urandom(char *str);
int						execute_command(t_ast_node *node, t_shell *shell);
void					redir_std(t_ast_node **current);
void					executor(t_ast_node **head_node, t_shell *shell);
bool					simple_is_redir(t_ast_node *node, char **args, int *i);

// v2 pipes
int						run_pipe(t_ast_node *node, t_shell *shell);
t_cmd					*get_clist(t_ast_node *node);
int						parse_cmd(t_cmd **clst_node, t_ast_node *ast_node);
void					pipes_parse_path(t_cmd *current, t_shell *shell);
void					p_handle_cmd_error(t_cmd **current, int err_code);
void					p_handle_error(t_cmd **current, t_shell *shell);
void					s_handle_cmd_error(t_ast_node **current, int err_code);
void					s_handle_error(t_ast_node **current, t_shell *shell);
void					handle_open_error(int *fd, char *file);
bool					is_redir(t_cmd *clst_node, char **args, int *i);

// v2 simple
void					parse_simple_cmd(t_ast_node *node, t_shell *shell);

// signal
void					handle_sigint(int sig);
int						get_return_value(int *status);
void					process_handle_sigint(int sig);
void					process_handle_sigquit(int sig);
void					input_eof(char **line, t_shell *shell);
void					signals(void);
void					process_signals(void);

// cleanup
void					free_ast(t_ast_node *node);
void					free_wildcard(t_wildcards *node);
void					free_env(t_env **node);
void					free_tokens(t_token **node);
void					free_shell(t_shell *shell);
void					free_clist(t_cmd **cmd_lst);
void					free_exit(int *exit_status, t_shell *shell);

#endif
