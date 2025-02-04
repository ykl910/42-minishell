/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:05:07 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/04 14:02:42 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define MAX_FILE_SIZE 100000
# define FD_MAX 1024

# include "../../libft/includes/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_lst
{
	char	**name;
	char	*path;
	int		index;
	pid_t	cmd_pid;
	void	*next;
}			t_lst;

typedef struct s_fd
{
	int		infile_fd;
	int		outfile_fd;
	int		urandom_fd;
}			t_fd;

typedef struct s_data
{
	t_lst	*cmd_lst;
	t_fd	fds;
	int		cmd_lst_size;
	bool	is_here_doc;
	bool	is_urandom;
	int		return_value;
}			t_data;

/*MAIN*/
int			main(int argc, char **argv, char **envp);

/*ERROR*/
void		error(char *msg, char *target);

/*ABSOLUTE PATH ARG*/
bool		create_node_abs(t_data *data, char *arg);

/*CHECK ARGS*/
bool		check_args(t_data *data, int ac, char **av);

/*CREATE CMD LST*/
bool		create_cmd_lst(t_data *data, int ac, char **av, char **env);

/*PARSING UTILS*/
char		*str_fusion(char *buffer, char *line);
bool		is_absolute_path(char *arg);
bool		add_subpath(char **path);
int			tab_size(char **tab);
bool		only_spaces(char *tab);

/*PUT HERE DOC*/
void		re_open_temp_doc(t_fd *fds);
bool		put_here_doc(t_fd *fds, char *limiter);

/*URANDOM PARSING*/
bool		put_urandom(t_fd *fds);
void		urandom_open(t_fd *fds, int ac, char **av);
void		check_urandom(t_data *data, char *arg);

/*RELATIVE PATH ARG*/
bool		create_node_rel(t_data *data, char **paths, char *arg);

/*DATA CLEANUP*/
void		data_cleanup(t_data *data);

/*DATA INIT*/
void		data_init(t_data *data);

/*LST INIT*/
bool		put_cmd_lst(t_lst **cmd_lst, char **cmd, char *path);

/*LST UTILS*/
void		put_index(t_lst **head);
int			get_cmd_size(t_lst **head);

/*RUN CMDS*/
void		run_cmds(t_data *data, char **env);

/*PIPES REDIRECTIONS*/
void		pipes_dup_for_child(int *pipe, t_fd fds, t_lst *cmd, int size);
void		pipes_dup_for_parent(int *pipe, t_lst *cmd, int size);

#endif
