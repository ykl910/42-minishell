/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:10:51 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/21 15:05:45 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_abs_path(t_ast_node *node)
{
	if (!ft_strncmp(node->cmd[0], "/", 1) || !ft_strncmp(node->cmd[0], "./", 2))
		return (true);
	return (false);
}

static void	handle_cmd_error(t_ast_node *node, int err_code)
{
	node->status = err_code;
	node->cmd_abs_path = NULL;
	ft_putstr_fd("ERROR: Command not found\n", STDERR_FILENO);
}

static int	try_access(t_ast_node *node, char **cmd)
{
	if (access(node->cmd_abs_path, F_OK) == 0)
	{
		if (access(node->cmd_abs_path, X_OK) == 0)
		{
			node->status = 0;
			ft_free_tab((void **)cmd);
			return (1);
		}
		node->status = 126;
		ft_free_tab((void **)cmd);
		ft_putstr_fd("ERROR: Permission denied\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

static void	check_relative_cmd(t_ast_node *node, t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->paths[i])
	{
		node->cmd_abs_path = ft_strjoin(shell->paths[i], node->cmd[0]);
		if (try_access(node, node->cmd))
			return ;
		free(node->cmd_abs_path);
		i++;
	}
	handle_cmd_error(node, 127);
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
			ft_putstr_fd("ERROR: Permission denied\n", STDERR_FILENO);
			return ;
		}
	}
	node->status = 127;
	ft_putstr_fd("ERROR: Command not found\n", STDERR_FILENO);
}

void	parse_path(t_ast_node *node, t_shell *shell)
{
	if (!node->cmd)
		return ;
	if (is_abs_path(node))
	{
		node->cmd_abs_path = ft_strdup(node->cmd[0]);
		if (!node->cmd_abs_path)
			return (ft_putendl_fd("malloc error create abs path",
					STDERR_FILENO));
		check_abs_cmd(node);
	}
	else
		check_relative_cmd(node, shell);
}

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	if (!*tab || !tab)
		return (i);
	while (tab[i])
		i++;
	return (i);
}

int	create_cmd(char ***cmd, char *arg)
{
	int		cmd_size;
	char	**temp;

	temp = NULL;
	if (!cmd || !*cmd)
		cmd_size = 0;
	else
		cmd_size = tab_size(*cmd);
	if (cmd_size == 0)
	{
		*cmd = ft_calloc(2, sizeof(char *));
		if (!*cmd)
			return (ft_putendl_fd("malloc error create cmd", STDERR_FILENO),
				-1);
		*cmd[0] = ft_strdup(arg);
		if (!(*cmd)[0])
			return (ft_putendl_fd("dup error create cmd", STDERR_FILENO), -1);
		return (0);
	}
	temp = append_args(*cmd, arg);
	if (!temp)
		return (-1);
	*cmd = temp;
	return (0);
}
