/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:44:09 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/10 16:44:45 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	match_prefix(char *file, char *pattern, int p_size)
{
	if (!ft_strncmp(file, pattern, p_size - 1))
		return (true);
	return (false);
}

bool	match_suffix(char *file, char *pattern, int f_size, int p_size)
{
	if (!ft_strncmp(&file[f_size - (p_size - 1)], &pattern[1], p_size - 1))
		return (true);
	return (false);
}

bool	match_subpatterns(char **sub_patterns, char *file, int f_size)
{
	int		i;
	char	*temp;

	i = 0;
	temp = file;
	while (sub_patterns[i])
	{
		temp = ft_strnstr(temp, sub_patterns[i], f_size);
		if (!temp)
			return (ft_free_tab((void **)sub_patterns), false);
		temp += ft_strlen(sub_patterns[i]);
		i++;
	}
	return (ft_free_tab((void **)sub_patterns), true);
}
