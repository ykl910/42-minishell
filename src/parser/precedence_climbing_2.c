/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence_climbing_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:24:18 by kyang             #+#    #+#             */
/*   Updated: 2025/02/07 18:19:52 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Gerer cas de figure si create_node renvoie NULL -> Retour Main et free ?*/

t_ast_node	*parse_expression(t_token **tokens, int min_precedence)
{
	t_ast_node	*left;
	t_ast_node	*right;
	e_token		op;
	int			precedence;

	left = parse_primary(tokens);
	while (*tokens && get_precedence((*tokens)->token_type) >= min_precedence)
	{
		op = (*tokens)->token_type;
		precedence = get_precedence(op);
		(*tokens) = (*tokens)->next;
		right = parse_expression(tokens, precedence + 1);
		left = create_node(get_command_type(op), left, right, NULL); //ici
	}
	return (left);
}

t_ast_node	*parse_primary(t_token **tokens)
{
	t_ast_node	*node;
	t_ast_node	*subshell;

	if (!*tokens)
		return (NULL);
	if ((*tokens)->token_type >= TOKEN_REDIRECT_IN
		&& (*tokens)->token_type <= TOKEN_TEXT)
	{
		node = create_node(COMMAND_SIMPLE, NULL, NULL, (*tokens)->value); //ici
		*tokens = (*tokens)->next;
		while ((*tokens) && ((*tokens)->token_type >= TOKEN_REDIRECT_IN
		&& (*tokens)->token_type <= TOKEN_TEXT))
		{
			node->value = append_args(node->value, (*tokens)->value);  //ici
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
		return (create_node(COMMAND_SUBSHELL, subshell, NULL, NULL)); //ici
	}
	ft_putstr_fd("Syntax Error: Unexpected token\n", STDERR_FILENO);
	exit(1);
}
