/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:35:33 by kyang             #+#    #+#             */
/*   Updated: 2025/02/11 20:03:43 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_wc(char *line)
{
	int			i;
	int			start;
	int			wc_flag;
	char		*wc_pattern;
	t_wildcards	*wc_exp;
	char		*wc_expand;
	char		*wc_expands;
	char		*word;
	char		*new_line;
	char		*temp;

	i = 0;
	wc_pattern = NULL;
	new_line = ft_strdup("");
	while (line[i])
	{
		if (line[i] <= ' ' && line[i] != '\0')
			i++;
		start = i;
		wc_flag = 0;
		while (line[i] && line[i] > ' ')
		{
			if (line[i] == '*')
				wc_flag = 1;
			i++;
		}
		if (!wc_flag)
		{
			word = ft_strjoin(ft_strndup(&line[start], i - start), " ");
			temp = ft_strjoin(new_line, word);
			free(new_line);
			new_line = temp;
			free(word);
		}
		else
		{
			wc_expands = ft_strdup("");
			wc_pattern = ft_strndup(&line[start], i - start);
			wc_exp = wildcard_expension(wc_pattern);
			while (wc_exp)
			{
				wc_expand = ft_strjoin(ft_strdup(wc_exp->file), " ");
				temp = ft_strjoin(wc_expands, wc_expand);
				free(wc_expands);
				wc_expands = temp;
				free(wc_expand);
				wc_exp = wc_exp->next;
			}
			temp = ft_strjoin(new_line, wc_expands);
			free(new_line);
			new_line = temp;
			free(wc_expands);
			free(wc_pattern);
		}
	}
	return (new_line);
}
