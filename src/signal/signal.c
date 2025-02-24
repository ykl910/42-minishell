/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:12:42 by kyang             #+#    #+#             */
/*   Updated: 2025/02/24 19:47:10 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_eof(char **line)
{
	if (*line != NULL)
		free(*line);
	ft_putendl_fd("exit", 2);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

void	process_handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	process_handle_sigquit(int sig)
{
	(void)sig;
	ft_printf("Quit\n");
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	get_return_value(int *status)
{
	if (WIFEXITED(*status))
		return (WEXITSTATUS(*status));
	else if (WIFSIGNALED(*status))
		return (128 + WTERMSIG(*status));
	else
		return (1);
}

void	signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	process_signals(void)
{
	signal(SIGINT, process_handle_sigint);
	signal(SIGQUIT, process_handle_sigquit);
}
