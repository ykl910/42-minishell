/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:07:14 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/05 14:46:49 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_new(char *str, char *expended, int i, int sub_len)
{
	char	*new;
	int		len_str;
	int		len_exp;

	len_str = ft_strlen(str);
	len_exp = ft_strlen(expended);
	new = ft_calloc(len_str - sub_len + len_exp + 1, sizeof(char));
	if (!new)
		return (error_msg(MEM, "create_new"), NULL);
	ft_memcpy(new, str, i - sub_len);
	ft_memcpy(new + (i - sub_len), expended, len_exp);
	ft_memcpy(new + (i - sub_len) + len_exp, &str[i], len_str - i);
	return (new);
}

static char	*extract_var(char *str, int *i)
{
	int		sub_len;
	char	*sub_p;

	sub_len = 0;
	while (str[*i] && str[*i] != '\"' && str[*i] != '\'')
	{
		sub_len++;
		(*i)++;
	}
	sub_p = ft_strndup(&str[*i - sub_len], sub_len);
	return (sub_p);
}

static int	skip_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '\"' || str[i] == '\''))
		i++;
	return (i);
}

char	*expension(char *str, t_shell *shell)
{
	char	*expended;
	char	*new;
	char	*sub_p;
	int		i;

	i = skip_quotes(str);
	sub_p = extract_var(str, &i);
	if (!sub_p)
		return (error_msg(MEM, "extract_var"), str);
	expended = variable_expension(sub_p, shell);
	free(sub_p);
	if (!expended)
		return (str);
	new = create_new(str, expended, i, i - skip_quotes(str));
	return (free(expended), free(str), new);
}

bool	check_expend(char *str)
{
	int		i;
	bool	in_squote;
	bool	in_dquote;

	i = 0;
	in_squote = false;
	in_dquote = false;
	while (str[i])
	{
		if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		else if (str[i] == '$' && (!in_squote || (i > 0 && str[i - 1] == '\''
					&& str[i + 1] == '\'')))
		{
			if (isalnum(str[i + 1]) || str[i + 1] == '_')
				return (true);
		}
		i++;
	}
	return (false);
}
