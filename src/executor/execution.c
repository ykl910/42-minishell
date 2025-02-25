/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:03:36 by kyang             #+#    #+#             */
/*   Updated: 2025/02/25 13:28:46 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ast_traversal(t_ast_node *current, t_shell *shell)
{
	if (!current)
		return ;
	if (current->node_type == COMMAND_PIPE)
		shell->status = execute_pipeline(current, shell, STDIN_FILENO);
	else if (current->node_type == COMMAND_AND)
	{
		executor(current->left, shell);
		if (shell->status == 0)
			executor(current->right, shell);
	}
	else if (current->node_type == COMMAND_OR)
	{
		executor(current->left, shell);
		if (shell->status != 0)
			executor(current->right, shell);
	}
	else if (current->node_type == COMMAND_SUBSHELL)
		executor(current->left, shell);
	else
		shell->status = execute_command(current, shell);
}

void	reset_fds(t_shell *shell)
{
	dup2(shell->true_stdin, STDIN_FILENO);
	dup2(shell->true_stdout, STDOUT_FILENO);
}

void	executor(t_ast_node *head_node, t_shell *shell)
{
	t_ast_node	*current;

	if (!head_node)
		return ;
	current = head_node;
	ast_traversal(current, shell);
	reset_fds(shell);
	free_ast(head_node);
	head_node = NULL;
}
