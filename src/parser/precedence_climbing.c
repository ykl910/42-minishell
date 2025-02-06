/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence_climbing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:24:18 by kyang             #+#    #+#             */
/*   Updated: 2025/02/06 18:53:46 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_expression(t_token **tokens, int min_precedence)
{
	t_ast_node	*left;
	t_ast_node	*right;
	e_token		op;
	int			precedence;
	t_ast_node	*file_node;

	left = parse_primary(tokens);
	while (*tokens && get_precedence((*tokens)->token_type) >= min_precedence)
	{
		op = (*tokens)->token_type;
		precedence = get_precedence(op);
		(*tokens) = (*tokens)->next;
		if (op >= TOKEN_REDIRECT_IN && op <= TOKEN_REDIRECT_APPEND)
		{
			if (!*tokens || (*tokens)->token_type != TOKEN_TEXT)
			{
				ft_putstr_fd("Syntax Error: Expected filename after redirection\n",
					STDERR_FILENO);
				exit(1);
			}
			file_node = create_node(COMMAND_SIMPLE, NULL, NULL,
					(*tokens)->value);
			*tokens = (*tokens)->next;
			left = create_node(get_command_type(op), left, file_node, NULL);
			continue ;
		}
		right = parse_expression(tokens, precedence + 1);
		left = create_node(get_command_type(op), left, right, NULL);
	}
	return (left);
}

t_ast_node	*parse_primary(t_token **tokens)
{
	t_ast_node	*node;
	t_ast_node	*subshell;
	t_ast_node	*file_node;
	e_token		op;

	if (!*tokens)
		return (NULL);
	if ((*tokens)->token_type >= TOKEN_REDIRECT_IN
		&& (*tokens)->token_type <= TOKEN_REDIRECT_APPEND)
	{
		op = (*tokens)->token_type;
		*tokens = (*tokens)->next;
		if (!*tokens || (*tokens)->token_type != TOKEN_TEXT)
		{
			ft_putstr_fd("Syntax Error: Expected filename after redirection\n",
				STDERR_FILENO);
			exit(1);
		}
		file_node = create_node(COMMAND_SIMPLE, NULL, NULL, (*tokens)->value);
		*tokens = (*tokens)->next;
		node = parse_primary(tokens);
		return (create_node(get_command_type(op), node, file_node, NULL));
	}
	if ((*tokens)->token_type == TOKEN_TEXT)
	{
		node = create_node(COMMAND_SIMPLE, NULL, NULL, (*tokens)->value);
		*tokens = (*tokens)->next;
		while ((*tokens) && ((*tokens)->token_type == TOKEN_TEXT))
		{
			node->value = append_args(node->value, (*tokens)->value);
			*tokens = (*tokens)->next;
		}
		return (node);
	}
	if ((*tokens)->token_type == TOKEN_LPAREN)
	{
		*tokens = (*tokens)->next;
		subshell = parse_expression(tokens, 0);
		if (!*tokens || (*tokens)->token_type != TOKEN_RPAREN)
		{
			ft_putstr_fd("Syntax Error: Missing ')'\n", STDERR_FILENO);
			exit(1);
		}
		*tokens = (*tokens)->next;
		return (create_node(COMMAND_SUBSHELL, subshell, NULL, NULL));
	}
	ft_putstr_fd("Syntax Error: Unexpected token\n", STDERR_FILENO);
	exit(1);
}
