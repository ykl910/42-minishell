/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:20:48 by kyang             #+#    #+#             */
/*   Updated: 2025/02/25 10:05:49 by kyang            ###   ########.fr       */
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

void	put_command_type(t_shell *shell)
{
	t_token	*current;

	current = shell->token_lst;
	while (current)
	{
		if (current->token_type == TOKEN_PIPE
			|| current->token_type == TOKEN_AND
			|| current->token_type == TOKEN_OR)
		{
			shell->prompt_type = 0;
			return ;
		}
		current = current->next;
	}
	shell->prompt_type = 1;
}

void	print_token(t_token *token)
{
	t_token	*current;
	int		i;

	i = 1;
	current = token;
	while (current)
	{
		printf("%d - %s\n", i, current->value);
		current = current->next;
		i++;
	}
}

char	*get_prompt(int status)
{
	char	*left;
	char	*right;
	char	*num;
	char	*prompt;
	size_t	prompt_size;

	left = ft_strjoin(CYAN "⌬  " RESET, NEON_GREEN "Minishell⌈" RESET);
	if (!left)
		return (error_msg(MEM, "prompt(1)"), NULL);
	right = NEON_GREEN "⌋ $❯ " RESET;
	num = ft_itoa(status);
	if (!num)
		return (error_msg(MEM, "prompt(2)"), free(left), NULL);
	prompt_size = ft_strlen(left) + ft_strlen(right) + ft_strlen(num)
		+ ft_strlen(MAGENTA) + ft_strlen(RESET) + 1;
	prompt = ft_calloc(prompt_size, sizeof(char));
	if (!prompt)
		return (error_msg(MEM, "prompt(3)"), free(left), free(num), NULL);
	ft_strlcat(prompt, left, prompt_size);
	ft_strlcat(prompt, MAGENTA, prompt_size);
	ft_strlcat(prompt, num, prompt_size);
	ft_strlcat(prompt, RESET, prompt_size);
	ft_strlcat(prompt, right, prompt_size);
	return (free(left), free(num), prompt);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	*prompt;
	t_shell	shell;
	t_token	*head;

	(void)ac;
	(void)av;
	shell_init(&shell, envp);
	while (1)
	{
		signals();
		prompt = get_prompt(shell.prev_status);
		line = readline(prompt);
		if (!line)
			input_eof(&line);
		else
		{
			process_signals();
			add_history(line);
			shell.status = check_unclosed(line);
			if (!shell.status)
			{
				shell.token_lst = lexer(line);
				expand_token(&shell.token_lst, &shell);
				free(line);
				shell.status = check_lexer(&shell.token_lst);
				head = shell.token_lst;
				if (shell.status == 0)
				{
					put_command_type(&shell);
					shell.ast = parse_expression(&shell.token_lst, 0, &shell);
					if (!shell.status)
						executor(shell.ast, &shell);
				}
				free_tokens(&head);
			}
			shell.prev_status = shell.status;
		}
		free(prompt);
	}
	return (0);
}
