/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:51:46 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/17 12:33:58 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_cmd(t_ast_node *node, t_shell *shell)
{
	int	i;

	i = 0;
	while(shell->paths[i])
	{
		node->cmd_abs_path = ft_strjoin(shell->paths[i], node->cmd[0]);
		if(access(node->cmd_abs_path, F_OK) == 0)
		{
			if(access(node->cmd_abs_path, X_OK) == 0)
				node->status = 0;
			else
			{
				node->status = 126;
				ft_putstr_fd("ERROR: Permission denied\n", STDERR_FILENO);
			}
		}
		free(node->cmd_abs_path);
		i++;
	}
	node->status = 127;
	ft_putstr_fd("ERROR: Command not found\n", STDERR_FILENO);
}

static void	new_process(t_ast_node *node, t_shell *shell)
{
	char **temp_env_array;

	temp_env_array = NULL;
	check_cmd(node, shell);
	shell->status = node->status;
	if(node->status == 0)
	{
		if(built_in_exec(shell, node) == -1)
		{
			temp_env_array = env_lst_to_array(shell->shell_env);
			execve(node->cmd_abs_path, node->cmd, temp_env_array);
		}
	}
	ft_free_tab((void **)temp_env_array);
	free(node->cmd_abs_path);
	exit(node->status);
}

static void	second_child_process(t_ast_node *node, t_shell *shell, int *pipex)
{
	if(node->node_type == COMMAND_SIMPLE)
		pipe_redir_cmd(node);
	else
	{
		if(dup2(node->outfile_fd, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		if(dup2(pipex[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	if(node->infile_fd < 0)
	{
		if(dup2(pipex[0], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	close(pipex[0]);
	close(pipex[1]);
	new_process(node, shell);
}

static void	first_child_process(t_ast_node *node, t_shell *shell, int *pipex)
{
	if(node->node_type == COMMAND_SIMPLE)
		pipe_redir_cmd(node);
	else
	{
		if(dup2(node->outfile_fd, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		if(dup2(pipex[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	if(node->outfile_fd < 0)
	{
		if(dup2(pipex[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	close(pipex[0]);
	close(pipex[1]);
	new_process(node, shell);
}

int	execute_pipe(t_ast_node *left_node, t_ast_node *right_node, t_shell *shell)
{
	int		pipex[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipex) < 0)
		exit(EXIT_FAILURE);
	pid1 = fork();
	if (pid1 < 0)
		exit(EXIT_FAILURE);
	if (pid1 == 0)
		first_child_process(left_node, shell, pipex);
	pid2 = fork();
	if(pid2 < 0)
		exit(EXIT_FAILURE);
	if(pid2 == 0)
		second_child_process(right_node, shell, pipex);
	close(pipex[0]);
	close(pipex[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return(right_node->status);
}
