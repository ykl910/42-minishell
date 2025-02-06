/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:20:48 by kyang             #+#    #+#             */
/*   Updated: 2025/02/06 12:45:15 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//debug function(s)//
static void	print_token_lst(t_token **tkn_lst)
{
	int	i;

	i = 0;
	while (tkn_lst[i])
	{
		ft_printf("type: %u value: %s\n", tkn_lst[i]->token_type,
			tkn_lst[i]->value);
		i++;
	}
}

// int	main(int ac, char **envp)
// {
// 	char		*line;
// 	t_token		**tokens;
// 	t_command	*current;

// 	(void)ac;
// 	(void)envp;
// 	while (1)
// 	{
// 		line = readline("input prompt > ");
// 		if (line)
// 			add_history(line);
// 		tokens = lexer(line);
// 		print_token_lst(tokens);
// 		current = parser(tokens);
// 		if (!current)
// 			return (ft_putstr_fd("malloc error at parsing1\n", STDERR_FILENO),
// 				0);
// 		while (current)
// 		{
// 			printf("Command: %d -> ", current->index);
// 			if (current->name)
// 			{
// 				for (int i = 0; current->name[i]; i++)
// 					printf("%s ", current->name[i]);
// 			}
// 			printf("\n");
// 			if (current->in_file)
// 				printf("Input file: %s\n", current->in_file);
// 			if (current->out_file)
// 				printf("Output file: %s\n", current->out_file);
// 			printf("----------\n");
// 			current = current->next;
// 		}
// 		free(line);
// 	}
// 	return (0);
// }

int	main(int ac, char **envp)
{
	char		*line;
	t_token		**tokens;

	(void)ac;
	(void)envp;
	while (1)
	{
		line = readline("input prompt > ");
		if (line)
			add_history(line);
		tokens = lexer(line);
		print_token_lst(tokens);
		free(line);
	}
	return (0);
}
