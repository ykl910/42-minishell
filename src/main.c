/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:20:48 by kyang             #+#    #+#             */
/*   Updated: 2025/02/01 18:32:27 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **env)
{
	char	*r;
	(void)	ac;
	(void)	env;
	int		i;
	
	while (1)
	{
		i = 0;
		r = readline("input prompt > ");
		if (r)
			add_history(r);
		while (lexer(r)[i])
		{
			//if (lexer(r)[i]->token_type == )
			printf("%u - %s\n", lexer(r)[i]->token_type, lexer(r)[i]->value);
			i++;
		}
		//execute_command(r, env);
		free(r);
	}
	return (0);
}

void	execute_command(char *av, char **env)
{
	pid_t	pid;
	char	**argv_c;

	pid = fork();
	if (pid == -1)
		error();
	else if (pid == 0)
	{
		argv_c = exec_args(av);
		if (execve(argv_c[0], argv_c, env) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}	
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
}
