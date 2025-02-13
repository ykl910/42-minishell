/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:51:46 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/13 14:55:01 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_absolute_path(char *arg)
{
	if (arg[0] == '/')
		return (true);
	else if (!ft_strncmp(arg, "./", 2))
		return (true);
	return (false);
}

static void	new_process(t_ast_node *node, t_shell *shell)
{
	int i;

	i = 0;
	while(shell->paths[i])
	{
		node->cmd_abs_path = ft_strjoin(shell->paths[i], node->cmd[0]);
		if(access(node->cmd_abs_path, F_OK | X_OK) == 0)
			execve(node->cmd_abs_path, node->cmd, shell->shell_env);
		free(node->cmd_abs_path);
		i++;
	}
	ft_putstr_fd("ERROR: Command not found", STDERR_FILENO);
}

static void	pipe_redir_operator(t_ast_node *node, int *pipex)
{
	if(dup2(node->outfile_fd, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if(dup2(pipex[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
}

static void	pipe_redir_cmd(t_ast_node *node, int *pipex)
{
	int	i;
	int j;
	int	arg_size;
	char **arg;

	i = 0;
	j = 0;
	arg_size = 0;
	arg = NULL;
	while(node->value[i])
	{
		arg_size = ft_strlen(node->value[i]);
		if(!ft_strncmp(node->value[i], "<", arg_size) && node->value[i + 1])
		{
			if(node->infile_fd > -1)
				close(node->infile_fd);
			node->infile_fd = open(node->value[i + 1], O_RDONLY, 0644);
			if(node->infile_fd < 0)
			{
				ft_putstr_fd("Error: Permisson denied", STDERR_FILENO);
				node->infile_fd = open("/dev/null", O_RDONLY);
			}
			i += 2;
		}
		else if(!ft_strncmp(node->value[i], ">", arg_size) && node->value[i + 1])
		{
			if(node->outfile_fd > -1)
				close(node->outfile_fd);
			node->outfile_fd = open(node->value[i + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
			if(node->infile_fd < 0)
			{
				ft_putstr_fd("Error: Permisson denied", STDERR_FILENO);
				node->outfile_fd = open("/dev/null", O_WRONLY);
			}
			i += 2;
		}
		else if(!ft_strncmp(node->value[i], ">>", arg_size) && node->value[i + 1])
		{
			if(node->outfile_fd > -1)
				close(node->outfile_fd);
			node->outfile_fd = open(node->value[i + 1], O_RDWR | O_APPEND | O_CREAT, 0644);
			if(node->infile_fd < 0)
			{
				ft_putstr_fd("Error: Permisson denied", STDERR_FILENO);
				node->outfile_fd = open("/dev/null", O_WRONLY);
			}
			i += 2;
		}
		else if(!ft_strncmp(node->value[i], "<<", arg_size))
		{
			if(node->infile_fd > -1)
				close(node->infile_fd);
			node->infile_fd = open("here_doc.txt", O_RDONLY, 0644);
			if(node->infile_fd < 0)
			{
				ft_putstr_fd("Error: Permisson denied", STDERR_FILENO);
				node->infile_fd = open("/dev/null", O_RDONLY);
			}
			i += 2;
		}
		else
		{
			while(node->value[j] && ft_strncmp(node->value[j], ">", ft_strlen(node->value[j]))
			&& ft_strncmp(node->value[j], ">>", ft_strlen(node->value[j]))
				&& ft_strncmp(node->value[j], "<", ft_strlen(node->value[j]))
				&& ft_strncmp(node->value[j], "<<", ft_strlen(node->value[j])))
			{
				j++;
				i++;
			}
			node->cmd = ft_calloc(j + 1, sizeof(char *));
			if(!node->cmd)
				return(NULL);
			while(j > 0)
			{
				node->cmd[j] = ft_strdup(node->value[j - 1]);
				j--;
			}
		}
	}
}

static void	parent_process(t_ast_node *node, t_shell *shell, int *pipex)
{
	if(node->node_type == COMMAND_SIMPLE)
		pipe_redir_cmd(node, pipex);
	else
		pipe_redir_operator(node, pipex);
	if(node->infile_fd < 0)
	{
		if(dup2(pipex[0], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	close(pipex[0]);
	close(pipex[1]);
	new_process(node, shell);
}

static void	child_process(t_ast_node *node, t_shell *shell, int *pipex)
{
	if(node->node_type == COMMAND_SIMPLE)
		pipe_redir_cmd(node, pipex);
	else
		pipe_redir_operator(node, pipex);
	if(node->outfile_fd < 0)
	{
		if(dup2(pipex[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	close(pipex[0]);
	close(pipex[1]);
	new_process(node, shell);
}

void	execute_pipe(t_ast_node *left_node, t_ast_node *right_node, t_shell *shell)
{
	int		pipex[2];
	pid_t	pid;

	if (pipe(pipex) < 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
		child_process(left_node, shell, pipex);
	else
		parent_process(right_node, shell, pipex);
	waitpid(pid, NULL, 0);
}
