/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:17:29 by kyang             #+#    #+#             */
/*   Updated: 2025/02/04 19:33:15 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
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
# include <termios.h>
# include <unistd.h>

typedef enum
{
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HERE_DOC,
	TOKEN_REDIRECT_APPEND,
	TOKEN_TEXT,
}						e_token;

typedef struct s_token
{
	e_token				token_type;
	char				*value;
}						t_token;

typedef struct s_command
{
	char				**name;
	char				*in_file;
	char				*out_file;
	int					index;
	struct s_command	*next;
}						t_command;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_shell
{
	t_token				**tokens;
	t_command			**cmd_lst;
	t_env				**env;
	int					status;
}						t_shell;

// lexer
int						count_input(char *av);
int						ft_isspace(char c);
t_token					*init_token(e_token type, char *av);
t_token					**lexer(char *av);

// parser

// exec
char					*get_path(char **paths, char *arg, char **split_arg);
char					*get_env(char *arg, char **split_arg);
char					**exec_args(char *av);
char					**exec_args_list(char **args, char *first, int i,
							int j);
void					free_split(char **split);
void					free_split2(char **split);
void					free_splits(char **split1, char **split2, char *arg);
void					execute_command(char *av, char **env);

// built in

// ERROR
void					error(char *msg, char *target);

#endif
