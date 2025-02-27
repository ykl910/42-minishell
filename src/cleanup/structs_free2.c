/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_free2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:29:51 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/27 11:41:58 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exit(int *exit_status, t_shell *shell)
{
	int	status;

	status = *exit_status;
	if (shell->shell_env)
		free_env(&shell->shell_env);
	if (shell->token_lst)
		free_tokens(&shell->token_lst);
	if (shell->paths)
		ft_free_tab((void **)shell->paths);
	if (shell->ast)
		free_ast(shell->ast);
	if (shell->prompt)
		free(shell->prompt);
	rl_clear_history();
	exit(status);
}
