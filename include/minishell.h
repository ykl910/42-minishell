/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:17:29 by kyang             #+#    #+#             */
/*   Updated: 2025/01/30 17:58:58 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <termios.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"

typedef enum 
{
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HERE_DOC,
	TOKEN_REDIRECT_APPEND,
}	e_token;

typedef struct s_token
{
	e_token	token_type;
	char	*value;
}	t_token;

// lexer
int	count_input(char *av);
t_token	*init_token(e_token	type, char *av);


// exec
char	*get_path(char **paths, char *arg, char **split_arg);
char	*get_env(char *arg, char **split_arg);
char	**exec_args(char *av);
char	**exec_args_list(char **args, char *first, int i, int j);
void	free_split(char **split);
void	free_split2(char **split);
void	free_splits(char **split1, char **split2, char *arg);
void	error(void);
void	execute_command(char *av, char **env);

// built in
void	built_in_cd(char *r);


#endif