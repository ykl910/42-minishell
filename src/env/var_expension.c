/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:58:12 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/04 12:05:33 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_env_var(char *current, char *arg)
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

static int	check_var(char *variable)
{
	if (!variable || !*variable)
		return (-1);
	if (ft_strlen(variable) < 2)
		return (-1);
	if (variable[0] != '$')
		return (-1);
	return (0);
}

char	*variable_expension(char *variable, t_shell *shell)
{
	t_env	*current;
	char	*expended;

	expended = NULL;
	if (check_var(variable) == -1)
		return (NULL);
	variable++;
	current = shell->shell_env;
	if (!ft_strncmp(variable, "?", ft_strlen(variable)))
		return (ft_itoa(shell->prev_status));
	if (!ft_strncmp(variable, "UID", ft_strlen(variable)))
		return (getenv("UID"));
	while (current)
	{
		if (is_env_var(current->name, variable))
		{
			expended = ft_strdup(current->value);
			if (!expended)
				return (error_msg(MEM, "variable_expension"), NULL);
			return (expended);
		}
		current = current->next;
	}
	return (NULL);
}
