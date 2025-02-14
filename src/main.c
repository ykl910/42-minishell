/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:20:48 by kyang             #+#    #+#             */
/*   Updated: 2025/02/17 19:03:40 by kyang            ###   ########.fr       */
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
	else if (command_type == COMMAND_SUBSHELL)
		return ("SUBSHELL");
	else
		return ("UNKNOWN");
}

// DEBUG//

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

void	print_wildcard(t_wildcards **head)
{
	t_wildcards	*current;

	current = *head;
	while (current)
	{
		if (current->file)
			ft_printf("%s\n", current->file);
		current = current->next;
	}
}

void	print_type(e_command type)
{
	if (type == COMMAND_SIMPLE)
		ft_printf("CMD ");
	if (type == COMMAND_PIPE)
		ft_printf("| ");
	if (type == COMMAND_AND)
		ft_printf("&& ");
	if (type == COMMAND_OR)
		ft_printf("|| ");
	if (type == COMMAND_SUBSHELL)
		ft_printf("(..) ");
}

void	ast_printer(t_ast_node *root)
{
	if (!root)
		return ;
	ast_printer(root->left);
	print_type(root->node_type);
	ast_printer(root->right);
}
// DEBUG//

void	put_command_type(t_shell *shell)
{
	t_token	*current;

	current = shell->token_lst;
	while (current)
	{
		if (current->token_type == TOKEN_PIPE || current->token_type == TOKEN_AND || \
			current->token_type == TOKEN_OR)
		{
			shell->prompt_type = 0;
			return ;
		}

		current = current->next;
	}
	shell->prompt_type = 1;
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_shell	shell;
	t_token *token;
	char	*new_line;
	(void)ac;
	(void)av;
	shell_init(&shell, envp);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	while (1)
	{
		g_sigint_flag = 0;
		line = readline(CYAN "*  " RESET NEON_GREEN "minishell ~ " RESET);
		if (line)
		{

			add_history(line);
			new_line = expand_line(line, &shell);
			printf("%s\n", new_line);
			shell.token_lst = lexer(new_line);
			check_lexer(&shell.token_lst);
			put_command_type(&shell);
			shell.ast = parse_expression(&shell.token_lst, 0);
			inorder_traversal(shell.ast, &shell); // WIP
			free(line);
		}
	}
	return (0);
}
