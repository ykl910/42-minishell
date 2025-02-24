/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:30:23 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/24 16:34:34 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_open_error(int *fd, char *file)
{
	error_msg(RED PERM RESET, file);
	*fd = -1;
	//open("/dev/null", O_RDWR);
}

bool	is_urandom(char *str)
{
	if (!ft_strncmp(str, "/dev/urandom", ft_strlen(str)))
		return (true);
	return (false);
}

void	redir_std(t_ast_node **current)
{
	if ((*current)->infile_fd != -1)
	{
		dup2((*current)->infile_fd, STDIN_FILENO);
		close((*current)->infile_fd);
	}
	if ((*current)->outfile_fd != -1)
	{
		dup2((*current)->outfile_fd, STDOUT_FILENO);
		close((*current)->outfile_fd);
	}
}
