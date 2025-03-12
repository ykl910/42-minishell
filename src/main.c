/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:20:48 by kyang             #+#    #+#             */
/*   Updated: 2025/03/12 10:54:52 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_status = 0;

static char	*get_prompt(int status)
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

static void	run_shell(char *line, t_shell *shell)
{
	t_token	*head;

	head = NULL;
	process_signals();
	add_history(line);
	(*shell).status = check_unclosed(line);
	if (!(*shell).status)
	{
		(*shell).token_lst = lexer(line);
		expand_token(&(*shell).token_lst, &(*shell));
		free(line);
		(*shell).status = check_lexer(&(*shell).token_lst);
		if ((*shell).status)
			free_tokens(&(*shell).token_lst);
		head = (*shell).token_lst;
		if ((*shell).status == 0)
		{
			(*shell).ast = parse_expression(&(*shell).token_lst, 0, &(*shell));
			free_tokens(&head);
			if (!(*shell).status)
				executor(&(*shell).ast, &(*shell));
		}
	}
	(*shell).prev_status = (*shell).status;
}

static char	*get_input(t_shell *shell)
{
	char	*input;

	if (isatty(STDIN_FILENO))
	{
		shell->prompt = get_prompt(shell->prev_status);
		input = readline(shell->prompt);
		if (g_exit_status == 130)
		{
			shell->prev_status = 130;
			g_exit_status = 0;
		}
		return (input);
	}
	else
		return (get_next_line(0));
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_shell	shell;

	(void)ac;
	(void)av;
	shell_init(&shell, envp);
	while (1)
	{
		signals();
		if (g_exit_status == 130)
		{
			shell.prev_status = 130;
			g_exit_status = 0;
			continue ;
		}
		line = get_input(&shell);
		if (!line && isatty(STDIN_FILENO))
			input_eof(&line, &shell);
		else if (!line && !isatty(STDIN_FILENO))
			break ;
		else
			run_shell(line, &shell);
		free(shell.prompt);
	}
	return (0);
}
