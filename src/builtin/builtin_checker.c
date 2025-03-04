/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:39:57 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/04 14:31:32 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in_exec(t_shell *shell, char **cmd)
{
	if (!cmd)
		return (-1);
	if (is_cmd(cmd[0], "cd"))
		return (builtin_cd(cmd, shell), 0);
	else if (is_cmd(cmd[0], "echo"))
		return (builtin_echo(cmd, shell), 0);
	else if (is_cmd(cmd[0], "pwd"))
		return (builtin_pwd(shell), 0);
	else if (is_cmd(cmd[0], "export"))
		return (builtin_export(cmd[1], shell), 0);
	else if (is_cmd(cmd[0], "unset"))
		return (builtin_unset(cmd[1], shell), 0);
	else if (is_cmd(cmd[0], "env"))
		return (builtin_env(shell), 0);
	else if (is_cmd(cmd[0], "exit"))
		return (builtin_exit(cmd, shell), 0);
	else
		return (-1);
}
