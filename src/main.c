/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:20:48 by kyang             #+#    #+#             */
/*   Updated: 2025/02/03 17:26:40 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **env)
{
	char	*line;
	int		i;

	(void)ac;
	(void)env;
	while (1)
	{
		i = 0;
		line = readline("input prompt > ");
		if (line)
			add_history(line);
		while (lexer(line)[i])
		{
			printf("%u - %s\n", lexer(line)[i]->token_type,
				lexer(line)[i]->value);
			i++;
		}
		free(line);
	}
	return (0);
}
