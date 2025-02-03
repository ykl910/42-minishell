/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:28:03 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/29 13:40:21 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	create_head(t_lst **head, char **cmd, char *path)
{
	*head = malloc(sizeof(t_lst));
	if (!*head)
		return (false);
	(*head)->name = cmd;
	(*head)->path = path;
	(*head)->index = 0;
	(*head)->next = NULL;
	return (true);
}

static bool	add_new_node(t_lst **node, char **cmd, char *path)
{
	t_lst	*temp;
	t_lst	*new_node;

	if (!*node)
		return (false);
	temp = *node;
	new_node = malloc(sizeof(t_lst));
	if (!new_node)
		return (false);
	new_node->name = cmd;
	new_node->path = path;
	new_node->index = 0;
	new_node->next = NULL;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	return (true);
}

bool	put_cmd_lst(t_lst **cmd_lst, char **cmd, char *path)
{
	if (!cmd_lst)
		return (false);
	if (!*cmd_lst)
	{
		if (!create_head(cmd_lst, cmd, path))
			return (false);
	}
	else
	{
		if (!add_new_node(cmd_lst, cmd, path))
			return (false);
	}
	return (true);
}
