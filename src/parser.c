/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:02:38 by kyang             #+#    #+#             */
/*   Updated: 2025/02/03 12:05:38 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command()
{
	t_command *command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->name = NULL;
	command->in_file = NULL;
	command->out_file = NULL;
	command->args = NULL;
	return (command);
}

char	**append_args(char **origin_args, char *new_arg)
{
	char	**new_args;
	int	i;

	i = 0;
	while (origin_args[i])
		i++;
	new_args = ft_calloc(sizeof(char *), (i + 1));
	if (!new_args)
		return (NULL);
	i = 0;
	while (origin_args[i])
	{
		new_args[i] = ft_strdup(origin_args[i]);
		free(origin_args[i]);
		i++;
	}
	new_args[i] = ft_strdup(new_arg);
	return (new_args);
}

// first token is command or redirection
// the token after redirection is a file


t_command	**parser(t_token **tokens)
{
	int			i;
	int			j;
	t_command	**commands;

	i = 0;
	while (tokens[i])
		i++;
	commands = ft_calloc(sizeof(t_command *), (i + 1));
	if (!commands)
		return (NULL);
	i = 0;
	j = 0;
	while (tokens[i + j])
	{
		commands[i] = ft_calloc(sizeof(t_command), 1);
		if (!commands[i])
			return (NULL);
		if (tokens[i + j]->token_type == 5)
		{
			commands[i]->name = tokens[i + j]->value;
			j++;
		}
		while (tokens[i + j]->token_type != 0)
		{
			if (!commands[i]->args)
			{
				commands[i]->args = calloc(sizeof(char *), 1);
				if (commands[i]->args)
					return (NULL);
			}
				
			if (tokens[i + j]->token_type == 1)
				commands[i]->in_file = tokens[i + 1]->value;
			else if (tokens[i + j]->token_type == 2 || tokens[i + j]->token_type == 4)
				commands[i]->out_file = tokens[i + 1]->value;
			else if (tokens[i + j]->token_type == 5 && !commands[i]->name)
				commands[i]->name = tokens[i + j]->value;
			else
				commands[i]->args = append_args(commands[i]->args, tokens[i + j]->value);
			j++;
		}
		j = 0;
		i++;
	}
	return (commands);
}
