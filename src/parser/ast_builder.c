/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:33:09 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/06 15:57:12 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_arg(t_token *token_lst, int *token_index)
{
	int		i;
	char	**args;

	i = 0;
	args = NULL;
	while (token_lst[*token_index + i].token_type == TOKEN_TEXT)
		i++;
	args = ft_calloc(i + 1, sizeof(char));
	if (!args)
		return (NULL);
	i = 0;
	while (token_lst[*token_index].token_type == TOKEN_TEXT)
	{
		args[i] = ft_strdup(token_lst[*token_index].token_type);
		if (!args[i])
			return (ft_free_tab((void **)args), NULL);
		(*token_index)++;
		i++;
	}
	return (args);
}

static t_ast	*parse_cmd(t_token *token_lst, int *token_index)
{
}

static t_ast	*parse_pipe(t_token *token_lst, int *token_index)
{
}

static t_ast	*parse_logic_operator(t_token *token_lst, int *token_index)
{
}

t_ast	*parser(t_token *token_lst)
{
	int	token_index;

	token_index = 0;
	return (parse_logic_operator(token_lst, &token_index));
}
