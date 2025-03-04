/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:13:25 by kyang             #+#    #+#             */
/*   Updated: 2025/03/04 14:16:48 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**append_args(char **origin_args, char *new_arg)
{
	char	**new_args;
	int		i;

	i = 0;
	while (origin_args[i])
		i++;
	new_args = ft_calloc((i + 2), sizeof(char *));
	if (!new_args)
		return (NULL);
	i = 0;
	while (origin_args[i])
	{
		new_args[i] = ft_strdup(origin_args[i]);
		if (!new_args[i])
			return (error_msg(MEM, "append_args(1)"),
				ft_free_tab((void **)new_args), NULL);
		i++;
	}
	ft_free_tab((void **)origin_args);
	new_args[i] = ft_strdup(new_arg);
	if (!new_args[i])
		return (error_msg(MEM, "append_args(2)"),
			ft_free_tab((void **)new_args), NULL);
	return (new_args);
}

int	get_precedence(t_tok_enum token)
{
	if (token == TOKEN_AND || token == TOKEN_OR)
		return (1);
	else if (token == TOKEN_PIPE)
		return (2);
	else if (token == TOKEN_REDIRECT_IN || token == TOKEN_REDIRECT_OUT
		|| token == TOKEN_HERE_DOC || token == TOKEN_REDIRECT_APPEND)
		return (2);
	else if (token == TOKEN_LPAREN)
		return (3);
	else
		return (-1);
}

t_com_enum	get_command_type(t_tok_enum token_type)
{
	if (token_type == TOKEN_AND)
		return (COMMAND_AND);
	else if (token_type == TOKEN_OR)
		return (COMMAND_OR);
	else if (token_type == TOKEN_PIPE)
		return (COMMAND_PIPE);
	else
		return (COMMAND_SIMPLE);
}

t_ast_node	*create_node(t_com_enum type, t_ast_node *left, t_ast_node *right,
		char *value)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (error_msg(MEM, "create_node(1)"), NULL);
	node->node_type = type;
	node->left = left;
	node->right = right;
	node->value = ft_calloc(2, sizeof(char *));
	if (!node->value)
		return (error_msg(MEM, "create_node(2)"), NULL);
	node->cmd = NULL;
	node->cmd_abs_path = NULL;
	node->status = 0;
	node->infile_fd = -1;
	node->outfile_fd = -1;
	node->redir_in = false;
	node->redir_out = false;
	if (value)
	{
		node->value[0] = ft_strdup(value);
		if (!node->value[0])
			return (error_msg(MEM, "create_node(3)"), NULL);
	}
	return (node);
}
