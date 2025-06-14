/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:30:30 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/11 13:47:49 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_exit(long exit_code, t_shell *shell)
{
	free_shell(shell);
	rl_clear_history();
	exit(exit_code % 256);
}

static void	manage_num_error(char *str, t_shell *shell)
{
	error_msg(RED EXIT RESET, str);
	clean_exit(255, shell);
}

static void	manage_args_error(t_shell *shell)
{
	shell->status = 1;
	error_msg(RED EXIT_ARG RESET, NULL);
}

static void	exit_args(char **args, t_shell *shell)
{
	long long	exit_code;
	size_t		args_len;

	args_len = ft_tabsize((void **)args);
	if (ft_isalpha(args[1][0]))
	{
		error_msg(RED EXIT RESET, args[1]);
		clean_exit(2, shell);
	}
	exit_code = 0;
	exit_code = ft_atoll(args[1]);
	if (args_len == 2)
	{
		if (INT_MIN > exit_code || exit_code > INT_MAX)
			manage_num_error(args[1], shell);
		else
			clean_exit(exit_code, shell);
	}
	else
		manage_args_error(shell);
}

void	builtin_exit(char **args, t_shell *shell)
{
	size_t	args_len;

	args_len = ft_tabsize((void **)args);
	ft_printf("exit\n");
	if (args_len == 1)
		clean_exit(0, shell);
	else
		exit_args(args, shell);
}
