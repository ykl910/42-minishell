/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:02:38 by kyang             #+#    #+#             */
/*   Updated: 2025/02/01 19:44:28 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(char *value, char *in_file, char *out_file, char **args)
{
	t_command *command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->value = value;
	command->in_file = in_file;
	command->out_file = out_file;
	command->args = args;
	return (command);
}

char	**append_args()
{
	
}

t_command	**parser(t_token **tokens)
{
	int			i;
	int			j;
	t_command	**commands;

	i = 0;
	while (tokens[i])
		i++;
	commands = malloc(sizeof(t_token *) * (i + 1));
	if (!commands)
		return (NULL);
	i = 0;
	j = 0;
	while (tokens[i + j])
	{
		if (tokens[i + j]->token_type == 5)
			commands[i]->value = tokens[i + j]->value;
		while (tokens[i + j]->token_type != 0)
		{
			if (tokens[i + j]->token_type == 1)
				commands[i]->in_file = tokens[i + 1]->value;
			else if (tokens[i + j]->token_type == 2 || tokens[i + j]->token_type == 4)
				commands[i]->out_file = tokens[i + 1]->value;
			else if (tokens[i + j]->token_type == 5 && !commands[i]->value)
				commands[i]->value = tokens[i + j]->value;
			else
				commands[i]->args = tokens[i + j]->value;
			j++;
		}
		j = 0;
		i++;
	}
}
