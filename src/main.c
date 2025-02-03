/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:20:48 by kyang             #+#    #+#             */
/*   Updated: 2025/02/03 18:45:16 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **env)
{
	char	*line;
	int		i;
	t_token	**tokens;
	t_command **commands;

	(void)ac;
	(void)env;
	while (1)
	{
		i = 0;
		line = readline("input prompt > ");
		if (line)
			add_history(line);
		tokens = lexer(line);
		while (tokens[i])
		{
			printf("%u - %s\n", tokens[i]->token_type,
				tokens[i]->value);
			i++;
		}
		// commands = parser(tokens);
		// if (!commands)
		// 	return (ft_putstr_fd("malloc error at parsing1\n", STDERR_FILENO), 0);
		// i = 0;
		// while (commands[i])
		// {
		// 	printf("dew");
		// 	i++;			
		// }
		free(line);
	}
	return (0);
}
