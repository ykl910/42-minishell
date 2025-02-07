/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:12:42 by kyang             #+#    #+#             */
/*   Updated: 2025/02/07 19:08:41 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_redir(char *av, int *i)
{
	t_token	*new_token;

	new_token = NULL;
	if (av[*i] == '<' && av[*i + 1] == '<')
	{
		new_token = init_token(TOKEN_HERE_DOC, "<<");
		*i += 2;
	}
	else if (av[*i] == '>' && av[*i + 1] == '>')
	{
		new_token = init_token(TOKEN_REDIRECT_APPEND, ">>");
		*i += 2;
	}
	else if (av[*i] == '<' && av[*i + 1] != '<')
	{
		new_token = init_token(TOKEN_REDIRECT_IN, "<");
		*i += 1;
	}
	else if (av[*i] == '>' && av[*i + 1] != '<')
	{
		new_token = init_token(TOKEN_REDIRECT_OUT, ">");
		*i += 1;
	}
	return (new_token);
}

t_token	*create_logical_ops_parantheses(char *av, int *i)
{
	t_token	*new_token;

	new_token = NULL;
	if (av[*i] == '&' && av[*i + 1] == '&')
	{
		new_token = init_token(TOKEN_AND, "&&");
		*i += 2;
	}
	else if (av[*i] == '|' && av[*i + 1] == '|')
	{
		new_token = init_token(TOKEN_OR, "||");
		*i += 2;
	}
	else if (av[*i] == '(')
	{
		new_token = init_token(TOKEN_LPAREN, "(");
		*i += 1;
	}
	else if (av[*i] == ')')
	{
		new_token = init_token(TOKEN_RPAREN, ")");
		*i += 1;
	}
	return (new_token);
}

t_token	*create_pipe_text(char *av, int *i)
{
	t_token	*new_token;
	int		start;
	int		quote;

	new_token = NULL;
	if (av[*i] == '|' && av[*i + 1] != '|')
	{
		new_token = init_token(TOKEN_PIPE, "|");
		*i += 1;
	}
	else
	{
		start = *i;
		quote = 0;
		while (av[*i] && (!ft_issep(av[*i]) || quote))
		{
			if (!quote && (av[*i] == '\'' || av[*i] == '"'))
				quote = av[*i];
			else if (quote && av[*i] == quote)
				quote = 0;
			(*i)++;
		}
		new_token = init_token(TOKEN_TEXT, ft_strndup(av + start, *i - start));
	}
	return (new_token);
}

t_token	*create_token(char *av, int *i)
{
	t_token	*new_token;

	new_token = NULL;
	new_token = create_redir(av, i);
	if (!new_token)
		new_token = create_logical_ops_parantheses(av, i);
	if (!new_token)
		new_token = create_pipe_text(av, i);
	return (new_token);
}

t_token	*lexer(char *av)
{
	t_token	*tokens;
	t_token	*current;
	t_token	*new_token;
	int		i;

	i = 0;
	tokens = NULL;
	current = NULL;
	while (av[i])
	{
		while (av[i] <= ' ')
			i++;
		new_token = NULL;
		new_token = create_token(av, &i);
		if (!tokens)
			tokens = new_token;
		else
			current->next = new_token;
		current = new_token;
	}
	return (tokens);
}

void	check_lexer(t_token **tokens)
{
	t_token	*current;
	t_token	*new_token;

	current = *tokens;
	if (!current->next)
	{
		if (current->token_type != TOKEN_TEXT)
		{
			ft_putstr_fd("Syntax Error near unexpected token 1\n", STDERR_FILENO);
			exit(1);
		}
	}
	new_token = current->next;
	while (new_token)
	{
		if ((current->token_type != TOKEN_TEXT) && \
		current->token_type == new_token->token_type)
		{
			ft_putstr_fd("Syntax Error near unexpected token 2\n", STDERR_FILENO);
			exit(1);
		}
		new_token = new_token->next;
	}
}
