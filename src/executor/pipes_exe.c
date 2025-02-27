/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:51:46 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/27 19:09:37 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_error(t_ast_node *node, t_shell *shell)
{
	node->status = 1;
	free_exit(&node->status, shell);
}

void	new_process(t_ast_node *node, t_shell *shell)
{
	char	**temp_env_array;

	temp_env_array = NULL;
	if (node->redir_in && node->infile_fd == -1)
		handle_error(node, shell);
	if (node->redir_out && node->outfile_fd == -1)
		handle_error(node, shell);
	if (node->status == 0)
	{
		if (built_in_exec(shell, node) == -1)
		{
			parse_path(node, shell);
			shell->status = node->status;
			if (!node->cmd_abs_path)
				free_exit(&node->status, shell);
			shell->status = node->status;
			temp_env_array = env_lst_to_array(shell->shell_env);
			execve(node->cmd_abs_path, node->cmd, temp_env_array);
		}
	}
	free_exit(&node->status, shell);
}

static void	pipe_forker(int *pipe_fd, t_ast_node *node, t_shell *shell,
		int input_fd)
{
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		handle_error(node, shell);
	pid = fork();
	if (pid == -1)
		handle_error(node, shell);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			handle_error(node, shell);
		close(pipe_fd[1]);
		execute_pipeline(node->left, shell, input_fd);
		free_exit(&node->left->status, shell);
	}
	close(pipe_fd[1]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
}

static int	cmd_forker(t_ast_node *node, t_shell *shell, int input_fd)
{
	pid_t	pid;
	int		status;

	cmd_builder(node);
	redir_std(&node);
	pid = fork();
	if (pid == -1)
		handle_error(node, shell);
	if (pid == 0)
	{
		if (input_fd != STDIN_FILENO && !node->redir_in)
		{
			if (dup2(input_fd, STDIN_FILENO) == -1)
				handle_error(node, shell);
		}
		new_process(node, shell);
		handle_error(node, shell);
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	waitpid(pid, &status, 0);
	return (get_return_value(&status));
}

int	execute_pipeline(t_ast_node *node, t_shell *shell, int input_fd)
{
	int	pipe_fd[2];

	if (!node)
		return (node->status);
	if (node->node_type == COMMAND_PIPE)
	{
		pipe_forker(pipe_fd, node, shell, input_fd);
		return (execute_pipeline(node->right, shell, pipe_fd[0]));
	}
	else
		return (cmd_forker(node, shell, input_fd));
}
