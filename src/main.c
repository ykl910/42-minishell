/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:20:48 by kyang             #+#    #+#             */
/*   Updated: 2025/02/11 17:02:32 by alacroix         ###   ########.fr       */
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
	// else if (command_type == COMMAND_REDIRECT_IN)
	// 	return ("REDIRECT_IN");
	// else if (command_type == COMMAND_REDIRECT_OUT)
	// 	return ("REDIRECT_OUT");
	// else if (command_type == COMMAND_REDIRECT_APPEND)
	// 	return ("REDIRECT_APPEND");
	// else if (command_type == COMMAND_HERE_DOC)
	// 	return ("HERE_DOC");
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
	if(type == COMMAND_SIMPLE)
		ft_printf("CMD ");
	if(type == COMMAND_PIPE)
		ft_printf("| ");
	if(type == COMMAND_AND)
		ft_printf("&& ");
	if(type == COMMAND_OR)
		ft_printf("|| ");
	if(type == COMMAND_SUBSHELL)
		ft_printf("(..) ");
}

void	ast_printer(t_ast_node *root)
{
	if (!root)
		return ;
	mega_printer(root->left);
	print_type(root->node_type);
	mega_printer(root->right);
}
// DEBUG//

void struct_init(t_shell *shell)
{
	shell->ast = NULL;
	shell->shell_env = NULL;
	shell->token_lst = NULL;
	shell->status = 0;
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_shell	shell;
	t_token	*token;

	(void)ac;
	(void)av;
	struct_init(&shell);
	import_env(&shell.shell_env, envp, &shell.status);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	while (1)
	{
		g_sigint_flag = 0;
		line = readline("input prompt > ");
		if (line)
		{
			add_history(line);
			shell.token_lst = lexer(line);
			token = shell.token_lst;
			while (token)
			{
				printf("type %u - value %s\n", token->token_type, token->value);
				token = token->next;
			}
			check_lexer(&shell.token_lst);
			shell.ast = parse_expression(&shell.token_lst, 0);
			free(line);
		}
	}
	return (0);
}
