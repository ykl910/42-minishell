/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:20:48 by kyang             #+#    #+#             */
/*   Updated: 2025/01/29 18:06:01 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*r;
	
	r = readline("input prompt >");
	
	//printf("$> %s", r);
	built_in_command(r);
	//execute_command(r, env);
	return (0);
}

// void	execute_command(char *av, char **env)
// {
// 	pid_t	pid;
// 	char	**argv_c;

// 	pid = fork();
// 	if (pid == -1)
// 		error();
// 	else if (pid == 0)
// 	{
// 		argv_c = exec_args(av[1], env);
// 		if (execve(argv_c[0], argv_c, env) == -1)
// 			error();
// 	}
// 	else if (pid > 0)
// 	{
// 		wait(NULL);
// 	}
// }

void	built_in_command(char *r)
{
	char **av;
	
	av = ft_split(r, ' ');
	if (ft_strncmp(av[0], "cd", 3) == 0)
	{
		if (av[1] == NULL)
			error();
		else if (chdir(av[1]) != 0)
		{
			error();
		}
	}
	printf("you are at %s",av[1]);
}