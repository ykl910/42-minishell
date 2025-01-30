/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:00:03 by kyang             #+#    #+#             */
/*   Updated: 2025/01/30 16:10:12 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char **paths, char *arg, char **split_arg)
{
	char	*temp;
	char	*full_path;
	int		j;

	if (!paths)
		return (NULL);
	j = 0;
	while (paths[j])
	{
		temp = ft_strjoin("/", arg);
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(paths[j], temp);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		j++;
	}
	free_splits(paths, split_arg, arg);
	perror("command not found");
	exit(EXIT_FAILURE);
	return (NULL);
}

char	*get_env(char *arg, char **split_arg)
{
	char	**paths;
	char	*result;
	int		i;

	i = 0;
	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		return (NULL);
	result = get_path(paths, arg, split_arg);

	free_split(paths);
	return (result);
}

char	**exec_args_list(char **args, char *first, int i, int j)
{
	char	**res;

	if (!args)
	{
		res = malloc(sizeof(char *) * 2);
		if (!res)
			return (NULL);
		res[0] = first;
		res[1] = NULL;
		return (res);
	}
	while (args[i])
		i++;
	res = malloc(sizeof(char *) * (i + 2));
	if (!res)
		return (NULL);
	res[0] = first;
	while (args[j - 1])
	{
		res[j] = ft_strtrim(args[j - 1], " ");
		j++;
	}
	res[j] = NULL;
	free_split(args);
	return (res);
}

char	**exec_args(char *av)
{
	char	**args;
	char	**split_av;
	char	*first;
	int		i;
	int		j;

	i = 0;
	j = 1;
	split_av = ft_split(av, ' ');
	if (!split_av)
		return (NULL);
	first = get_env(split_av[0], split_av);
	free_split(split_av);
	if (!first)
		error();
	args = ft_split(av, ' ');
	return (exec_args_list(args, first, i, j));
}
