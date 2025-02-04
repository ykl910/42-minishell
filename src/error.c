/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:56:40 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/04 14:09:50 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *msg, char *target)
{
	if(msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	if (target)
		ft_putstr_fd(target, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
