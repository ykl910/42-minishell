/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:19:59 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/04 15:44:55 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env_node(t_env *node)
{
	free(node->key_val);
	free(node->name);
	free(node->value);
	free(node);
}

static void	remove_first_env_node(t_shell *shell, t_env *current)
{
	shell->shell_env = current->next;
	free_env_node(current);
}

static void	remove_env_node(t_env *prev, t_env *current)
{
	prev->next = current->next;
	free_env_node(current);
}

static void	handle_unset_path(t_shell *shell, char *target)
{
	if (is_path(target))
	{
		ft_free_tab((void **)shell->paths);
		shell->paths = NULL;
	}
}

void	builtin_unset(char *target, t_shell *shell)
{
	int		target_size;
	t_env	*current;
	t_env	*prev;

	shell->status = 0;
	if (!shell->shell_env || !target)
		return ;
	target_size = ft_strlen(target);
	current = shell->shell_env;
	prev = NULL;
	if (!ft_strncmp(target, current->name, target_size))
		return (remove_first_env_node(shell, current));
	while (current && ft_strncmp(target, current->name, target_size))
	{
		prev = current;
		current = current->next;
	}
	if (current)
		remove_env_node(prev, current);
	handle_unset_path(shell, target);
}
