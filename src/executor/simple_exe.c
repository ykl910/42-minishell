/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:43:02 by kyang             #+#    #+#             */
/*   Updated: 2025/03/04 14:23:49 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	simple_process(t_ast_node *node, t_shell *shell)
{
	char	**temp_env_array;

	temp_env_array = NULL;
	simple_parse_path(node, shell);
	shell->status = node->status;
	if (!node->cmd_abs_path)
		free_exit(&node->status, shell);
	shell->status = node->status;
	temp_env_array = env_lst_to_array(shell->shell_env);
	execve(node->cmd_abs_path, node->cmd, temp_env_array);
	free_exit(&node->status, shell);
}

static void	child_process(t_ast_node *node, t_shell *shell)
{
	if (node->redir_in && node->infile_fd == -1)
	{
		node->status = 1;
		free_exit(&node->status, shell);
	}
	else if (node->redir_out && node->outfile_fd == -1)
	{
		node->status = 1;
		free_exit(&node->status, shell);
	}
	else
		simple_process(node, shell);
}

static void	parent_process(t_ast_node *node)
{
	if (node->infile_fd != -1)
		close(node->infile_fd);
	if (node->outfile_fd != -1)
		close(node->outfile_fd);
}

int	execute_command(t_ast_node *node, t_shell *shell)
{
	pid_t		pid;
	t_ast_node	*current;
	int			status;

	current = node;
	if (current && current->left && current->node_type == COMMAND_SUBSHELL)
		current = current->left;
	parse_simple_cmd(current, shell);
	simple_std_dup(&node, shell);
	if (built_in_exec(shell, current->cmd) == 0)
		return (shell->status);
	pid = fork();
	if (pid == 0)
		child_process(current, shell);
	else
		parent_process(current);
	waitpid(pid, &status, 0);
	return (get_return_value(&status));
}
