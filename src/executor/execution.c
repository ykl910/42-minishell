/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:03:36 by kyang             #+#    #+#             */
/*   Updated: 2025/02/12 15:56:05 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executer(t_ast_node *node, t_shell *shell)
{
	if (node->node_type == COMMAND_SIMPLE)
		execute_commad(node, shell);
	else if (node->node_type == COMMAND_PIPE)
		execute_pipe(node->left, node->right, shell);
	else if (node->node_type == COMMAND_AND)
	{
		execute_and(node->left, node->right, shell);
		if (shell->status == 0)
			executer(node->right, shell);
	}
	else if (node->node_type == COMMAND_OR)
	{
		execute_or(node->left, node->right, shell);
		if (shell->status != 0)
			executer(node->right, shell);
	}
	else if (node->node_type == COMMAND_SUBSHELL)
		excute_subshell(node, shell);
}

void	inorder_traversal(t_ast_node *node, t_shell *shell)
{
	if (!node)
		return ;
	inorder_traversal(node->left, shell);
	executer(node, shell);
	inorder_traversal(node->right, shell);
}

void	execute_simple_cmd(t_shell *shell, t_token *token_lst)
{
}
