/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:17:29 by kyang             #+#    #+#             */
/*   Updated: 2025/02/04 17:22:07 by kyang            ###   ########.fr       */
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
}							e_token;

typedef struct s_token
{
	e_token					token_type;
	char					*value;
}							t_token;

typedef struct s_command	t_command;

typedef struct s_command
{
	char					**name;
	char					*in_file;
	char					*out_file;
	int						index;
	t_command				*next;
}							t_command;

// lexer
int							count_input(char *av);
int							ft_issep(char c);
t_token						*init_token(e_token type, char *av);
t_token						**lexer(char *av);

// parser
t_command					*init_command(void);
char						**append_args(char **origin_args, char *new_arg);
t_command					*parser(t_token **tokens);

// exec


#endif
