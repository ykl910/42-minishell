/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:25:37 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/29 12:26:46 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_path(char *cmd)
{
	if (access(cmd, F_OK) != 0)
		error(CMD_ABS, cmd);
	if (access(cmd, X_OK) != 0)
		error(PERM, cmd);
}

static char	*get_path_abs(char *arg)
{
	char	**temp;
	char	*path;

	temp = ft_split(arg, ' ');
	if (!temp)
		return (NULL);
	path = ft_strdup(temp[0]);
	ft_free_tab((void **)temp);
	if (!path)
		return (NULL);
	return (path);
}

static char	**get_cmd_name(char *arg)
{
	char	**temp;
	char	**cmd;
	int		temp_size;

	temp_size = 0;
	temp = ft_split(arg, '/');
	if (!temp)
		return (NULL);
	temp_size = tab_size(temp);
	cmd = ft_split(temp[temp_size - 1], ' ');
	if (!cmd)
		return (ft_free_tab((void **)temp), NULL);
	return (ft_free_tab((void **)temp), cmd);
}

bool	create_node_abs(t_data *data, char *arg)
{
	char	**cmd;
	char	*path;

	cmd = get_cmd_name(arg);
	if (!cmd)
		return (false);
	path = get_path_abs(arg);
	if (!path)
		return (free(cmd), false);
	check_path(path);
	if (!put_cmd_lst(&data->cmd_lst, cmd, path))
		return (false);
	return (true);
}
