/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:12:42 by kyang             #+#    #+#             */
/*   Updated: 2025/02/04 17:22:30 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token(e_token type, char *av)
{
	t_token	*token;

	token = ft_calloc(1, (sizeof(t_token)));
	if (!token)
		return (NULL);
	token->token_type = type;
	token->value = ft_strdup(av);
	if (!token->value)
		return (ft_putstr_fd("init token malloc error", STDERR_FILENO), NULL);
	return (token);
}

int	ft_issep(char c)
{
	if (c <= ' ' || c == '>' || c == '<' || c == '|' || c == '&' || c == '(' || c == ')')
		return (1);
	return (0);
}

int	count_input(char *av)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (av[i])
	{
		if (av[i] == '|' && av[i + 1] && av[i + 1] != '|')
			c++;
		else if (av[i] == '<' && av[i + 1] && av[i + 1] == '<')
		{
			c++;
			i++;
		}
		else if (av[i] == '<' && av[i + 1] && av[i + 1] != '<')
			c++;
		else if (av[i] == '>' && av[i + 1] && av[i + 1] == '>')
		{
			c++;
			i++;
		}
		else if (av[i] == '>' && av[i + 1] && av[i + 1] != '>')
			c++;
		else if (av[i] == '&' && av[i + 1] && av[i + 1] == '&')
		{
			c++;
			i++;
		}
		else if (av[i] == '|' && av[i + 1] && av[i + 1] == '|')
		{
			c++;
			i++;
		}
		else if (av[i] == '(')
			c++;
		else if (av[i] == ')')
			c++;
		else if (!ft_issep(av[i]) && ft_issep(av[i + 1]))
			c++;
		i++;
	}
	return (c);
}

t_token	**lexer(char *av)
{
	t_token	**tokens;
	int		count;
	int		i;
	int		j;
	int		start;
	char	quote;

	i = 0;
	j = 0;
	// expand_env_variable(av);
	count = count_input(av);
	printf("%d",count);
	tokens = ft_calloc(count + 1, sizeof(t_token *));
	if (!tokens)
		return (ft_putstr_fd("lexer calloc", STDERR_FILENO), NULL);
	while (av[i])
	{
		while (av[i] <= ' ')
			i++;
		if (av[i] == '<' && av[i + 1] == '<')
		{
			tokens[j] = init_token(TOKEN_HERE_DOC, "<<");
			i += 2;
		}
		else if (av[i] == '>' && av[i + 1] == '>')
		{
			tokens[j] = init_token(TOKEN_REDIRECT_APPEND, ">>");
			i += 2;
		}
		else if (av[i] == '<' && av[i + 1] != '<')
		{
			tokens[j] = init_token(TOKEN_REDIRECT_IN, "<");
			i += 1;
		}
		else if (av[i] == '>' && av[i + 1] != '<')
		{
			tokens[j] = init_token(TOKEN_REDIRECT_OUT, ">");
			i += 1;
		}
		else if (av[i] == '|' && av[i + 1] != '|')
		{
			tokens[j] = init_token(TOKEN_PIPE, "|");
			i += 1;
		}
		else if (av[i] == '&' && av[i + 1] == '&')
		{
			tokens[j] = init_token(TOKEN_AND, "&&");
			i += 2;
		}
		else if (av[i] == '|' && av[i + 1] == '|')
		{
			tokens[j] = init_token(TOKEN_OR, "||");
			i += 2;
		}
		else if (av[i] == '(')
		{
			tokens[j] = init_token(TOKEN_LPAREN, "(");
			i += 1;
		}
		else if (av[i] == ')')
		{
			tokens[j] = init_token(TOKEN_RPAREN, ")");
			i += 1;
		}
		else
		{
			start = i;
			quote = 0;
			while (av[i] && (!ft_issep(av[i]) || quote))
			{
				if (!quote && (av[i] == '\'' || av[i] == '"'))
					quote = av[i];
				else if (quote && av[i] == quote)
					quote = 0;
				i++;
			}
			tokens[j] = init_token(TOKEN_TEXT, ft_strndup(av + start, i - start));
		}
		j++;
	}
	tokens[j] = NULL;
	return (tokens);
}
