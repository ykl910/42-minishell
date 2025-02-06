/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:20:48 by kyang             #+#    #+#             */
/*   Updated: 2025/02/06 19:30:34 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*get_command_name(int command_type)
{
	if (command_type == COMMAND_AND)
		return ("AND");
	else if (command_type == COMMAND_OR)
		return ("OR");
	else if (command_type == COMMAND_PIPE)
		return ("PIPE");
	else if (command_type == COMMAND_SIMPLE)
		return ("COMMAND");
	else if (command_type == COMMAND_REDIRECT_IN)
		return ("REDIRECT_IN");
	else if (command_type == COMMAND_REDIRECT_OUT)
		return ("REDIRECT_OUT");
	else if (command_type == COMMAND_REDIRECT_APPEND)
		return ("REDIRECT_APPEND");
	else if (command_type == COMMAND_HERE_DOC)
		return ("HERE_DOC");
	else if (command_type == COMMAND_SUBSHELL)
		return ("SUBSHELL");
	else
		return ("UNKNOWN");
}

void	print_ast(t_ast_node *node, int depth)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	while (++i < depth)
		printf("  ");
	if (node->value)
	{
		i = 0;
		printf("%s:", get_command_name(node->node_type));
		while (node->value[i])
		{
			printf("%s ", node->value[i]);
			i++;
		}
		printf("\n");
	}
	else
		printf("%s\n", get_command_name(node->node_type));
	if (node->left)
		print_ast(node->left, depth + 1);
	if (node->right)
		print_ast(node->right, depth + 1);
}

int	main(int ac, char **envp)
{
	char		*line;
	int			i;
	t_token		*tokens;
	t_ast_node	*ast;

	(void)ac;
	(void)envp;
	while (1)
	{
		i = 0;
		line = readline("input prompt > ");
		if (line)
			add_history(line);
		tokens = lexer(line);
		ast = parse_expression(&tokens, 0);
		print_ast(ast, 0);
		free(line);
	}
	return (0);
}
