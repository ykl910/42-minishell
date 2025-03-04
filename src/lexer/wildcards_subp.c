/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_subp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:14:09 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/04 13:15:15 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	match_only_sub(char **sub_p, char *file, int f_size)
{
	int		i;
	char	*temp;
	int		s_size;
	int		p_size;

	p_size = 0;
	i = 0;
	s_size = ft_tabsize((void **)sub_p);
	temp = file;
	while (i < s_size)
	{
		temp = ft_strnstr(temp, sub_p[i], f_size - (ft_strlen(temp) - f_size));
		if (!temp)
			return (ft_free_tab((void **)sub_p), false);
		temp += ft_strlen(sub_p[i]);
		i++;
	}
	return (ft_free_tab((void **)sub_p), true);
}

static bool	match_prefix_sub(char **sub_p, char *file, int f_size)
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
	while (i < s_size)
	{
		temp = ft_strnstr(temp, sub_p[i], f_size - (ft_strlen(temp) - f_size));
		if (!temp)
			return (ft_free_tab((void **)sub_p), false);
		temp += ft_strlen(sub_p[i]);
		i++;
	}
	return (ft_free_tab((void **)sub_p), true);
}

static bool	match_suffix_sub(char **sub_p, char *file, int f_size)
{
	int		i;
	char	*temp;
	int		s_size;
	int		p_size;

	p_size = 0;
	i = 0;
	s_size = ft_tabsize((void **)sub_p);
	temp = file;
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

static bool	match_all(char **sub_p, char *file, int f_size)
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

bool	match_subpatterns(char **sub_p, char *pattern, char *file, int f_size)
{
	int	pattern_size;

	pattern_size = ft_strlen(pattern);
	if (pattern[0] != '*' && pattern[pattern_size - 1] != '*')
		return (match_all(sub_p, file, f_size));
	else if (pattern[0] != '*' && pattern[pattern_size - 1] == '*')
		return (match_prefix_sub(sub_p, file, f_size));
	else if (pattern[0] == '*' && pattern[pattern_size - 1] != '*')
		return (match_suffix_sub(sub_p, file, f_size));
	else
		return (match_only_sub(sub_p, file, f_size));
}
