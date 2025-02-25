/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:12:42 by kyang             #+#    #+#             */
/*   Updated: 2025/02/25 12:54:56 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//extern int g_signal;

void	input_eof(char **line, t_shell *shell)
{
	if (*line)
		free(*line);
	free_shell(shell);
	ft_putendl_fd("exit", 2);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

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

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	heredoc_handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = 1;
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

void	heredoc_signals(void)
{
	signal(SIGINT, process_handle_sigint);
	signal(SIGQUIT, process_handle_sigquit);
}
