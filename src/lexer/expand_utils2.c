/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:30:25 by kyang             #+#    #+#             */
/*   Updated: 2025/02/27 18:17:17 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_expanded_wildcards(t_wildcards *wc_exp)
{
	char	*new_value;
	char	*temp;

	new_value = ft_calloc(1, sizeof(char));
	if (!new_value)
		return (error_msg(MEM, "join_expanded_wildcards"), NULL);
	while (wc_exp)
	{
		if (is_not_hidden_file(wc_exp->file))
		{
			temp = ft_strjoin(new_value, wc_exp->file);
			if (!temp)
				return (error_msg(MEM, "join_expanded_wildcards"), NULL);
			free(new_value);
			new_value = temp;
			temp = ft_strjoin(new_value, " ");
			if (!temp)
				return (error_msg(MEM, "join_expanded_wildcards"), NULL);
			free(new_value);
			new_value = temp;
		}
		wc_exp = wc_exp->next;
	}
	return (new_value);
}

void	expand_wc(t_token *token)
{
	char		*wc_pattern;
	t_wildcards	*wc_exp;
	t_wildcards	*wc_tmp;

	wc_pattern = ft_strdup(token->value);
	if (!wc_pattern)
		return (error_msg(MEM, "expand_wc"));
	wc_exp = wildcard_expension(wc_pattern);
	free(wc_pattern);
	if (!wc_exp)
	{
		error_msg(RED WC RESET, token->value);
		return ;
	}
	free(token->value);
	wc_tmp = wc_exp;
	token->value = join_expanded_wildcards(wc_exp);
	free_wildcard(wc_tmp);
}
