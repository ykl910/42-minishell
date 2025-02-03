/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:20:48 by kyang             #+#    #+#             */
/*   Updated: 2025/02/03 15:36:29 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **env)
{
	char	*r;
	(void)	ac;
	(void)	env;
	int		i;
	
	while (1)
	{
		i = 0;
		r = readline("input prompt > ");
		if (r)
			add_history(r);
		while (lexer(r)[i])
		{
			printf("%u - %s\n", lexer(r)[i]->token_type, lexer(r)[i]->value);
			i++;
		}
		free(r);
	}
	return (0);
}

