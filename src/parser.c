/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:02:38 by kyang             #+#    #+#             */
/*   Updated: 2025/02/03 18:37:16 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->in_file = NULL;
	command->out_file = NULL;
	command->name = NULL;//ft_calloc(1, sizeof(char *));
	// if (!command->name)
	// 	return (ft_putstr_fd("malloc error init_command\n", STDERR_FILENO), NULL);
	return (command);
}

char	**append_args(char **origin_args, char *new_arg)
{
	char	**new_args;
	int		i;

	i = 0;
	while (origin_args[i])
		i++;
	new_args = ft_calloc((i + 2), sizeof(char *));
	if (!new_args)
		return (NULL);
	i = 0;
	while (origin_args[i])
	{
		new_args[i] = ft_strdup(origin_args[i]);
		if (!new_args[i])
			return (ft_putstr_fd("malloc error app.arg\n", STDERR_FILENO), NULL);
		free(origin_args[i]);
		i++;
	}
	free(origin_args);
	new_args[i] = ft_strdup(new_arg);
	if (!new_args[i])
		return (ft_putstr_fd("malloc error at app.args\n", STDERR_FILENO), NULL);
	return (new_args);
}

t_command	**parser(t_token **tokens)
{
	int			i;
	int			j;
	t_command	**commands;

	i = 0;
	while (tokens[i])
		i++;
	printf("%d",i);
	commands = ft_calloc((i + 1), sizeof(t_command *));
	if (!commands)
		return (ft_putstr_fd("malloc error at parsing1\n", STDERR_FILENO), NULL);
	i = 0;
	j = 0;
	while (tokens[i + j])
	{
		commands[i] = init_command();
		if (!commands[i])
			return (ft_putstr_fd("malloc error at parsing1\n", STDERR_FILENO), NULL);
		while (tokens[i + j]->token_type != 0)
		{
			if (tokens[i + j]->token_type == 5)
			{
				if (!commands[i]->name)
				{
					commands[i]->name[j] =  ft_strdup(tokens[i + j]->value);
					if (!commands[i]->name[j])
						return (ft_putstr_fd("malloc error at parsing1\n", STDERR_FILENO), NULL);
				}
				else
					commands[i]->name = append_args(commands[i]->name, tokens[i + j]->value);
			}
			else if (tokens[i + j]->token_type == 1)
			{
				if (tokens[i + j + 1])
				{
					commands[i]->in_file = tokens[i + j + 1]->value;
					j++;
				}
			}
			else if (tokens[i + j]->token_type == 2
			|| tokens[i + j]->token_type == 4)
			{
				if (tokens[i + j + 1])
				{
					commands[i]->out_file = tokens[i + j + 1]->value;
					j++;					
				}
			}
			j++;
		}
		j = 0;
		i++;
	}
	commands[i] = NULL;
	return (commands);
}
