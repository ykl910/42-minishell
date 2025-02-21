/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:00:52 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/21 12:04:06 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_toggle_quote(char c, char *quote)
{
	if ((c == '\'' || c == '"') && (*quote == 0 || *quote == c))
	{
		if (*quote == 0)
			*quote = c;
		else
			quote = 0;
		return (1);
	}
	return (0);
}

static char	*remove_quotes(char *str)
{
	size_t	i;
	size_t	j;
	char	quote;
	char	*res;

	i = 0;
	j = 0;
	quote = 0;
	res = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (!skip_toggle_quote(str[i], &quote))
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	return (res);
}

static size_t	tab_size(char **tab) // a rajouter a la libft
{
	size_t i;

	i = 0;
	if (!*tab || !tab)
		return (i);
	while (tab[i])
		i++;
	return (i);
}

char	**quotes_handler(char **args)
{
	size_t	i;
	size_t	count;
	char	**parsed;

	i = 0;
	count = tab_size(args);
	parsed = ft_calloc(count + 1, sizeof(char *));
	if (!parsed)
		return (NULL);
	while (i < count)
	{
		parsed[i] = remove_quotes(args[i]);
		if (!parsed)
			return (ft_free_tab((void **)parsed), NULL);
		i++;
	}
	return (parsed);
}
