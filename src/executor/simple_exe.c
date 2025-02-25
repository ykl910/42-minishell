/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:43:02 by kyang             #+#    #+#             */
/*   Updated: 2025/02/25 10:06:04 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_process(t_ast_node *node, t_shell *shell)
{
	char	**temp_env_array;

	temp_env_array = NULL;
	parse_path(node, shell);
	shell->status = node->status;
	if (!node->cmd_abs_path)
		exit(node->status);
	shell->status = node->status;
	temp_env_array = env_lst_to_array(shell->shell_env);
	execve(node->cmd_abs_path, node->cmd, temp_env_array);
	exit(node->status);
}

void	child_process(t_ast_node *node, t_shell *shell)
{
	if (node->redir_in && node->infile_fd == -1)
		exit(1);
	else if (node->redir_out && node->outfile_fd == -1)
		exit(1);
	else
		simple_process(node, shell);
}

void	parent_process(t_ast_node *node)
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
	cmd_builder(current);
	redir_std(&node);
	if (built_in_exec(shell, current) == 0)
		return (shell->status);
	//process_signals();
	pid = fork();
	if (pid == 0)
		child_process(current, shell);
	else
		parent_process(current);
	waitpid(pid, &status, 0);
	return (get_return_value(&status));
}
