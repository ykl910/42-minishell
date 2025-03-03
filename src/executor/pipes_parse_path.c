/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   V2pipes_parse_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:10:51 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/03 12:54:37 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_abs_path(t_cmd *current)
{
	if (!ft_strncmp(current->cmd[0], "/", 1) || !ft_strncmp(current->cmd[0], "./", 2))
		return (true);
	return (false);
}

static int	try_access(t_cmd *current, char **cmd)
{
	if (access(current->abs_path, F_OK) == 0)
	{
		if (access(current->abs_path, X_OK) == 0)
		{
			current->status = 0;
			return (1);
		}
		current->status = 126;
		ft_free_tab((void **)cmd);
		error_msg(RED PERM RESET, cmd[0]);
		return (1);
	}
	return (0);
}

static void	check_relative_cmd(t_cmd *current, t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->paths)
	{
		p_handle_cmd_error(&current, 127);
		return ;
	}
	while (shell->paths[i])
	{
		current->abs_path = ft_strjoin(shell->paths[i], current->cmd[0]);
		if (!current->abs_path)
			return (error_msg(MEM, "check_relative_cmd"));
		if (try_access(current, current->cmd))
			return ;
		free(current->abs_path);
		i++;
	}
	p_handle_cmd_error(&current, 127);
}

static void	check_abs_cmd(t_cmd *current)
{
	if (access(current->abs_path, F_OK) == 0)
	{
		if (access(current->abs_path, X_OK) == 0)
		{
			current->status = 0;
			return ;
		}
		else
		{
			current->status = 126;
			error_msg(RED PERM RESET, current->cmd[0]);
			return ;
		}
	}
	current->status = 127;
	error_msg(RED CMD RESET, current->cmd[0]);
}

void	pipes_parse_path(t_cmd *current, t_shell *shell)
{
	if (!current->cmd)
		return ;
	if (is_abs_path(current))
	{
		current->abs_path = ft_strdup(current->cmd[0]);
		if (!current->abs_path)
			return (error_msg(MEM, "parse_path"));
		check_abs_cmd(current);
	}
	else
		check_relative_cmd(current, shell);
}
