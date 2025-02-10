/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:32:07 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/10 16:39:35 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_wc_struct(t_wildcards **head)
{
	t_wildcards	*current;
	t_wildcards	*next;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		if (current->file)
			free(current->file);
		free(current);
		current = next;
	}
	*head = NULL;
}

int	create_head_wc(t_wildcards **head, char *file, int index)
{
	*head = malloc(sizeof(t_wildcards));
	if (!*head)
		return (-1);
	(*head)->file = file;
	(*head)->index = index;
	(*head)->next = NULL;
	return (0);
}

int	create_node_wc(t_wildcards **head, char *file, int index)
{
	t_wildcards	*current;
	t_wildcards	*new;

	current = *head;
	while (current->next)
		current = current->next;
	new = malloc(sizeof(t_wildcards));
	if (!new)
		return (-1);
	new->file = file;
	new->index = index;
	new->next = NULL;
	current->next = new;
	return (0);
}

int	wc_struct(t_wildcards **node, char *file, int index)
{
	int	status;

	status = 0;
	if (!file)
		return (-1);
	if (!*node)
		status = create_head_wc(node, file, index);
	else
		status = create_node_wc(node, file, index);
	return (status);
}

int	occurence_count(char *str, char occurence)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == occurence)
			count++;
		i++;
	}
	return (count);
}
