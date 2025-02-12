/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:35:33 by kyang             #+#    #+#             */
/*   Updated: 2025/02/12 12:01:52 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_line(char *line, t_shell *shell)
{
	int i;
	int	start;
	char quote;
	char *new_line;
	char *temp;
	char *word;
	char *wc_pattern;
	char *var_value;
	t_wildcards *wc_exp;

	quote = 0;
	new_line = ft_strdup("");
	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] <= ' ' && quote == 0)
			i++;
		start = i;
		int wc_flag = 0, var_flag = 0;
		while (line[i] && (quote || line[i] > ' '))
		{
			if ((line[i] == '"' || line[i] == '\'') && (quote == 0 || quote == line[i]))
			{
				if (quote == 0)
					quote = line[i];
				else
					quote = 0;
				i++;
				continue;
			}
			if (line[i] == '*' && quote == 0)
				wc_flag = 1;
			if (line[i] == '$' && quote != '\'')
				var_flag = 1;
			i++;
		}
		if (var_flag && line[i - 1] == '"')
			start++;
		if (i == start)
			continue;
		if (var_flag)
		{
			char *var_name = ft_strndup(&line[start], i - start);
			var_value = variable_expension(var_name, shell);
			if (var_value)
				temp = ft_strjoin(new_line, var_value);
			else
				temp = ft_strjoin(new_line, var_name);
			free(new_line);
			new_line = temp;
			free(var_name);
			if (var_value)
				free(var_value);
		}
		else if (wc_flag)
		{
			wc_pattern = ft_strndup(&line[start], i - start);
			wc_exp = wildcard_expension(wc_pattern);
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
			free(wc_pattern);
		}
		else
		{
			word = ft_strndup(&line[start], i - start);
			temp = ft_strjoin(new_line, word);
			free(new_line);
			new_line = temp;
			free(word);
		}
		if (line[i] != '\0' && quote == 0)
		{
			temp = ft_strjoin(new_line, " ");
			free(new_line);
			new_line = temp;
		}
	}
	return (new_line);
}
