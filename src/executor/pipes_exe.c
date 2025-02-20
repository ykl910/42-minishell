/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:51:46 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/20 14:30:57 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	new_process(t_ast_node *node, t_shell *shell)
// {
// 	char	**temp_env_array;

// 	temp_env_array = NULL;
// 	if (node->status == 0)
// 	{
// 		if (built_in_exec(shell, node) == -1)
// 		{
// 			parse_path(node, shell);
// 			shell->status = node->status;
// 			if (!node->cmd_abs_path)
// 				exit(node->status);
// 			shell->status = node->status;
// 			temp_env_array = env_lst_to_array(shell->shell_env);
// 			execve(node->cmd_abs_path, node->cmd, temp_env_array);
// 		}
// 	}
// 	exit(node->status);
// }

// static void	second_child_process(t_ast_node *node, t_shell *shell, int *pipex)
// {
// 	if (node->node_type == COMMAND_SIMPLE)
// 	{
// 		pipe_redir_cmd(node);
// 		redir_std(&node);
// 	}
// 	else
// 	{
// 		if (dup2(node->outfile_fd, STDIN_FILENO) == -1)
// 			exit(EXIT_FAILURE);
// 		if (dup2(pipex[1], STDOUT_FILENO) == -1)
// 			exit(EXIT_FAILURE);
// 	}
// 	if (node->infile_fd < 0)
// 	{
// 		if (dup2(pipex[0], STDIN_FILENO) == -1)
// 			exit(EXIT_FAILURE);
// 	}
// 	close(pipex[0]);
// 	close(pipex[1]);
// 	new_process(node, shell);
// }

// static void	first_child_process(t_ast_node *node, t_shell *shell, int *pipex)
// {
// 	if (node->node_type == COMMAND_SIMPLE)
// 	{
// 		pipe_redir_cmd(node);
// 		redir_std(&node);
// 	}
// 	else
// 	{
// 		if (dup2(node->outfile_fd, STDIN_FILENO) == -1)
// 			exit(EXIT_FAILURE);
// 		if (dup2(pipex[1], node->outfile_fd) == -1)
// 			exit(EXIT_FAILURE);
// 	}
// 	if (node->outfile_fd < 0)
// 	{
// 		if (dup2(pipex[1], STDOUT_FILENO) == -1)
// 			exit(EXIT_FAILURE);
// 	}
// 	close(pipex[0]);
// 	close(pipex[1]);
// 	new_process(node, shell);
// }

// int	execute_pipe(t_ast_node *pipe_node, t_ast_node *left_node,
// 		t_ast_node *right_node, t_shell *shell)
// {
// 	int		pipex[2];
// 	int		status;
// 	pid_t	pid1;
// 	pid_t	pid2;

// 	if (pipe(pipex) < 0)
// 		exit(EXIT_FAILURE);
// 	pid1 = fork();
// 	if (pid1 < 0)
// 		exit(EXIT_FAILURE);
// 	if (pid1 == 0)
// 		first_child_process(left_node, shell, pipex);
// 	pid2 = fork();
// 	if (pid2 < 0)
// 		exit(EXIT_FAILURE);
// 	if (pid2 == 0)
// 		second_child_process(right_node, shell, pipex);
// 	close(pipex[0]);
// 	close(pipex[1]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, &status, 0);
// 	free_ast_node(left_node);
// 	free_ast_node(right_node);
// 	return (get_return_value(&status));
// }


void	new_process(t_ast_node *node, t_shell *shell)
{
	char	**temp_env_array;

	temp_env_array = NULL;
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

// static void	second_child_process(t_ast_node *node, t_shell *shell, int *pipex)
// {
// 	if (node->node_type == COMMAND_SIMPLE)
// 	{
// 		pipe_redir_cmd(node);
// 		redir_std(&node);
// 	}
// 	else
// 	{
// 		// if (dup2(node->outfile_fd, STDIN_FILENO) == -1)
// 		// 	exit(EXIT_FAILURE);
// 		if (dup2(pipex[1], STDOUT_FILENO) == -1)
// 			exit(EXIT_FAILURE);
// 	}
// 	if (node->infile_fd < 0)
// 	{
// 		if (dup2(pipex[0], STDIN_FILENO) == -1)
// 			exit(EXIT_FAILURE);
// 	}
// 	close(pipex[0]);
// 	close(pipex[1]);
// 	new_process(node, shell);
// }

// static void	first_child_process(t_ast_node *node, t_shell *shell, int *pipex)
// {
// 	if (node->node_type == COMMAND_SIMPLE)
// 	{
// 		pipe_redir_cmd(node);
// 		redir_std(&node);
// 	}
// 	else
// 	{
// 		if(node->node_type == COMMAND_PIPE)
// 			shell->status = execute_pipe(node, node->left, node->right, shell);
// 	}
// 	if (node->outfile_fd == -1)
// 	{
// 		if (dup2(pipex[1], STDOUT_FILENO) == -1)
// 			exit(EXIT_FAILURE);
// 	}
// 	close(pipex[0]);
// 	close(pipex[1]);
// 	new_process(node, shell);
// }

// int	execute_pipe(t_ast_node *current, t_ast_node *left, t_ast_node *right, t_shell *shell)
// {
// 	int		pipex[2];
// 	int		status;
// 	pid_t	pid1;
// 	pid_t	pid2;

// 	(void)current;
// 	if (pipe(pipex) < 0)
// 		exit(EXIT_FAILURE);
// 	pid1 = fork();
// 	if (pid1 < 0)
// 		exit(EXIT_FAILURE);
// 	if (pid1 == 0)
// 		first_child_process(left, shell, pipex);
// 	pid2 = fork();
// 	if (pid2 < 0)
// 		exit(EXIT_FAILURE);
// 	if (pid2 == 0)
// 		second_child_process(right, shell, pipex);
// 	close(pipex[0]);
// 	close(pipex[1]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, &status, 0);
// 	free_ast_node(left);
// 	free_ast_node(right);
// 	return (get_return_value(&status));
// }


int execute_pipeline(t_ast_node *node, t_shell *shell, int input_fd)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (!node)
		return (node->status);
	if (node->node_type == COMMAND_PIPE)
	{
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
		return (execute_pipeline(node->right, shell, pipe_fd[0]));
	}
	else
	{
		pipe_redir_cmd(node);
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
}
