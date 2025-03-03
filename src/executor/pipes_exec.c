/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:02:57 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/03 17:13:54 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipes_std_dup(t_cmd **current, t_shell *shell)
{
	if ((*current)->fd_in != -1)
	{
		if (dup2((*current)->fd_in, STDIN_FILENO) == -1)
			p_handle_error(current, shell);
		close((*current)->fd_in);
	}
	if ((*current)->fd_out != -1)
	{
		if (dup2((*current)->fd_out, STDOUT_FILENO) == -1)
			p_handle_error(current, shell);
		close((*current)->fd_out);
	}
}

static void	execute_cmd(t_cmd *current, t_shell *shell)
{
	char	**temp_env_array;

	temp_env_array = NULL;
	if (current->redir_in && current->fd_in == -1)
		p_handle_error(&current, shell);
	if (current->redir_out && current->fd_out == -1)
		p_handle_error(&current, shell);
	if (built_in_exec(shell, current->cmd) == -1)
	{
		pipes_parse_path(current, shell);
		shell->status = current->status;
		if (!current->abs_path)
			free_exit(&current->status, shell);
		temp_env_array = env_lst_to_array(shell->shell_env);
		execve(current->abs_path, current->cmd, temp_env_array);
	}
	free_exit(&current->status, shell);
}

static void	child_process(t_cmd *current, int *pipes, t_shell *shell)
{
	if (current->fd_out == -1 && current->next)
	{
		if (dup2(pipes[1], STDOUT_FILENO) == -1)
			p_handle_error(&current, shell);
	}
	close(pipes[0]);
	close(pipes[1]);
	execute_cmd(current, shell);
}

static void	parent_process(t_cmd *current, int *pipes, t_shell *shell)
{
	if (current->next)
	{
		if (dup2(pipes[0], STDIN_FILENO) == -1)
			p_handle_error(&current, shell);
	}
	close(pipes[0]);
	close(pipes[1]);
}

static void	create_fork(t_cmd *current, t_shell *shell)
{
	int		pipes[2];
	pid_t	pid;

	if (pipe(pipes) < 0)
		p_handle_error(&current, shell);
	pipes_std_dup(&current, shell);
	pid = fork();
	current->pid = pid;
	if (pid < 0)
		p_handle_error(&current, shell);
	if (pid == 0)
		child_process(current, pipes, shell);
	else
		parent_process(current, pipes, shell);
}

int	run_pipe(t_ast_node *node, t_shell *shell)
{
	t_cmd	*current_cmd;
	int		status;

	shell->clist = get_clist(node);
	current_cmd = shell->clist;
	while (1)
	{
		create_fork(current_cmd, shell);
		if (!current_cmd->next)
			break ;
		current_cmd = current_cmd->next;
	}
	current_cmd = shell->clist;
	while (current_cmd)
	{
		waitpid(current_cmd->pid, &status, 0);
		current_cmd = current_cmd->next;
	}
	return (get_return_value(&status));
}
