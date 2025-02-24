/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:29:51 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/24 15:30:09 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->value)
		ft_free_tab((void **)node->value);
	if (node->cmd)
		ft_free_tab((void **)node->cmd);
	if (node->cmd_abs_path)
		free(node->cmd_abs_path);
	if (node->infile_fd > 0)
		close(node->infile_fd);
	if (node->outfile_fd > 0)
		close(node->outfile_fd);
	unlink("heredoc.txt");
	free(node);
	node = NULL;
}

void	free_wildcard(t_wildcards *node)
{
	t_wildcards	*current;
	t_wildcards	*next;

	if (!node)
		return ;
	current = node;
	while (current)
	{
		next = current->next;
		if (current->file)
			free(current->file);
		free(current);
		current = next;
	}
	node = NULL;
}

void	free_env(t_env **node)
{
	t_env	*current;
	t_env	*next;

	if (!*node || !node)
		return ;
	current = *node;
	while (current)
	{
		next = current->next;
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
		if (current->key_val)
			free(current->key_val);
		free(current);
		current = next;
	}
	*node = NULL;
}

void	free_tokens(t_token **node)
{
	t_token	*current;
	t_token	*next;

	if (!*node || !node)
		return ;
	current = *node;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*node = NULL;
}

void	free_shell(t_shell *shell)
{
	if (shell->shell_env)
		free_env(&shell->shell_env);
	if (shell->token_lst)
		free_tokens(&shell->token_lst);
	if (shell->paths)
		ft_free_tab((void **)shell->paths);
	free(shell);
	shell = NULL;
}
