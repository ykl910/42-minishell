/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:44:09 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/04 13:14:47 by alacroix         ###   ########.fr       */
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
