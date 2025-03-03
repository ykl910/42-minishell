/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:11:52 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/03 15:22:59 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_open_error(int *fd, char *file)
{
	error_msg(RED PERM RESET, file);
	*fd = -1;
}

void	p_handle_cmd_error(t_cmd **current, int err_code)
{
	(*current)->status = err_code;
	(*current)->abs_path = NULL;
	error_msg(RED CMD RESET, (*current)->cmd[0]);
}

void	p_handle_error(t_cmd **current, t_shell *shell)
{
	(*current)->status = 1;
	free_exit(&(*current)->status, shell);
}

void	s_handle_cmd_error(t_ast_node **current, int err_code)
{
	(*current)->status = err_code;
	(*current)->cmd_abs_path = NULL;
	error_msg(RED CMD RESET, (*current)->cmd[0]);
}

void	s_handle_error(t_ast_node **current, t_shell *shell)
{
	(*current)->status = 1;
	free_exit(&(*current)->status, shell);
}
