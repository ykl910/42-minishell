/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:55:37 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/23 16:59:14 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	put_index(t_lst **head)
{
	int		i;
	t_lst	*current;

	if (!*head)
		return ;
	i = 0;
	current = *head;
	while (current)
	{
		current->index = i;
		current = current->next;
		i++;
	}
}

int	get_cmd_size(t_lst **head)
{
	int		i;
	t_lst	*current;

	if (!*head)
		return (0);
	current = *head;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}
