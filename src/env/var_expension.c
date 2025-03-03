/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:58:12 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/03 16:21:25 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_env_var(char *current, char *arg)
{
	if (ft_strlen(current) != ft_strlen(arg))
		return (false);
	else
	{
		if (!ft_strncmp(current, arg, ft_strlen(current)))
			return (true);
		return (false);
	}
}

char	*variable_expension(char *variable, t_shell *shell)
{
	t_env	*current;

	if (!variable || !*variable)
		return (NULL);
	if (ft_strlen(variable) < 2)
		return (NULL);
	if (variable[0] != '$')
		return (NULL);
	variable++;
	current = shell->shell_env;
	if (!ft_strncmp(variable, "?", ft_strlen(variable)))
		return (ft_itoa(shell->prev_status));
	while (current)
	{
		if (is_env_var(current->name, variable))
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}
