/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:20:31 by kyang             #+#    #+#             */
/*   Updated: 2025/03/04 17:09:18 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_text(t_token *token, int *wc_flag, int *var_flag)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (token->value[i] && (quote || token->value[i] > ' '))
	{
		if ((token->value[i] == '"' || token->value[i] == '\'') && (quote == 0
				|| quote == token->value[i]))
		{
			if (!quote)
				quote = token->value[i];
			else
				quote = 0;
			i++;
			continue ;
		}
		if (token->value[i] == '*' && quote == 0)
			*wc_flag = 1;
		if (token->value[i] == '$' && quote != '\'')
			*var_flag = 1;
		i++;
	}
}

static void	insert_wc_expand(char **temp, int i, t_token **last_new)
{
	t_token	*new_token;

	new_token = NULL;
	while (temp[i])
	{
		new_token = init_token(TOKEN_TEXT, temp[i]);
		if (!new_token)
			return (error_msg(MEM, "insert_wc_expand"));
		(*last_new)->next = new_token;
		*last_new = new_token;
		i++;
	}
}

static void	single_expand(t_token **current)
{
	char	**temp;
	int		i;
	t_token	*last_new;
	t_token	*next_token;

	if (!(*current)->value)
		return ;
	if ((*current)->value[0] != '\'' && (*current)->value[0] != '"')
	{
		temp = ft_split((*current)->value, ' ');
		free((*current)->value);
		(*current)->value = ft_strdup(temp[0]);
		if (!(*current)->value)
			return (error_msg(MEM, "single_expand"));
		last_new = (*current);
		next_token = (*current)->next;
		i = 1;
		insert_wc_expand(temp, i, &last_new);
		last_new->next = next_token;
		ft_free_tab((void **)temp);
		(*current) = next_token;
	}
	else
		(*current) = (*current)->next;
}

static void	final_expansion(t_token **token)
{
	t_token	*current;

	current = *token;
	while (current)
	{
		if (current->token_type == TOKEN_TEXT)
			single_expand(&current);
		else
			current = current->next;
	}
}

void	expand_token(t_token **token, t_shell *shell)
{
	t_token	*current;
	int		wc_flag;
	int		var_flag;

	current = *token;
	while (current)
	{
		wc_flag = 0;
		var_flag = 0;
		if (current->token_type == TOKEN_TEXT)
		{
			expand_text(current, &wc_flag, &var_flag);
			if (wc_flag)
				expand_wc(current);
			if (var_flag)
				expand_var(current, shell);
		}
		current = current->next;
	}
	final_expansion(token);
}
