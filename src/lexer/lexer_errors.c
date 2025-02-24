/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:56:04 by kyang             #+#    #+#             */
/*   Updated: 2025/02/24 18:40:09 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redirect(t_token **current)
{
	if ((*current)->token_type == TOKEN_REDIRECT_IN && (*current)->next
		&& (*current)->next->token_type == TOKEN_REDIRECT_APPEND)
		return (error_msg(TOK, ">"), 1);
	else if (((*current)->token_type == TOKEN_REDIRECT_IN
			|| (*current)->token_type == TOKEN_REDIRECT_OUT) && (*current)->next
		&& (*current)->next->token_type == TOKEN_AND)
		return (error_msg(TOK, "&"), 1);
	else if ((*current)->token_type == TOKEN_REDIRECT_OUT && (*current)->next
		&& (*current)->next->token_type == TOKEN_OR)
		return (error_msg(TOK, "|"), 1);
	else if ((*current)->token_type == TOKEN_REDIRECT_OUT && (*current)->next
		&& (*current)->next->token_type == TOKEN_REDIRECT_IN)
		return (error_msg(TOK, "<"), 1);
	else if ((*current)->token_type == TOKEN_REDIRECT_IN && (*current)->next
		&& (*current)->next->token_type == TOKEN_REDIRECT_OUT)
		return (error_msg(TOK, "newline"), 1);
	else if ((*current)->token_type >= TOKEN_REDIRECT_IN
		&& (*current)->token_type <= TOKEN_REDIRECT_APPEND)
	{
		if (!(*current)->next)
			return (error_msg(TOK, "newline"), 1);
		else if ((*current)->next && (*current)->next->token_type != TOKEN_TEXT)
			return (error_msg(TOK, (*current)->next->value), 1);
	}
	return (0);
}

static int	check_operator(t_token **current)
{
	if ((*current)->token_type == TOKEN_AND
		|| (*current)->token_type == TOKEN_OR
		|| (*current)->token_type == TOKEN_PIPE)
	{
		if ((*current)->next && ((*current)->next->token_type == TOKEN_AND
				|| (*current)->next->token_type == TOKEN_OR
				|| (*current)->next->token_type == TOKEN_PIPE
				|| (*current)->next->token_type == TOKEN_RPAREN))
			return (error_msg(TOK, (*current)->next->value), 1);
	}
	else if ((*current)->token_type == TOKEN_LPAREN)
	{
		if ((*current)->next && ((*current)->next->token_type == TOKEN_PIPE
				|| (*current)->next->token_type == TOKEN_AND
				|| (*current)->next->token_type == TOKEN_OR
				|| (*current)->next->token_type == TOKEN_RPAREN))
			return (error_msg(TOK, (*current)->next->value), 1);
	}
	return (0);
}

static int	check_current(t_token **current, t_token **last)
{
	while (*current)
	{
		if (check_redirect(current))
			return (1);
		if (check_operator(current))
			return (1);
		if ((*current)->next && (*current)->next->token_type == TOKEN_LPAREN
			&& ((*current)->token_type != TOKEN_PIPE
				&& (*current)->token_type != TOKEN_AND
				&& (*current)->token_type != TOKEN_OR))
			return (error_msg(TOK, (*current)->next->next->value), 1);
		*last = *current;
		(*current) = (*current)->next;
	}
	return (0);
}

int	check_lexer(t_token **tokens)
{
	t_token	*current;
	t_token	*last;

	current = *tokens;
	if (!current)
		return (0);
	if (current->token_type == TOKEN_PIPE || current->token_type == TOKEN_AND
		|| current->token_type == TOKEN_OR
		|| current->token_type == TOKEN_RPAREN
		|| (current->token_type == TOKEN_LPAREN
			&& current->next->token_type == TOKEN_RPAREN))
		return (error_msg(TOK, current->value), 1);
	if (check_current(&current, &last))
		return (1);
	if (last && (last->token_type == TOKEN_PIPE || last->token_type == TOKEN_AND
			|| last->token_type == TOKEN_OR
			|| last->token_type == TOKEN_LPAREN))
		return (error_msg(TOK, last->value), 1);
	return (0);
}
