/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:30:23 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/18 15:46:51 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_open_error(int fd)
{
	ft_putendl_fd("Error: Permisson denied", STDERR_FILENO);
	fd = open("/dev/null", O_RDONLY);
}

bool	is_urandom(char *str)
{
	if (!ft_strncmp(str, "/dev/urandom", ft_strlen(str)))
		return (true);
	return (false);
}
