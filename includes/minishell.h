/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:17:29 by kyang             #+#    #+#             */
/*   Updated: 2025/02/06 15:56:43 by alacroix         ###   ########.fr       */
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
}					e_token;

typedef enum e_node_type
{
	COMMAND,       // CMD
	PIPE,          // |
	AND,           // &&
	OR,            // ||
	REDIR_IN,      // <
	RDIT_OUT,      // >
	REDIR_APPEND,  // >>
	REDIR_HEREDOC, // <<
	SUBSHELL       // (..)
}					t_node_type;

typedef struct s_token
{
	e_token			token_type;
	char			*value;
}					t_token;

typedef struct s_ast
{
	t_node_type node_type;    // atom type
	char **args;              // CMD args
	struct s_ast *left_node;  // left son
	struct s_ast *right_node; // right son
	struct s_ast *subshell;   // manage Subshells
	char *redir_file;         // target filles for redirections
	struct s_ast *next;       // chain redirections
}					t_ast;

/*MAIN*/
int					main(int ac, char **envp);

/*LEXER*/
int					count_input(char *av);
int					ft_issep(char c);
t_token				*init_token(e_token type, char *av);
t_token				**lexer(char *av);

/*PARSER*/
t_ast	*parser(t_token *token_lst);

/*EXECUTOR*/

#endif
