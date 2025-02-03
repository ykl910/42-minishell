/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:02:38 by kyang             #+#    #+#             */
/*   Updated: 2025/02/03 15:33:27 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->name = NULL;
	command->in_file = NULL;
	command->out_file = NULL;
	command->args = ft_calloc(1, sizeof(char *));
	if (!command->args)
		return (NULL);
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
		if (!new_arg[i])
			return (ft_putstr_fd("malloc error app.arg", STDERR_FILENO), NULL);
		free(origin_args[i]);
		i++;
	}
	new_args[i] = ft_strdup(new_arg);
	if (!new_arg[i])
		return (ft_putstr_fd("malloc error at app.args", STDERR_FILENO),
			NULL);
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
	commands = ft_calloc((i + 1), sizeof(t_command *));
	if (!commands)
		return (NULL);
	i = 0;
	j = 0;
	while (tokens[i + j])
	{
		commands[i] = ft_calloc(1, sizeof(t_command));
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
				commands[i]->args = calloc(1, sizeof(char *));
				if (commands[i]->args)
					return (NULL);
			}
			if (tokens[i + j]->token_type == 1)
				commands[i]->in_file = tokens[i + 1]->value;
			else if (tokens[i + j]->token_type == 2 || tokens[i
				+ j]->token_type == 4)
				commands[i]->out_file = tokens[i + 1]->value;
			else if (tokens[i + j]->token_type == 5 && !commands[i]->name)
				commands[i]->name = tokens[i + j]->value;
			else
				commands[i]->args = append_args(commands[i]->args, tokens[i
						+ j]->value);
			j++;
		}
		j = 0;
		i++;
	}
	return (commands);
}
