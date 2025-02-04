/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:58:50 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/29 13:31:28 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	create_node(t_data *data, char **paths, char *arg)
{
	if (is_absolute_path(arg))
	{
		if (!create_node_abs(data, arg))
			return (error(MEM, "create_node_abs"), false);
	}
	else
	{
		if (!create_node_rel(data, paths, arg))
			return (error(MEM, "create_node_rel"), false);
	}
	return (true);
}

static bool	browse_args(t_data *data, char **paths, int ac, char **av)
{
	int	i;

	i = 2;
	if (data->is_here_doc)
		i++;
	while (i < (ac - 1))
	{
		if (!create_node(data, paths, av[i]))
			return (false);
		i++;
	}
	return (true);
}

static char	**get_paths(char **envp)
{
	int		i;
	char	*temp;
	char	**paths;

	i = 0;
	if (!*envp || !envp)
		return (NULL);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	temp = ft_strdup(envp[i] + 5);
	if (!temp)
		return (NULL);
	paths = ft_split(temp, ':');
	free(temp);
	if (!paths)
		return (NULL);
	if (!add_subpath(paths))
		return (ft_free_tab((void **)paths), NULL);
	return (paths);
}

bool	create_cmd_lst(t_data *data, int ac, char **av, char **env)
{
	char	**paths;

	paths = get_paths(env);
	if (!browse_args(data, paths, ac, av))
		return (error(MEM, "create_node"), data->return_value = 1, false);
	put_index(&data->cmd_lst);
	data->cmd_lst_size = get_cmd_size(&data->cmd_lst);
	if (data->cmd_lst_size == 0)
		return (ft_free_tab((void **)paths), false);
	return (ft_free_tab((void **)paths), true);
}
