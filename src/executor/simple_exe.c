/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:43:02 by kyang             #+#    #+#             */
/*   Updated: 2025/02/18 18:43:48 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_process(t_ast_node *node, t_shell *shell)
{
	char	**temp_env_array;

	temp_env_array = NULL;
	if (node->status == 0)
	{
		if (built_in_exec(shell, node) == -1)
		{
			parse_path(node, shell);
			shell->status = node->status;
			temp_env_array = env_lst_to_array(shell->shell_env);
			execve(node->cmd_abs_path, node->cmd, temp_env_array);
		}
	}
	ft_free_tab((void **)temp_env_array);
	free(node->cmd_abs_path);
}

int	execute_command(t_ast_node *node, t_shell *shell)
{
	pid_t		pid;
	t_ast_node	*current;

	current = node;
	if (current && current->left && current->node_type == COMMAND_SUBSHELL)
		current = current->left;
	pipe_redir_cmd(current);
	pid = fork();
	if (pid == 0)
	{
		redir_std(&current);
		simple_process(current, shell);
	}
	else
	{
		waitpid(pid, NULL, 0);
		if (current->infile_fd != -1)
			close(current->infile_fd);
		if (current->outfile_fd != -1)
			close(current->outfile_fd);
	}
	free_ast_node(node);
	return (shell->status);
}
