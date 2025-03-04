/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:29:39 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/04 15:57:06 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_newline_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (false);
	i = 1;
	while (str[++i])
	{
		if (str[i] != 'n')
			return (false);
	}
	return (true);
}

static int	skipe_newline_flags(char **cmd, bool *new_line)
{
	int	i;

	i = 1;
	*new_line = true;
	while (cmd[i] && is_newline_flag(cmd[i]))
	{
		*new_line = false;
		i++;
	}
	return (i);
}

static void	print_echo_args(char **cmd, int i)
{
	while (cmd[i])
	{
		ft_printf("%s", cmd[i]);
		if (cmd[i + 1])
			ft_printf(" ");
		i++;
	}
}

void	builtin_echo(char **cmd, t_shell *shell)
{
	int		i;
	bool	new_line;

	i = skipe_newline_flags(cmd, &new_line);
	print_echo_args(cmd, i);
	if (new_line)
		ft_printf("\n");
	shell->status = 0;
}
