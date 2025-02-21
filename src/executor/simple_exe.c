/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:43:02 by kyang             #+#    #+#             */
/*   Updated: 2025/02/21 12:37:15 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_process(t_ast_node *node, t_shell *shell)
{
	char	**temp_env_array;

	temp_env_array = NULL;
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
	exit(node->status);
}

int	execute_command(t_ast_node *node, t_shell *shell)
{
	pid_t		pid;
	t_ast_node	*current;
	int			status;

	current = node;
	if (current && current->left && current->node_type == COMMAND_SUBSHELL)
		current = current->left;
	cmd_builder(current);
	pid = fork();
	if (pid == 0)
	{
		redir_std(&current);
		simple_process(current, shell);
	}
	else
	{
		if (current->infile_fd != -1)
			close(current->infile_fd);
		if (current->outfile_fd != -1)
			close(current->outfile_fd);
	}
	waitpid(pid, &status, 0);
	free_ast_node(node);
	return (get_return_value(&status));
}
