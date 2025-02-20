/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:51:46 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/20 11:17:14 by kyang            ###   ########.fr       */
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

static void	second_child_process(t_ast_node *node, t_shell *shell, int *pipex)
{
	if (node->node_type == COMMAND_SIMPLE)
	{
		pipe_redir_cmd(node);
		redir_std(&node);
	}
	else
	{
		// if (dup2(node->outfile_fd, STDIN_FILENO) == -1)
		// 	exit(EXIT_FAILURE);
		if (dup2(pipex[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	if (node->infile_fd < 0)
	{
		if (dup2(pipex[0], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	close(pipex[0]);
	close(pipex[1]);
	new_process(node, shell);
}

static void	first_child_process(t_ast_node *node, t_shell *shell, int *pipex, int prev_fd)
{
	pipe_redir_cmd(node);
	redir_std(&node);
	if(node->infile_fd == -1)
	{
		if(prev_fd != -1)
		{
			if(dup2(prev_fd, STDIN_FILENO) == -1)
				exit(EXIT_FAILURE);
			close(prev_fd);
		}
	}
	if (node->outfile_fd == -1)
	{
		if (dup2(pipex[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	close(pipex[0]);
	close(pipex[1]);
	new_process(node, shell);
}

int	execute_pipe(t_ast_node *current, t_ast_node *left, t_ast_node *right, t_shell *shell, int prev_fd)
{
	(void) prev_pipe_in;
	int		pipex[2];
	int		status;
	pid_t	pid1;
	//pid_t	pid2;

	(void)current;
	if (pipe(pipex) < 0)
		exit(EXIT_FAILURE);
	if(left->node_type == COMMAND_PIPE)
		status = execute_pipe(left, left->left, left->right, shell, prev_fd);
	pid1 = fork();
	if (pid1 < 0)
		exit(EXIT_FAILURE);
	if (pid1 == 0)
		first_child_process(left, shell, pipex, prev_fd);
	pid2 = fork();
	if (pid2 < 0)
		exit(EXIT_FAILURE);
	if (pid2 == 0)
		second_child_process(right, shell, pipex);
	close(pipex[0]);
	close(pipex[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	free_ast_node(left);
	free_ast_node(right);
	return (get_return_value(&status));
}


// int execute_pipe(t_ast_node *pipe_node, t_ast_node *left_node,
// 	t_ast_node *right_node, t_shell *shell, int prev_pipe_in)
// {
// 	int pipex[2];
// 	int status;
// 	pid_t pid1, pid2;

// 	printf("my infile :%d", prev_pipe_in);
// 	if (pipe(pipex) < 0)
// 		exit(EXIT_FAILURE);
// 	pid1 = fork();
// 	if (pid1 < 0)
// 		exit(EXIT_FAILURE);
// 	if (pid1 == 0)
// 	{
// 		pipe_redir_cmd(left_node);
//  		redir_std(&left_node);
// 		if (prev_pipe_in != -1)
// 		{
// 			dup2(prev_pipe_in, STDIN_FILENO);
// 			close(prev_pipe_in);
// 		}
// 		dup2(pipex[1], STDOUT_FILENO);
// 		close(pipex[1]);
// 		close(pipex[0]);
// 		new_process(left_node, shell);
// 	}
// 	pid2 = fork();
// 	if (pid2 < 0)
// 		exit(EXIT_FAILURE);
// 	if (pid2 == 0)
// 	{
// 		pipe_redir_cmd(right_node);
// 		redir_std(&right_node);
// 		dup2(pipex[0], STDIN_FILENO);
// 		close(pipex[0]);
// 		close(pipex[1]);
// 		if (right_node->node_type == COMMAND_PIPE)
// 		{
// 			int new_pipe_in = execute_pipe(pipe_node, right_node->left, right_node->right, shell, pipex[0]);
// 			close(new_pipe_in);
// 		}
// 		else
// 		{
// 			new_process(right_node, shell);
// 		}
// 	}
// 	close(pipex[0]);
// 	close(pipex[1]);
// 	if (prev_pipe_in != -1)
// 		close(prev_pipe_in);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, &status, 0);
// 	return status;
// }

