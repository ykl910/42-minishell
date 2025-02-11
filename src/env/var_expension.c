/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:58:12 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/11 15:30:19 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (ft_itoa(shell->status));
	while (current)
	{
		if (!ft_strncmp(current->name, variable, ft_strlen(current->name)))
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}
