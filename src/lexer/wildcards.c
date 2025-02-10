/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:20:41 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/10 16:44:26 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	match_pattern(char *file, char *pattern, int p_size)
{
	int		f_size;
	char	**sub_patterns;

	f_size = ft_strlen(file);
	sub_patterns = NULL;
	if (!file || !*file)
		return (false);
	if (p_size == 1 && pattern[0] == '*')
		return (true);
	else if (p_size > f_size)
		return (false);
	else if (pattern[0] == '*' && (occurence_count(pattern, '*') < 2))
		return (match_suffix(file, pattern, f_size, p_size));
	else if (pattern[p_size - 1] == '*' && (occurence_count(pattern, '*') < 2))
		return (match_prefix(file, pattern, p_size));
	else
	{
		sub_patterns = ft_split(pattern, '*');
		if (!sub_patterns)
			return (false);
		else
			return (match_subpatterns(sub_patterns, file, f_size));
	}
}

static int	browse_dir(void *dir, char *pattern, t_wildcards **expension)
{
	int				index;
	int				pattern_size;
	struct dirent	*curr_dir;

	index = 0;
	pattern_size = ft_strlen(pattern);
	curr_dir = NULL;
	while ((curr_dir = readdir(dir)) != NULL)
	{
		if (match_pattern(curr_dir->d_name, pattern, pattern_size))
		{
			if (wc_struct(expension, ft_strdup(curr_dir->d_name), index) == -1)
				return (free_wc_struct(expension), -1);
		}
		index++;
	}
	return (0);
}

t_wildcards	*wildcard_expension(char *pattern)
{
	void		*dir;
	t_wildcards	*expension;

	if (!pattern || !*pattern)
		return (NULL);
	expension = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	if (browse_dir(dir, pattern, &expension) == -1)
		return (closedir(dir), NULL);
	return (closedir(dir), expension);
}
