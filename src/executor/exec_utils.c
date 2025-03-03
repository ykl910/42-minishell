/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:15:46 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/03 15:15:59 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_urandom(char *str)
{
	if (!ft_strncmp(str, "/dev/urandom", ft_strlen(str)))
		return (true);
	if (!ft_strncmp(str, "/dev/random", ft_strlen(str)))
		return (true);
	return (false);
}
