/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_parse_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:36:35 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/03 15:25:36 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_abs_path(t_ast_node *node)
{
	if (!ft_strncmp(node->cmd[0], "/", 1) || !ft_strncmp(node->cmd[0], "./", 2))
		return (true);
	return (false);
}

static int	try_access(t_ast_node *node, char **cmd)
{
	if (access(node->cmd_abs_path, F_OK) == 0)
	{
		if (access(node->cmd_abs_path, X_OK) == 0)
		{
			node->status = 0;
			return (1);
		}
		node->status = 126;
		ft_free_tab((void **)cmd);
		error_msg(RED PERM RESET, cmd[0]);
		return (1);
	}
	return (0);
}

static void	check_relative_cmd(t_ast_node *node, t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->paths)
	{
		s_handle_cmd_error(&node, 127);
		return ;
	}
	while (shell->paths[i])
	{
		node->cmd_abs_path = ft_strjoin(shell->paths[i], node->cmd[0]);
		if (!node->cmd_abs_path)
			return (error_msg(MEM, "check_relative_cmd"));
		if (try_access(node, node->cmd))
			return ;
		free(node->cmd_abs_path);
		i++;
	}
	s_handle_cmd_error(&node, 127);
}

static void	check_abs_cmd(t_ast_node *node)
{
	if (access(node->cmd_abs_path, F_OK) == 0)
	{
		if (access(node->cmd_abs_path, X_OK) == 0)
		{
			node->status = 0;
			return ;
		}
		else
		{
			node->status = 126;
			error_msg(RED PERM RESET, node->cmd[0]);
			return ;
		}
	}
	node->status = 127;
	error_msg(RED CMD RESET, node->cmd[0]);
}

void	simple_parse_path(t_ast_node *node, t_shell *shell)
{
	if (!node->cmd)
		return ;
	if (is_abs_path(node))
	{
		node->cmd_abs_path = ft_strdup(node->cmd[0]);
		if (!node->cmd_abs_path)
			return (error_msg(MEM, "parse_path"));
		check_abs_cmd(node);
	}
	else
		check_relative_cmd(node, shell);
}
