/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   V2pipes_clist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:05:01 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/03 14:47:37 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_head_cmd(t_cmd **cmd_lst, t_ast_node *ast_node)
{
	*cmd_lst = malloc(sizeof(t_cmd));
	if (!*cmd_lst)
		return (error_msg(MEM, "create_head_cmd"), -1);
	(*cmd_lst)->abs_path = NULL;
	(*cmd_lst)->cmd = NULL;
	(*cmd_lst)->fd_in = -1;
	(*cmd_lst)->fd_out = -1;
	(*cmd_lst)->redir_in = false;
	(*cmd_lst)->redir_out = false;
	(*cmd_lst)->status = 0;
	(*cmd_lst)->next = NULL;
	return (parse_cmd(cmd_lst, ast_node));
}

static int	create_node_cmd(t_cmd **cmd_lst, t_ast_node *ast_node)
{
	t_cmd	*new;

	if (!*cmd_lst || !cmd_lst)
		return (error_msg(MEM, "create_node_cmd(1)"), -1);
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (error_msg(MEM, "create_node_cmd(2)"), -1);
	new->abs_path = NULL;
	new->cmd = NULL;
	new->fd_in = -1;
	new->fd_out = -1;
	new->redir_in = false;
	new->redir_out = false;
	new->status = 0;
	new->next = (*cmd_lst);
	(*cmd_lst) = new;
	return (parse_cmd(&new, ast_node));
}

static int	add_node(t_cmd **cmd_lst, t_ast_node *current)
{
	if (!*cmd_lst || !cmd_lst)
		return (create_head_cmd(cmd_lst, current));
	else
		return (create_node_cmd(cmd_lst, current));
}

t_cmd	*get_clist(t_ast_node *node)
{
	t_ast_node	*current;
	t_cmd		*cmd_lst;
	int			status;

	if (!node)
		return (NULL);
	current = node;
	cmd_lst = NULL;
	status = 0;
	while (current)
	{
		if (current->node_type == COMMAND_PIPE)
			status = add_node(&cmd_lst, current->right);
		else
			status = add_node(&cmd_lst, current);
		if (status == -1)
			return (free_clist(&cmd_lst), NULL);
		current = current->left;
	}
	return (cmd_lst);
}
