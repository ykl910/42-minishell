/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:12:42 by kyang             #+#    #+#             */
/*   Updated: 2025/02/26 14:50:05 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_handle_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
}

void	process_handle_sigquit(int sig)
{
	(void)sig;
	ft_printf("Quit\n");
}

void	process_signals(void)
{
	signal(SIGINT, process_handle_sigint);
	signal(SIGQUIT, process_handle_sigquit);
}
