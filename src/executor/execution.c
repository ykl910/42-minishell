/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:03:36 by kyang             #+#    #+#             */
/*   Updated: 2025/02/11 18:59:44 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// int	execute(t_ast_node node)
// {
// 	if (node.node_type == COMMAND_PIPE)
// 		return (execute_pipe(node.left, node.right));
// 	else
// 		return (execute_simple_command(node.value));
// }

void inorder_traversal(t_ast_node *node)
{
    if (node == NULL)
        return;

    inorder_traversal(node->left);
    printf("%u ", node->node_type); 
    inorder_traversal(node->right);
}
