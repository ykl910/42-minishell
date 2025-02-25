/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:51:46 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/25 10:26:05 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_process(t_ast_node *node, t_shell *shell)
{
	char	**temp_env_array;

	temp_env_array = NULL;
	if (node->redir_in && node->infile_fd == -1)
		exit(1);
	if (node->redir_out && node->outfile_fd == -1)
		exit(1);
	if (node->status == 0)
	{
		if (built_in_exec(shell, node) == -1)
		{
			parse_path(node, shell);
			shell->status = node->status;
			if (!node->cmd_abs_path)
				exit(node->status);
			shell->status = node->status;
			temp_env_array = env_lst_to_array(shell->shell_env);
			execve(node->cmd_abs_path, node->cmd, temp_env_array);
		}
	}
	exit(node->status);
}

void	pipe_forker(int *pipe_fd, t_ast_node *node, t_shell *shell,
		int input_fd)
{
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(pipe_fd[1]);
		execute_pipeline(node->left, shell, input_fd);
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[1]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
}

int	cmd_forker(t_ast_node *node, t_shell *shell, int input_fd)
{
	pid_t	pid;
	int		status;

	cmd_builder(node);
	redir_std(&node);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (input_fd != STDIN_FILENO)
		{
			if (dup2(input_fd, STDIN_FILENO) == -1)
				exit(EXIT_FAILURE);
			close(input_fd);
		}
		new_process(node, shell);
		exit(EXIT_FAILURE);
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

// int	execute_pipeline(t_ast_node *node, t_shell *shell, int input_fd)
// {
// 	int		pipe_fd[2];
// 	pid_t	pid;
// 	int		status;

// 	if (!node)
// 		return (node->status);
// 	if (node->node_type == COMMAND_PIPE)
// 	{
// 		if (pipe(pipe_fd) == -1)
// 			exit(EXIT_FAILURE);
// 		pid = fork();
// 		if (pid == -1)
// 			exit(EXIT_FAILURE);
// 		if (pid == 0)
// 		{
// 			close(pipe_fd[0]);
// 			if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
// 				exit(EXIT_FAILURE);
// 			close(pipe_fd[1]);
// 			execute_pipeline(node->left, shell, input_fd);
// 			exit(EXIT_FAILURE);
// 		}
// 		close(pipe_fd[1]);
// 		if (input_fd != STDIN_FILENO)
// 			close(input_fd);
// 		return (execute_pipeline(node->right, shell, pipe_fd[0]));
// 	}
// 	else
// 	{
// 		cmd_builder(node);
// 		redir_std(&node);
// 		pid = fork();
// 		if (pid == -1)
// 			exit(EXIT_FAILURE);
// 		if (pid == 0)
// 		{
// 			if (input_fd != STDIN_FILENO)
// 			{
// 				if (dup2(input_fd, STDIN_FILENO) == -1)
// 					exit(EXIT_FAILURE);
// 				close(input_fd);
// 			}
// 			new_process(node, shell);
// 			exit(EXIT_FAILURE);
// 		}
// 		if (input_fd != STDIN_FILENO)
// 			close(input_fd);
// 		waitpid(pid, &status, 0);
// 		return (get_return_value(&status));
// 	}
// }
