/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:03:36 by kyang             #+#    #+#             */
/*   Updated: 2025/02/21 14:36:29 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_ast_node *node, t_shell *shell)
{
	if(!node)
		return ;
	if(node->node_type == COMMAND_PIPE)
		shell->status = execute_pipeline(node, shell, STDIN_FILENO);
	else if(node->node_type == COMMAND_AND)
	{
		executor(node->left, shell);
		if(shell->status == 0)
			executor(node->right, shell);
	}
	else if(node->node_type == COMMAND_OR)
	{
		executor(node->left, shell);
		if(shell->status != 0)
			executor(node->right, shell);
	}
	else if(node->node_type == COMMAND_SUBSHELL)
		executor(node->left, shell);
	else
		shell->status = execute_command(node, shell);
}
