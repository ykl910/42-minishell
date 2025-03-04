/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:23:12 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/04 14:23:57 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipes_std_dup(t_cmd **current, t_shell *shell)
{
	if ((*current)->fd_in != -1)
	{
		if (dup2((*current)->fd_in, STDIN_FILENO) == -1)
			p_handle_error(current, shell);
		close((*current)->fd_in);
	}
	if ((*current)->fd_out != -1)
	{
		if (dup2((*current)->fd_out, STDOUT_FILENO) == -1)
			p_handle_error(current, shell);
		close((*current)->fd_out);
	}
}

void	simple_std_dup(t_ast_node **current, t_shell *shell)
{
	if ((*current)->infile_fd != -1)
	{
		if (dup2((*current)->infile_fd, STDIN_FILENO) == -1)
			s_handle_error(current, shell);
		close((*current)->infile_fd);
	}
	if ((*current)->outfile_fd != -1)
	{
		if (dup2((*current)->outfile_fd, STDOUT_FILENO) == -1)
			s_handle_error(current, shell);
		close((*current)->outfile_fd);
	}
}
