/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:24:18 by kyang             #+#    #+#             */
/*   Updated: 2025/02/24 16:14:30 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Gerer cas de figure si create_node renvoie NULL -> Retour Main et free ?*/

t_ast_node	*parse_txt(t_token **tokens)
{
	t_ast_node	*node;
	node = create_node(COMMAND_SIMPLE, NULL, NULL, (*tokens)->value);
	if (!node)
		return (NULL);
	*tokens = (*tokens)->next;
	while ((*tokens) && ((*tokens)->token_type >= TOKEN_REDIRECT_IN
			&& (*tokens)->token_type <= TOKEN_TEXT))
	{
		node->value = append_args(node->value, (*tokens)->value);
		if (!node->value)
			return (free(node), NULL);
		*tokens = (*tokens)->next;
	}
	return (node);
}

t_ast_node	*parse_subshell(t_token **tokens, t_ast_node *subshell, t_shell *shell)
{
	*tokens = (*tokens)->next;
	subshell = parse_expression(tokens, 0, shell);
	if (!*tokens)
	{
		error_msg(RED SYN_INP RESET, NULL);
		shell->status = 1;
	}
	if ((*tokens)->token_type != TOKEN_RPAREN)
	{
		error_msg(RED SYN_RPA RESET, NULL);
		shell->status = 1;
	}
	*tokens = (*tokens)->next;
	return (create_node(COMMAND_SUBSHELL, subshell, NULL, NULL));
}

t_ast_node	*parse_primary(t_token **tokens, t_shell *shell)
{
	t_ast_node	*subshell;

	subshell = NULL;
	if (!*tokens)
		return (NULL);
	if ((*tokens)->token_type >= TOKEN_REDIRECT_IN
		&& (*tokens)->token_type <= TOKEN_TEXT)
		return (parse_txt(tokens));
	if ((*tokens)->token_type == TOKEN_LPAREN)
		return (parse_subshell(tokens, subshell, shell));
	error_msg(RED SYN_TOK RESET, NULL);
	shell->status = 1;
	return (NULL);
}

t_ast_node	*parse_expression(t_token **tokens, int min_precedence, t_shell *shell)
{
	t_ast_node	*left;
	t_ast_node	*right;
	e_token		op;
	int			precedence;

	if (!*tokens)
		return (NULL);
	left = parse_primary(tokens, shell);
	if (!left)
	{
		error_msg(RED SYN_OPE RESET, NULL);
		//exit(2);
	}
	while (*tokens && get_precedence((*tokens)->token_type) >= min_precedence)
	{
		op = (*tokens)->token_type;
		precedence = get_precedence(op);
		(*tokens) = (*tokens)->next;
		right = parse_expression(tokens, precedence + 1, shell);
		left = create_node(get_command_type(op), left, right, NULL);
	}
	return (left);
}
