/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:17:29 by kyang             #+#    #+#             */
/*   Updated: 2025/01/30 12:39:07 by kyang            ###   ########.fr       */
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
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <termios.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"

char	*get_path(char **paths, char *arg, char **split_arg);
char	*get_env(char *arg, char **split_arg);
char	**exec_args(char *av);
char	**exec_args_list(char **args, char *first, int i, int j);
void	free_split(char **split);
void	free_split2(char **split);
void	free_splits(char **split1, char **split2, char *arg);
void	error(void);
void	built_in_command(char *r);
void	execute_command(char *av, char **env);


#endif