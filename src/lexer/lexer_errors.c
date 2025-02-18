/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:56:04 by kyang             #+#    #+#             */
/*   Updated: 2025/02/18 15:24:41 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	print_syntax_error(char *token_value, int *i)
{
	if (token_value == NULL || *token_value == '\0')
		token_value = "newline";
	*i = 1;
	write(2, "bash: syntax error near unexpected token `", 43);
	write(2, token_value, ft_strlen(token_value));
	write(2, "'\n", 2);
}

static void	check_redirect(t_token **current, int *i)
{
	if ((*current)->token_type == TOKEN_REDIRECT_IN && (*current)->next && \
	(*current)->next->token_type == TOKEN_REDIRECT_APPEND)
		print_syntax_error(">", i);
	else if (((*current)->token_type == TOKEN_REDIRECT_IN || (*current)->token_type == TOKEN_REDIRECT_OUT) && \
	(*current)->next && (*current)->next->token_type == TOKEN_AND)
		print_syntax_error("&", i);
	else if ((*current)->token_type == TOKEN_REDIRECT_OUT && (*current)->next && \
	(*current)->next->token_type == TOKEN_OR)
		print_syntax_error("|", i);
	else if ((*current)->token_type >= TOKEN_REDIRECT_IN && (*current)->token_type <= TOKEN_REDIRECT_APPEND)
	{
		if (!(*current)->next)
			print_syntax_error(NULL, i);
		else if ((*current)->next && (*current)->next->token_type != TOKEN_TEXT)
			print_syntax_error((*current)->next->value, i);
	}
}

static void	check_operator(t_token **current, int *i)
{
	if ((*current)->token_type == TOKEN_AND || \
	(*current)->token_type == TOKEN_OR || (*current)->token_type == TOKEN_PIPE)
	{
		if ((*current)->next && ((*current)->next->token_type == TOKEN_AND || \
		(*current)->next->token_type == TOKEN_OR || (*current)->next->token_type == TOKEN_PIPE || \
		(*current)->next->token_type == TOKEN_RPAREN))
			print_syntax_error((*current)->next->value, i);
	}
	else if ((*current)->token_type == TOKEN_LPAREN)
	{
		if ((*current)->next && ((*current)->next->token_type == TOKEN_PIPE || \
		(*current)->next->token_type == TOKEN_AND || (*current)->next->token_type == TOKEN_OR || \
		(*current)->next->token_type == TOKEN_RPAREN))
			print_syntax_error((*current)->next->value, i);
	}
}

static void	check_current(t_token **current, t_token **last, int *i)
{
	while (*current)
	{
		if ((*current)->next && (*current)->token_type == TOKEN_REDIRECT_IN && \
		(*current)->next->token_type == TOKEN_REDIRECT_OUT)
		{
			(*current) = (*current)->next;
			continue ;
		}
		check_redirect(current, i);
		check_operator(current, i);
		if ((*current)->next && (*current)->next->token_type == TOKEN_LPAREN && \
		((*current)->token_type != TOKEN_PIPE && (*current)->token_type != TOKEN_AND && (*current)->token_type != TOKEN_OR))
			print_syntax_error((*current)->next->next->value, i);
		*last = *current;
		(*current) = (*current)->next;
	}
}

int	check_lexer(t_token **tokens, t_shell *shell)
{
	t_token	*current;
	t_token	*last;

	current = *tokens;
	if (!current)
	{
		shell->status = 1;
		return (shell->status);
	}
	if (current->token_type == TOKEN_PIPE || current->token_type == TOKEN_AND || \
	current->token_type == TOKEN_OR || current->token_type == TOKEN_RPAREN || \
	(current->token_type == TOKEN_LPAREN && current->next->token_type == TOKEN_RPAREN))
		print_syntax_error(current->value, &shell->status);
	check_current(&current, &last,  &shell->status);
	if (last && (last->token_type == TOKEN_PIPE || last->token_type == TOKEN_AND ||
					last->token_type == TOKEN_OR || last->token_type == TOKEN_LPAREN))
		print_syntax_error(last->value,  &shell->status);
	return (shell->status);
}
