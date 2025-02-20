/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:03:36 by kyang             #+#    #+#             */
/*   Updated: 2025/02/20 11:12:40 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	execute(t_ast_node *node, t_shell *shell)
// {
// 	if (node->node_type == COMMAND_SIMPLE)
// 		ft_printf("execute cmd: %s\n", node->value[0]); //execute_commad(node, shell);
// 	else if (node->node_type == COMMAND_PIPE)
// 		ft_printf("%s | %s\n", node->left->value[0], node->right->value[0]); //execute_pipe(node->left, node->right, shell);
// 	else if (node->node_type == COMMAND_AND)
// 	{
// 		ft_printf("&&: l->cmd_type: %d\n", node->left->node_type); //execute(node->left, shell);
// 		if (shell->status == 0)
// 			ft_printf("&&: r->cmd_type %d\n", node->right->node_type); //executer(node->right, shell);
// 	}
// 	else if (node->node_type == COMMAND_OR)
// 	{
// 		ft_printf("||: l->cmd_type: %d\n", node->left->node_type); //execute(node->left, shell);
// 		if (shell->status == 0)
// 			ft_printf("||: r->cmd: %d\n", node->right->node_type); //executer(node->right, shell);
// 	}
// 	else if (node->node_type == COMMAND_SUBSHELL)
// 		ft_printf("SUBSHELL\n"); //excute_subshell(node, shell);
// }

// void	execute(t_ast_node *node, t_shell *shell)
// {
// 	if (node->node_type == COMMAND_PIPE)
// 		node->status = execute_pipe(node, node->left, node->right, shell);
// 	else if (node->node_type == COMMAND_AND)
// 	{
// 		node->status = execute_command(node->left, shell);
// 		if (shell->status == 0)
// 			node->status = execute_command(node->right, shell);
// 	}
// 	else if (node->node_type == COMMAND_OR)
// 	{
// 		node->status = execute_command(node->left, shell);
// 		if (shell->status != 0)
// 			node->status = execute_command(node->right, shell);
// 	}
// 	else if (node->node_type == COMMAND_SUBSHELL)
// 		ft_printf("SUBSHELL\n"); //excute_subshell(node, shell);
// }

// void	inorder_traversal(t_ast_node *node, t_shell *shell)
// {
// 	if (!node)
// 		return ;
// 	if (shell->prompt_type == 1)
// 	{
// 		shell->status = execute_command(node, shell);
// 		return ;
// 	}
// 	if (node->node_type == COMMAND_SUBSHELL)
// 		execute(node, shell);
// 	inorder_traversal(node->left, shell);
// 	if (node->node_type >= COMMAND_PIPE && node->node_type <= COMMAND_OR)
// 		execute(node, shell);
// 	inorder_traversal(node->right, shell);
// }

void	executor(t_ast_node *node, t_shell *shell)
{
	if(!node)
		return ;
	if(node->node_type == COMMAND_PIPE)
		shell->status = execute_pipe(node, node->left, node->right, shell, -1);
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
		return ;//shell->status = execute_subshell(node, shell);
	else
		shell->status = execute_command(node, shell);
}
