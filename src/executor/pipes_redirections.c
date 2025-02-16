/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:11:22 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/14 13:11:56 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_infile(t_ast_node *node, int *i)
{
	if(node->infile_fd > -1)
			close(node->infile_fd);
	node->infile_fd = open(node->value[*i + 1], O_RDONLY, 0644);
	if(node->infile_fd < 0)
	{
		ft_putstr_fd("Error: Permisson denied", STDERR_FILENO);
		node->infile_fd = open("/dev/null", O_RDONLY);
	}
	*i += 2;
}

static void	redirect_trunc_outile(t_ast_node *node, int *i)
{
	if(node->outfile_fd > -1)
		close(node->outfile_fd);
	node->outfile_fd = open(node->value[*i + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if(node->infile_fd < 0)
	{
		ft_putstr_fd("Error: Permisson denied", STDERR_FILENO);
		node->outfile_fd = open("/dev/null", O_WRONLY);
	}
	*i +=2;
}

static void	redirect_app_outfile(t_ast_node *node, int *i)
{
	if(node->outfile_fd > -1)
		close(node->outfile_fd);
	node->outfile_fd = open(node->value[*i + 1], O_RDWR | O_APPEND | O_CREAT, 0644);
	if(node->infile_fd < 0)
	{
		ft_putstr_fd("Error: Permisson denied", STDERR_FILENO);
		node->outfile_fd = open("/dev/null", O_WRONLY);
	}
	*i += 2;
}

static void	redirect_here_doc(t_ast_node *node, int *i)
{
	if(node->infile_fd > -1)
		close(node->infile_fd);
	node->infile_fd = open("here_doc.txt", O_RDONLY, 0644);
	if(node->infile_fd < 0)
	{
		ft_putstr_fd("Error: Permisson denied", STDERR_FILENO);
		node->infile_fd = open("/dev/null", O_RDONLY);
	}
	*i += 2;
}

void	pipe_redir_cmd(t_ast_node *node, int *pipex)
{
	int	i;
	int	arg_size;

	i = 0;
	arg_size = 0;
	while(node->value[i])
	{
		arg_size = ft_strlen(node->value[i]);
		if(!ft_strncmp(node->value[i], "<", arg_size) && node->value[i + 1])
			redirect_infile(node, i);
		else if(!ft_strncmp(node->value[i], ">", arg_size) && node->value[i + 1])
			redirect_trunc_outile(node, i);
		else if(!ft_strncmp(node->value[i], ">>", arg_size) && node->value[i + 1])
			redirect_app_outfile(node, i);
		else if(!ft_strncmp(node->value[i], "<<", arg_size))
			redirect_here_doc(node, i);
		else
			i++;
	}
}
