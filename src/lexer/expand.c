/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:35:33 by kyang             #+#    #+#             */
/*   Updated: 2025/02/14 18:40:42 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_line(char *line, t_shell *shell)
{
	int i;
	int start;
	int wc_flag;
	int var_flag;
	char quote;
	char *new_line;
	char *temp;
	char *env_temp;
	char *word;

	quote = 0;
	new_line = ft_strdup("");
	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] <= ' ' && quote == 0)
			i++;
		start = i;
		wc_flag = 0;
		var_flag = 0;
		while (line[i] && (quote || line[i] > ' '))
		{
			if ((line[i] == '"' || line[i] == '\'') && (quote == 0 || quote == line[i]))
			{
				if (!quote)
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
			char *segment = ft_strndup(&line[start], i - start);
			temp = expand_env(segment, shell);
			free(segment);
			env_temp = ft_strjoin(new_line, temp);
			free(new_line);
			new_line = env_temp;
		}
		else if (wc_flag)
			new_line = expand_wc(line, start, i, new_line);
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
