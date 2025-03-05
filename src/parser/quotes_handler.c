/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:00:52 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/05 14:45:33 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_toggle_quote(char c, char *quote)
{
	if ((c == '\'' || c == '"') && (*quote == 0 || *quote == c))
	{
		if (*quote == 0)
			*quote = c;
		else if (*quote == c)
			*quote = 0;
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
		return (error_msg(MEM, "remove_quotes"), NULL);
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

char	**quotes_handler(char **args, t_shell *shell)
{
	int		i;
	int		count;
	char	**parsed;
	bool	to_expend;

	i = 0;
	count = ft_tabsize((void **)args);
	parsed = ft_calloc(count + 1, sizeof(char *));
	if (!parsed)
		return (error_msg(MEM, "quotes_handler"), NULL);
	while (i < count)
	{
		to_expend = check_expend(args[i]);
		parsed[i] = remove_quotes(args[i]);
		if (!parsed)
			return (ft_free_tab((void **)parsed), NULL);
		if (to_expend)
			parsed[i] = expension(parsed[i], shell);
		i++;
	}
	return (parsed);
}
