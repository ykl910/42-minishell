/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:20:41 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/21 15:50:40 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *msg, char *context)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	if (!context)
		ft_putstr_fd("\n", STDERR_FILENO);
	else
		ft_putendl_fd(context, STDERR_FILENO);
}
