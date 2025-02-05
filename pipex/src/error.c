/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:56:40 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/23 12:57:00 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *msg, char *target)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	if (target)
		ft_putstr_fd(target, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
