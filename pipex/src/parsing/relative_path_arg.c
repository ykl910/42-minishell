/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative_path_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:28:08 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/29 13:33:53 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path(t_data *data, char **paths, char **cmd)
{
	int		i;
	char	*cmd_path;

	i = 0;
	if (!cmd || !cmd[0])
		return (data->return_value = 127, error(CMD, "(empty)"), NULL);
	while (paths && paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd[0]);
		if (!cmd_path)
			return (ft_free_tab((void **)cmd), error(MEM, "get_path"), NULL);
		if (access(cmd_path, F_OK) == 0)
		{
			if (access(cmd_path, X_OK) == 0)
				return (cmd_path);
			else
				return (free(cmd_path), data->return_value = 126, error(PERM,
						cmd[0]), NULL);
		}
		free(cmd_path);
		i++;
	}
	return (data->return_value = 127, error(CMD, cmd[0]), NULL);
}

bool	create_node_rel(t_data *data, char **paths, char *arg)
{
	char	**cmd;
	char	*path;

	path = NULL;
	cmd = NULL;
	if (*arg && !only_spaces(arg))
	{
		cmd = ft_split(arg, ' ');
		if (!cmd)
			return (false);
		if (!*cmd)
			return (free(cmd), false);
	}
	else
	{
		cmd = ft_calloc(1, sizeof(char *));
		if (!cmd)
			return (false);
	}
	path = get_path(data, paths, cmd);
	if (!put_cmd_lst(&data->cmd_lst, cmd, path))
		return (ft_free_tab((void **)cmd), free(path), false);
	return (true);
}
