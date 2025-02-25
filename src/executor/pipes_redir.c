/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:11:22 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/25 15:58:37 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_infile(t_ast_node *node, char **args, int *i)
{
	if (node->infile_fd > -1)
		close(node->infile_fd);
	if (is_urandom(args[*i + 1]))
		handle_open_error(&node->infile_fd, args[*i + 1]);
	else
	{
		node->infile_fd = open(args[*i + 1], O_RDONLY, 0644);
		if (node->infile_fd < 0)
			handle_open_error(&node->infile_fd, args[*i + 1]);
	}
	if (!node->redir_in)
		node->redir_in = true;
	*i += 2;
}

static void	redirect_trunc_outile(t_ast_node *node, char **args, int *i)
{
	if (node->outfile_fd > -1)
		close(node->outfile_fd);
	node->outfile_fd = open(args[*i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (node->outfile_fd < 0)
		handle_open_error(&node->outfile_fd, args[*i + 1]);
	if (!node->redir_out)
		node->redir_out = true;
	*i += 2;
}

static void	redirect_app_outfile(t_ast_node *node, char **args, int *i)
{
	if (node->outfile_fd > -1)
		close(node->outfile_fd);
	node->outfile_fd = open(args[*i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (node->outfile_fd < 0)
		handle_open_error(&node->outfile_fd, args[*i + 1]);
	if (!node->redir_out)
		node->redir_out = true;
	*i += 2;
}

static void	redirect_here_doc(t_ast_node *node, char **args, int *i)
{
	char	*limiter;

	limiter = NULL;
	if (node->infile_fd > -1)
	{
		close(node->infile_fd);
	}
	limiter = ft_strdup(args[*i + 1]);
	if (!limiter)
		return ;
	node->infile_fd = open("/tmp/hdoc", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (node->infile_fd < 0)
		handle_open_error(&node->infile_fd, args[*i + 1]);
	put_heredoc(node->infile_fd, limiter);
	reopen_heredoc(&node->infile_fd, args[*i + 1]);
	free(limiter);
	if (!node->redir_in)
		node->redir_in = true;
	*i += 2;
}

static bool	is_redir(t_ast_node *node, char **args, int *i)
{
	size_t	size;

	size = ft_strlen(args[*i]);
	if (!ft_strncmp(args[*i], "<", size) && args[*i + 1])
		return (redirect_infile(node, args, i), true);
	else if (!ft_strncmp(args[*i], ">", size) && args[*i + 1])
		return (redirect_trunc_outile(node, args, i), true);
	else if (!ft_strncmp(args[*i], ">>", size) && args[*i + 1])
		return (redirect_app_outfile(node, args, i), true);
	else if (!ft_strncmp(args[*i], "<<", size) && args[*i + 1])
		return (redirect_here_doc(node, args, i), true);
	else
		return (false);
}

void	cmd_builder(t_ast_node *node)
{
	char	**args;
	int		i;
	int		size;

	i = 0;
	size = 0;
	args = quotes_handler(node->value);
	if (!args)
		return ;
	while (args[i])
	{
		if (!is_redir(node, args, &i))
		{
			if (create_cmd(&(node->cmd), args[i]) == -1)
				return ;
			i++;
		}
	}
	unlink("/tmp/hdoc");
	ft_free_tab((void **)args);
}
