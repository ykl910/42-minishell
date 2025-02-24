/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:20:48 by kyang             #+#    #+#             */
/*   Updated: 2025/02/24 14:44:13 by alacroix         ###   ########.fr       */
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

////////////

char	*get_prompt(int status)
{
	char	*left_part;
	char	*right_part;
	char	*number;
	char	*prompt;
	size_t	prompt_size;

	left_part = ft_strjoin(CYAN "⌬  " RESET, NEON_GREEN "Minishell ⌈" RESET);
	right_part = NEON_GREEN "⌋ ❯ " RESET;
	number = ft_itoa(status);
	if (!number)
		return (free(left_part), "minishell ❯ ");
	prompt_size = ft_strlen(left_part) + ft_strlen(right_part)
		+ ft_strlen(number) + ft_strlen(MAGENTA) + ft_strlen(RESET) + 1;
	prompt = ft_calloc(prompt_size, sizeof(char));
	if (!prompt)
		return (free(left_part), free(number), "minishell ❯ ");
	ft_strlcat(prompt, left_part, prompt_size);
	ft_strlcat(prompt, MAGENTA, prompt_size);
	ft_strlcat(prompt, number, prompt_size);
	ft_strlcat(prompt, RESET, prompt_size);
	ft_strlcat(prompt, right_part, prompt_size);
	return (free(left_part), free(number), prompt);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	*prompt;
	t_shell	shell;

	(void)ac;
	(void)av;
	shell_init(&shell, envp);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	while (1)
	{
		g_sigint_flag = 0;
		prompt = get_prompt(shell.prev_status);
		line = readline(prompt);
		if (line)
		{
			add_history(line);
			shell.status = check_unclosed(line);
			if (!shell.status)
			{
				shell.token_lst = lexer(line);
				expand_token(&shell.token_lst, &shell);
				free(line);
				shell.status = check_lexer(&shell.token_lst, &shell);
				if (shell.status == 0)
				{
					put_command_type(&shell);
					shell.ast = parse_expression(&shell.token_lst, 0, &shell);
					if (!shell.status)
						executor(shell.ast, &shell);
				}
			free_tokens(&shell.token_lst);
			}
			shell.prev_status = shell.status;
		}
		free(prompt);
	}
	return (0);
}
