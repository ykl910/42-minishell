/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:30:25 by kyang             #+#    #+#             */
/*   Updated: 2025/02/26 14:54:28 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_char(char *s, char c)
{
	int		len;
	char	*new_str;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	new_str = (char *)malloc(len + 2);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	return (new_str);
}

static void	expand_variable(char *segment, int *i, t_shell *shell,
		char **expanded)
{
	int		start;
	char	*var_name;
	char	*var_value;
	char	*temp;

	start = *i;
	(*i)++;
	while (ft_isalnum(segment[*i]) || segment[*i] == '_' || segment[*i] == '?')
		(*i)++;
	var_name = ft_strndup(&segment[start], *i - start);
	var_value = variable_expension(var_name, shell);
	if (var_value)
		temp = ft_strjoin(*expanded, var_value);
	else
		temp = ft_strjoin(*expanded, var_name);
	free(*expanded);
	*expanded = temp;
	free(var_name);
	if (var_value)
		free(var_value);
}

static char	*expand_env(char *segment, t_shell *shell)
{
	int		i;
	char	*expanded;
	char	*temp;

	expanded = ft_strdup("");
	i = 0;
	while (segment[i])
	{
		if (segment[i] == '$' && segment[i + 1] && segment[i + 1] > ' ')
			expand_variable(segment, &i, shell, &expanded);
		else
		{
			if (segment[i] != '"')
			{
				temp = ft_strjoin_char(expanded, segment[i]);
				free(expanded);
				expanded = temp;
			}
			i++;
		}
	}
	return (expanded);
}

void	expand_wc(t_token *token)
{
	char		*wc_pattern;
	t_wildcards	*wc_exp;
	char		*temp;
	char		*new_value;
	t_wildcards	*wc_tmp;

	new_value = ft_strdup("");
	wc_pattern = ft_strdup(token->value);
	wc_exp = wildcard_expension(wc_pattern);
	free(wc_pattern);
	free(token->value);
	wc_tmp = wc_exp;
	while (wc_exp)
	{
		temp = ft_strjoin(new_value, wc_exp->file);
		free(new_value);
		new_value = temp;
		temp = ft_strjoin(new_value, " ");
		free(new_value);
		new_value = temp;
		wc_exp = wc_exp->next;
	}
	token->value = new_value;
	free_wildcard(wc_tmp);
}

void	expand_var(t_token *token, t_shell *shell)
{
	char	*temp;

	temp = expand_env(token->value, shell);
	free(token->value);
	token->value = temp;
}
