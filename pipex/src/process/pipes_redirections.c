/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:30:39 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/03 17:49:12 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipes_dup_for_child(int *pipe, t_fd fds, t_lst *cmd, int size)
{
	if (cmd->index == 0 && size != 1)
	{
		if (dup2(fds.infile_fd, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		if (dup2(pipe[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	else if (cmd->index == size - 1 && size != 1)
	{
		if (dup2(fds.outfile_fd, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	else if (cmd->index == size - 1 && size == 1)
	{
		if (dup2(fds.infile_fd, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		if (dup2(fds.outfile_fd, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		if (dup2(pipe[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
}

void	pipes_dup_for_parent(int *pipe, t_lst *cmd, int size)
{
	if (cmd->index != size - 1 && size != 1)
	{
		if (dup2(pipe[0], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
}
