/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:20:48 by kyang             #+#    #+#             */
/*   Updated: 2025/02/05 17:14:27 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **envp)
{
	char	*line;
	int		i;
	t_token	**tokens;
	t_command *current;

	(void)ac;
	(void)envp;
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
		current = parser(tokens);
		if (!current)
			return (ft_putstr_fd("malloc error at parsing1\n", STDERR_FILENO), 0);
		i = 0;
		while (current)
		{
			printf("Command: %d -> ",current->index);
			if (current->name)
			{
				for (int i = 0; current->name[i]; i++)
					printf("%s ", current->name[i]);
			}
			printf("\n");
			if (current->in_file)
				printf("Input file: %s\n", current->in_file);
			if (current->out_file)
				printf("Output file: %s\n", current->out_file);
			printf("----------\n");
			current = current->next;
		}
		free(line);
	}
	return (0);
}
