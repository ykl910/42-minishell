/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:24:18 by kyang             #+#    #+#             */
/*   Updated: 2025/02/24 14:59:05 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Gerer cas de figure si create_node renvoie NULL -> Retour Main et free ?*/


t_ast_node	*parse_txt(t_token *current_token)
{
	t_ast_node	*node;
	node = create_node(COMMAND_SIMPLE, NULL, NULL, current_token->value);
	if (!node)
		return (NULL);
	current_token = current_token->next;
	while (current_token && current_token->token_type >= TOKEN_REDIRECT_IN
			&& current_token->token_type <= TOKEN_TEXT)
	{
		node->value = append_args(node->value, current_token->value);
		if (!node->value)
			return (free(node), NULL);
		current_token = current_token->next;
	}
	return (node);
}

t_ast_node	*parse_subshell(t_token *current_token, t_ast_node *subshell, t_shell *shell)
{
	current_token = current_token->next;
	subshell = parse_expression(&current_token, 0, shell);
	if (!current_token)
	{
		error_msg(RED SYN_INP RESET, NULL);
		shell->status = 1;
		//exit(2);
	}
	if (current_token->token_type != TOKEN_RPAREN)
	{
		error_msg(RED SYN_RPA RESET, NULL);
		shell->status = 1;
		//exit(2);
	}
	current_token= current_token->next;
	return (create_node(COMMAND_SUBSHELL, subshell, NULL, NULL));
}

t_ast_node	*parse_primary(t_token *current_token, t_shell *shell)
{
	t_ast_node	*subshell;

	subshell = NULL;
	if (!current_token)
		return (NULL);
	if (current_token->token_type >= TOKEN_REDIRECT_IN
		&& current_token->token_type <= TOKEN_TEXT)
		return (parse_txt(current_token));
	if (current_token->token_type == TOKEN_LPAREN)
		return (parse_subshell(current_token, subshell, shell));
	error_msg(RED SYN_TOK RESET, NULL);
	shell->status = 1;
	return (NULL);
	//exit(2);
}

t_ast_node	*parse_expression(t_token **tokens, int min_precedence, t_shell *shell)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_token		*current_token;
	e_token		op;
	int			precedence;

	if (!*tokens)
		return (NULL);
	current_token = *tokens;
	left = parse_primary(current_token, shell);
	if (!left)
	{
		error_msg(RED SYN_OPE RESET, NULL);
		shell->status = 1;
		//exit(2);
	}
	while (current_token && get_precedence(current_token->token_type) >= min_precedence)
	{
		op = current_token->token_type;
		precedence = get_precedence(op);
		current_token = current_token->next;
		right = parse_expression(&current_token, precedence + 1, shell);
		left = create_node(get_command_type(op), left, right, NULL);
	}
	return (left);
}

