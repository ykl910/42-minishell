/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:12:42 by kyang             #+#    #+#             */
/*   Updated: 2025/02/03 12:02:52 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token(e_token	type, char *av)
{
	t_token	*token;

	token = ft_calloc((sizeof(t_token)), 1);
	if (!token)
		return (NULL);
	token->token_type = type;
	token->value = ft_strdup(av);
	return (token);
}

int	ft_isspace(char c)
{
	if (c == '\f' || c == '\n' || c == '\r' || c == '\t' \
		|| c == '\v' || c == ' ' || c == '\0')
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
		if (!ft_isspace(av[i]) && ft_isspace(av[i + 1]))
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

	i = 0;
	j = 0;
	count = count_input(av);
	tokens = ft_calloc(sizeof(t_token *), count + 1);
	if (!tokens)
		return (NULL);
	while (av[i])
	{
		while (ft_isspace(av[i]))
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
		else if (av[i] == '|')
		{
			tokens[j] = init_token(TOKEN_PIPE, "|");
			i += 1;
		}
		else
		{
			start = i;
			while (!ft_isspace(av[i]) && av[i] != '>' && av[i] != '<' && av[i] != '|')
				i++;
	        tokens[j] = init_token(TOKEN_TEXT, ft_strndup(av + start, i - start));
		}
		j++;
	}
	tokens[j] = NULL;
	return (tokens);
}
