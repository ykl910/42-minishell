/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:30:25 by kyang             #+#    #+#             */
/*   Updated: 2025/02/14 18:30:45 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strjoin_char(char *s, char c)
{
	int len;
	char *new_str;
	int i;

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

void	expand_variable(char *segment, int *i, t_shell *shell, char **expanded)
{
	int start;
	char *var_name;
	char *var_value;
	char *temp;

	start = *i;
	(*i)++;
	while (segment[*i] && segment[*i] != ' ' && segment[*i] != '$' 
		&& segment[*i] != '\'' && segment[*i] != '"')
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

char *expand_env(char *segment, t_shell *shell)
{
	int i;
	char *expanded;
	char *temp;

	expanded = ft_strdup("");
	i = 0;
	while (segment[i])
	{
		if (segment[i] == '$' && segment[i + 1] && segment[i + 1] != ' ')
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

char *expand_wc(char *line, int start, int end, char *new_line)
{
	char		*wc_pattern;
	t_wildcards	*wc_exp;
	char		*temp;

	wc_pattern = ft_strndup(&line[start], end - start);
	wc_exp = wildcard_expension(wc_pattern);
	free(wc_pattern);
	while (wc_exp)
	{
		temp = ft_strjoin(new_line, wc_exp->file);
		free(new_line);
		new_line = temp;
		if (wc_exp->next)
		{
			temp = ft_strjoin(new_line, " ");
			free(new_line);
			new_line = temp;
		}
		wc_exp = wc_exp->next;
	}
	return (new_line);
}
