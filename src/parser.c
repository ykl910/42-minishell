/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:02:38 by kyang             #+#    #+#             */
/*   Updated: 2025/01/31 16:08:22 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(char *value, char *in_file, char *out_file, char *args)
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

// t_command	**parser(t_token **tokens)
// {
// 	int			i;
// 	t_command	**commands;

// 	i = 0;
// 	while (tokens[i])
// 		i++;
// 	commands = malloc(sizeof(t_token *) * (i + 1));
// 	if (!commands)
// 		return (NULL);
	
// }