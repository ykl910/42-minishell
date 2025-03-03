/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   V2pipes_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:07:15 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/03 12:27:09 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_infile(t_cmd *node, char **args, int *i)
{
	if (node->fd_in > -1)
		close(node->fd_in);
	if (is_urandom(args[*i + 1]))
		handle_open_error(&node->fd_in, args[*i + 1]);
	else
	{
		node->fd_in = open(args[*i + 1], O_RDONLY, 0644);
		if (node->fd_in < 0)
			handle_open_error(&node->fd_in, args[*i + 1]);
	}
	if(!node->redir_in)
		node->redir_in = true;
	*i += 2;
}

static void	redirect_trunc_outile(t_cmd *node, char **args, int *i)
{
	if (node->fd_out > -1)
		close(node->fd_out);
	node->fd_out = open(args[*i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (node->fd_out < 0)
		handle_open_error(&node->fd_out, args[*i + 1]);
	if(!node->redir_out)
		node->redir_out = true;
	*i += 2;
}

static void	redirect_app_outfile(t_cmd *node, char **args, int *i)
{
	if (node->fd_out > -1)
		close(node->fd_out);
	node->fd_out = open(args[*i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (node->fd_out < 0)
		handle_open_error(&node->fd_out, args[*i + 1]);
	if(!node->redir_out)
		node->redir_out = true;
	*i += 2;
}

static void	redirect_here_doc(t_cmd *node, char **args, int *i)
{
	char	*limiter;

	limiter = NULL;
	if (node->fd_in > -1)
		close(node->fd_in);
	limiter = ft_strdup(args[*i + 1]);
	if (!limiter)
		return ;
	node->fd_in = open("/tmp/hdoc", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (node->fd_in < 0)
		handle_open_error(&node->fd_in, args[*i + 1]);
	put_heredoc(node->fd_in, limiter);
	reopen_heredoc(&node->fd_in, args[*i + 1]);
	free(limiter);
	unlink("/tmp/hdoc");
	if(!node->redir_in)
		node->redir_in = true;
	*i += 2;
}

bool	is_redir(t_cmd *clst_node, char **args, int *i)
{
	size_t	size;

	size = ft_strlen(args[*i]);
	if (!ft_strncmp(args[*i], "<", size) && args[*i + 1])
		return (redirect_infile(clst_node, args, i), true);
	else if (!ft_strncmp(args[*i], ">", size) && args[*i + 1])
		return (redirect_trunc_outile(clst_node, args, i), true);
	else if (!ft_strncmp(args[*i], ">>", size) && args[*i + 1])
		return (redirect_app_outfile(clst_node, args, i), true);
	else if (!ft_strncmp(args[*i], "<<", size) && args[*i + 1])
		return (redirect_here_doc(clst_node, args, i), true);
	else
		return (false);
}
