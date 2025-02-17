/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:56:04 by kyang             #+#    #+#             */
/*   Updated: 2025/02/17 18:01:14 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	print_syntax_error(char *token_value)
{
	if (token_value == NULL || *token_value == '\0')
		token_value = "newline";
	write(2, "bash: syntax error near unexpected token `", 43);
	write(2, token_value, ft_strlen(token_value));
	write(2, "'\n", 2);
	exit(1);
}

// pipe or and or or before a left parent
void	check_lexer(t_token **tokens)
{
	t_token	*current;
	t_token	*last;

	current = *tokens;
	if (!current)
		exit(1);
	if (current->token_type == TOKEN_PIPE || current->token_type == TOKEN_AND || \
	current->token_type == TOKEN_OR || current->token_type == TOKEN_RPAREN || \
	(current->token_type == TOKEN_LPAREN && current->next->token_type == TOKEN_RPAREN))
		print_syntax_error(current->value);
	while (current)
	{
		if (current->next && current->token_type == TOKEN_REDIRECT_IN && \
		current->next->token_type == TOKEN_REDIRECT_OUT)
		{
			current = current->next;
			continue ;
		}
		else if (current->token_type == TOKEN_REDIRECT_IN && current->next && \
		current->next->token_type == TOKEN_REDIRECT_APPEND)
			print_syntax_error(">");
		else if ((current->token_type == TOKEN_REDIRECT_IN || current->token_type == TOKEN_REDIRECT_OUT) && \
		current->next && current->next->token_type == TOKEN_AND)
			print_syntax_error("&");
		else if (current->token_type == TOKEN_REDIRECT_OUT && current->next && \
		current->next->token_type == TOKEN_OR)
			print_syntax_error("|");
		else if (current->token_type >= TOKEN_REDIRECT_IN && current->token_type <= TOKEN_REDIRECT_APPEND)
		{
			if (!current->next)
				print_syntax_error(NULL);
			else if (current->next && current->next->token_type != TOKEN_TEXT)
				print_syntax_error(current->next->value);
		}
		else if (current->token_type == TOKEN_AND || \
		current->token_type == TOKEN_OR || current->token_type == TOKEN_PIPE)
		{
			if (current->next && (current->next->token_type == TOKEN_AND || \
			current->next->token_type == TOKEN_OR || current->next->token_type == TOKEN_PIPE || \
			current->next->token_type == TOKEN_RPAREN))
				print_syntax_error(current->next->value);
		}
		else if (current->token_type == TOKEN_LPAREN)
		{
			if (current->next && (current->next->token_type == TOKEN_PIPE || \
			current->next->token_type == TOKEN_AND || current->next->token_type == TOKEN_OR || \
			current->next->token_type == TOKEN_RPAREN))
				print_syntax_error(current->next->value);
		}
		last = current;
		current = current->next;
	}
	if (last && (last->token_type == TOKEN_PIPE || last->token_type == TOKEN_AND ||
					last->token_type == TOKEN_OR || last->token_type == TOKEN_LPAREN))
		print_syntax_error(last->value);
}
