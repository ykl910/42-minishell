/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:20:48 by kyang             #+#    #+#             */
/*   Updated: 2025/01/30 17:59:15 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **env)
{
	char	*r;
	(void)	ac;
	(void)	env;
	
	while (1)
	{
		r = readline("input prompt >");
		if (r)
			add_history(r);
		printf("%d\n", count_input(r));
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
