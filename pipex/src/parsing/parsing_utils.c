/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:58:37 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/29 20:24:41 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*str_fusion(char *buffer, char *line)
{
	char	*temp;

	temp = ft_strjoin(buffer, line);
	if (!temp)
		return (free(buffer), NULL);
	free(buffer);
	return (temp);
}

bool	is_absolute_path(char *arg)
{
	if (arg[0] == '/')
		return (true);
	else if (!ft_strncmp(arg, "./", 2))
		return (true);
	return (false);
}

bool	add_subpath(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		path[i] = str_fusion(path[i], "/\0");
		if (!path[i])
			return (false);
		i++;
	}
	return (true);
}

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (i);
	while (tab[i])
		i++;
	return (i);
}

bool	only_spaces(char *tab)
{
	int	i;

	i = 0;
	if (!tab || !*tab)
		return (false);
	while (tab[i])
	{
		if (tab[i] > 32)
			return (false);
		i++;
	}
	return (true);
}
