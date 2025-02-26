/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:57:23 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/26 16:55:33 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_cmd(char *prompt, char *cmd)
{
	int	prompt_size;
	int	cmd_size;

	prompt_size = ft_strlen(prompt);
	cmd_size = ft_strlen(cmd);
	if (prompt_size != cmd_size)
		return (false);
	if (!ft_strncmp(prompt, cmd, prompt_size))
		return (true);
	return (false);
}

bool	is_numerical(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_unset_path(char *target)
{
	size_t	target_size;

	target_size = ft_strlen(target);
	if (target_size != 4)
		return (false);
	if (!ft_strncmp(target, "PATH", target_size))
		return (true);
	return (false);
}
