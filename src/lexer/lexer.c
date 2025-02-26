/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:12:42 by kyang             #+#    #+#             */
/*   Updated: 2025/02/26 14:54:03 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_token(t_token **tokens, t_token **current, t_token *new_token)
{
	if (!new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		*current = *tokens;
	}
	else
	{
		(*current)->next = new_token;
		*current = new_token;
	}
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
		while (av[i] && av[i] <= ' ')
			i++;
		if (!av[i])
			break ;
		new_token = create_token(av, &i);
		new_token->next = NULL;
		add_token(&tokens, &current, new_token);
	}
	return (tokens);
}
