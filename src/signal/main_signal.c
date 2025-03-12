/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:12:42 by kyang             #+#    #+#             */
/*   Updated: 2025/03/12 10:54:59 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_eof(char **line, t_shell *shell)
{
	if (*line)
		free(*line);
	free_shell(shell);
	ft_putendl_fd("exit", 2);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

void	handle_sigint(int sig)
{
	(void)sig;
	g_exit_status = 130;
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
	{
		g_exit_status = 128 + WTERMSIG(*status);
		return (g_exit_status);
	}
	else
		return (1);
}

void	signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
