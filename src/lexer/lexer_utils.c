/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:53:37 by kyang             #+#    #+#             */
/*   Updated: 2025/03/04 14:15:50 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token(t_tok_enum type, char *av)
{
	t_token	*token;

	token = malloc((sizeof(t_token)));
	if (!token)
		return (NULL);
	token->token_type = type;
	token->value = ft_strdup(av);
	if (!token->value)
	{
		free(token);
		return (ft_putstr_fd("init token malloc error", STDERR_FILENO), NULL);
	}
	return (token);
}

static int	count_redir_text(char *av, int *i)
{
	int	c;

	c = 0;
	if (av[*i] == '<' && av[*i + 1] && av[*i + 1] == '<')
	{
		c++;
		(*i)++;
	}
	else if (av[*i] == '<' && av[*i + 1] && av[*i + 1] != '<')
		c++;
	else if (av[*i] == '>' && av[*i + 1] && av[*i + 1] == '>')
	{
		c++;
		(*i)++;
	}
	else if (av[*i] == '>' && av[*i + 1] && av[*i + 1] != '>')
		c++;
	else if (!ft_issep(av[*i]) && ft_issep(av[*i + 1]))
		c++;
	return (c);
}

static int	count_logical_ops_parantheses(char *av, int *i)
{
	int	c;

	c = 0;
	if (av[*i] == '&' && av[*i + 1] && av[*i + 1] == '&')
	{
		c++;
		(*i)++;
	}
	else if (av[*i] == '|' && av[*i + 1] && av[*i + 1] == '|')
	{
		c++;
		(*i)++;
	}
	else if (av[*i] == '(' || av[*i] == ')')
		c++;
	return (c);
}

int	count_input(char *av)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (av[i])
	{
		c += count_redir_text(av, &i);
		c += count_logical_ops_parantheses(av, &i);
		i++;
	}
	return (c);
}
