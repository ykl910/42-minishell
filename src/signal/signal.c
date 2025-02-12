/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:12:42 by kyang             #+#    #+#             */
/*   Updated: 2025/02/12 10:03:39 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigint_flag = 0;

void handle_sigint(int sig)
{
	(void)sig;

	g_sigint_flag = 1;
	write(STDOUT_FILENO, "\n", 1);
	//rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void handle_sigquit(int sig)
{
	(void)sig;

	exit(1);
}