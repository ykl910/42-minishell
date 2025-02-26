/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:12:42 by kyang             #+#    #+#             */
/*   Updated: 2025/02/26 14:50:34 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*create_redir(char *av, int *i)
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
	else if (av[*i] == '>' && av[*i + 1] != '>')
	{
		new_token = init_token(TOKEN_REDIRECT_OUT, ">");
		*i += 1;
	}
	return (new_token);
}

static t_token	*create_logical_ops_parantheses(char *av, int *i)
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

static char	*extract_text_token(char *av, int *i)
{
	int	start;
	int	quote;
	int	sep_len;

	start = *i;
	quote = 0;
	while (av[*i])
	{
		sep_len = is_token_separator(av, *i);
		if (sep_len && !quote)
			break ;
		if (!quote && (av[*i] == '\'' || av[*i] == '"'))
			quote = av[*i];
		else if (quote && av[*i] == quote)
			quote = 0;
		(*i)++;
	}
	if (*i > start)
		return (ft_strndup(av + start, *i - start));
	return (NULL);
}

static t_token	*create_pipe_text(char *av, int *i)
{
	t_token	*new_token;
	char	*temp;

	if (av[*i] == '|' && av[*i + 1] != '|')
	{
		(*i)++;
		return (init_token(TOKEN_PIPE, "|"));
	}
	temp = extract_text_token(av, i);
	if (!temp)
		return (error_msg(MEM, "create_pipe_text"), NULL);
	new_token = init_token(TOKEN_TEXT, temp);
	if (temp)
		free(temp);
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
