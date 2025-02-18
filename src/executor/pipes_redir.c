/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:11:22 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/18 15:47:38 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_infile(t_ast_node *node, int *i)
{
	if (node->infile_fd > -1)
		close(node->infile_fd);
	if(is_urandom(node->value[*i + 1]))
		handle_open_error(node->infile_fd);
	else
	{
		node->infile_fd = open(node->value[*i + 1], O_RDONLY, 0644);
		if (node->infile_fd < 0)
			handle_open_error(node->infile_fd);
	}
	*i += 2;
}

static void	redirect_trunc_outile(t_ast_node *node, int *i)
{
	if (node->outfile_fd > -1)
		close(node->outfile_fd);
	node->outfile_fd = open(node->value[*i + 1], O_RDWR | O_TRUNC | O_CREAT,
			0644);
	if (node->outfile_fd < 0)
		handle_open_error(node->outfile_fd);
	if(!node->redirection)
		node->redirection = true;
	*i += 2;
}

static void	redirect_app_outfile(t_ast_node *node, int *i)
{
	if (node->outfile_fd > -1)
		close(node->outfile_fd);
	node->outfile_fd = open(node->value[*i + 1], O_RDWR | O_APPEND | O_CREAT,
			0644);
	if (node->outfile_fd < 0)
		handle_open_error(node->outfile_fd);
	if(!node->redirection)
		node->redirection = true;
	*i += 2;
}

static void	redirect_here_doc(t_ast_node *node, int *i)
{
	char *limiter;

	limiter = NULL;
	if (node->infile_fd > -1)
	{
		close(node->infile_fd);
		unlink("heredoc.txt");
	}
	limiter = ft_strdup(node->value[*i + 1]);
	if(!limiter)
		return ;
	node->infile_fd = open("heredoc.txt", O_CREAT | O_RDONLY, 0644);
	if (node->infile_fd < 0)
		handle_open_error(node->infile_fd);
	put_heredoc(node->infile_fd, limiter);
	reopen_heredoc(node->infile_fd);
	*i += 2;
}

void	pipe_redir_cmd(t_ast_node *node)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (node->value[i])
	{
		size = ft_strlen(node->value[i]);
		if (!ft_strncmp(node->value[i], "<", size) && node->value[i + 1])
			redirect_infile(node, &i);
		else if (!ft_strncmp(node->value[i], ">", size) && node->value[i + 1])
			redirect_trunc_outile(node, &i);
		else if (!ft_strncmp(node->value[i], ">>", size) && node->value[i + 1])
			redirect_app_outfile(node, &i);
		else if (!ft_strncmp(node->value[i], "<<", size && node->value[i + 1]))
			redirect_here_doc(node, &i);
		else
		{
			if(create_cmd(&(node->cmd), node->value[i]) == -1)
				return ;
			i++;
		}
	}
}
