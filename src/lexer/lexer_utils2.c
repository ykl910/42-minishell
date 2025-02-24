/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:34:04 by kyang             #+#    #+#             */
/*   Updated: 2025/02/24 19:07:13 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unclosed(char *av)
{
	int	i;
	int	quote;
	int	par;

	i = 0;
	quote = 0;
	par = 0;
	while (av[i])
	{
		if (av[i] == '(')
			par++;
		else if (av[i] == ')')
			par--;
		else if (!quote && (av[i] == '\'' || av[i] == '"'))
			quote = av[i];
		else if (quote && av[i] == quote)
			quote = 0;
		i++;
	}
	if (par || quote)
		return (error_msg(UNC, NULL), 1);
	return (0);
}
