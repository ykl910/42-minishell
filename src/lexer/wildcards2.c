/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:44:09 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/27 16:25:55 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_not_hidden_file(char *file)
{
	int	f_len;

	if (!file)
		return (false);
	f_len = ft_strlen(file);
	if (file[0] == '.')
		return (false);
	if (f_len > 1 && file[1] == '.')
		return (false);
	return (true);
}

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

bool	match_subpatterns(char **sub_p, char *file, int f_size)
{
	int		i;
	char	*temp;
	int		s_size;
	int		p_size;

	p_size = 0;
	i = 0;
	s_size = ft_tabsize((void **)sub_p);
	temp = file;
	if (!match_prefix(file, sub_p[i], ft_strlen(sub_p[i]) + 1))
		return (ft_free_tab((void **)sub_p), false);
	temp += ft_strlen(sub_p[i]);
	i++;
	while (i < s_size - 1)
	{
		temp = ft_strnstr(temp, sub_p[i], f_size - (ft_strlen(temp) - f_size));
		if (!temp)
			return (ft_free_tab((void **)sub_p), false);
		temp += ft_strlen(sub_p[i]);
		i++;
	}
	p_size = ft_strlen(sub_p[s_size - 1]);
	if (!ft_strncmp(&temp[ft_strlen(temp) - p_size], sub_p[s_size - 1], p_size))
		return (ft_free_tab((void **)sub_p), true);
	return (ft_free_tab((void **)sub_p), false);
}
