/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:43:10 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/29 20:41:22 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	new_process(t_lst *command, char **env)
{
	if (command->path)
	{
		if (access(command->path, F_OK | X_OK) == 0)
			execve(command->path, command->name, env);
	}
}

static void	parent_process(t_data *data, int *pipe, t_lst *cmd)
{
	pipes_dup_for_parent(pipe, cmd, data->cmd_lst_size);
	close(pipe[0]);
	close(pipe[1]);
}

static void	child_process(t_data *data, int *pipe, t_lst *cmd, char **env)
{
	pipes_dup_for_child(pipe, data->fds, cmd, data->cmd_lst_size);
	if (data->fds.infile_fd != STDIN_FILENO)
		close(data->fds.infile_fd);
	if (data->fds.outfile_fd != STDOUT_FILENO)
		close(data->fds.outfile_fd);
	close(pipe[0]);
	close(pipe[1]);
	new_process(cmd, env);
}

static void	create_fork(t_data *data, t_lst *cmd, char **env)
{
	int		pipex[2];
	pid_t	pid;

	if (pipe(pipex) < 0)
		exit(EXIT_FAILURE);
	pid = fork();
	cmd->cmd_pid = pid;
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
		child_process(data, pipex, cmd, env);
	else
		parent_process(data, pipex, cmd);
}

void	run_cmds(t_data *data, char **env)
{
	t_lst	*current_cmd;
	int		status;

	status = 0;
	current_cmd = data->cmd_lst;
	if (data->fds.infile_fd < 0)
		return ;
	while (current_cmd)
	{
		create_fork(data, current_cmd, env);
		current_cmd = current_cmd->next;
	}
	current_cmd = data->cmd_lst;
	while (current_cmd)
	{
		waitpid(current_cmd->cmd_pid, NULL, 0);
		current_cmd = current_cmd->next;
	}
	if (WIFEXITED(status))
		data->return_value = WEXITSTATUS(status);
	else
		data->return_value = 1;
}
