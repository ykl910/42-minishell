/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:02:38 by kyang             #+#    #+#             */
/*   Updated: 2025/02/05 17:19:21 by kyang            ###   ########.fr       */
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
	command->name = NULL;
	command->index = -1;
	command->next = NULL;
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

int		count_commands(t_token **tokens)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while (tokens[i])
	{
		if (tokens[i]->token_type == 0)
			count++;
		i++;
	}
	return (count);
}

// t_command	*parser(t_token **tokens)
// {
// 	int			i;
// 	int			j;
// 	int			index;
// 	t_command	*head;
// 	t_command	*current;
// 	t_command	*new_cmd;

// 	i = 0;
// 	j = 0;
// 	index = 0;
// 	head = NULL;
// 	current = NULL;

// 	while (tokens[i + j])
// 	{
// 		new_cmd = init_command();
// 		if (!new_cmd)
// 			return (ft_putstr_fd("malloc error at parsing\n", STDERR_FILENO), NULL);
// 		if (!head)
// 			head = new_cmd;
// 		else
// 			current->next = new_cmd;
// 		current = new_cmd;
// 		current->index = index;
// 		while (tokens[i + j] && tokens[i + j]->token_type != 0)
// 		{
// 			if (tokens[i + j]->token_type == 9)
// 			{
// 				if (!new_cmd->name)
// 				{
// 					new_cmd->name = ft_calloc(2, sizeof(char *));
// 					if (!new_cmd->name)
// 						return (ft_putstr_fd("malloc error at parsing\n", STDERR_FILENO), NULL);
// 					new_cmd->name[0] = ft_strdup(tokens[i + j]->value);
// 					if (!new_cmd->name[0])
// 						return (ft_putstr_fd("malloc error at parsing\n", STDERR_FILENO), NULL);
// 					new_cmd->name[1] = NULL;
// 				}
// 				else
// 					new_cmd->name = append_args(new_cmd->name, tokens[i + j]->value);
// 			}
// 			else if (tokens[i + j]->token_type == 1)
// 			{
// 				if (tokens[i + j + 1])
// 				{
// 					new_cmd->in_file = tokens[i + j + 1]->value;
// 					j++;
// 				}
// 			}
// 			else if (tokens[i + j]->token_type == 2 || tokens[i + j]->token_type == 4)
// 			{
// 				if (tokens[i + j + 1])
// 				{
// 					new_cmd->out_file = tokens[i + j + 1]->value;
// 					j++;					
// 				}
// 			}
// 			j++;
// 		}
// 		if (tokens[i + j] && tokens[i + j]->token_type == 0)
// 			i = i + j + 1;
// 		else
// 			i += j;
// 		j = 0;
// 		index++;
// 	}
// 	return (head);
// }


t_command	*parser(t_token **tokens)
{
	int			i;
	int			j;
	int			index;
	t_command	*head;
	t_command	*current;
	t_command	*new_cmd;

	i = 0;
	j = 0;
	index = 0;
	head = NULL;
	current = NULL;

	while (tokens[i + j])
	{
		new_cmd = init_command();
		if (!new_cmd)
			return (ft_putstr_fd("malloc error at parsing\n", STDERR_FILENO), NULL);
		if (!head)
			head = new_cmd;
		else
			current->next = new_cmd;
		current = new_cmd;
		current->index = index;
		while (tokens[i + j] && tokens[i + j]->token_type != 0)
		{
			if (tokens[i + j]->token_type == 9)
			{
				if (!new_cmd->name)
				{
					new_cmd->name = ft_calloc(2, sizeof(char *));
					if (!new_cmd->name)
						return (ft_putstr_fd("malloc error at parsing\n", STDERR_FILENO), NULL);
					new_cmd->name[0] = ft_strdup(tokens[i + j]->value);
					if (!new_cmd->name[0])
						return (ft_putstr_fd("malloc error at parsing\n", STDERR_FILENO), NULL);
					new_cmd->name[1] = NULL;
				}
				else
					new_cmd->name = append_args(new_cmd->name, tokens[i + j]->value);
			}
			else if (tokens[i + j]->token_type == 1)
			{
				if (tokens[i + j + 1])
				{
					new_cmd->in_file = tokens[i + j + 1]->value;
					j++;
				}
			}
			else if (tokens[i + j]->token_type == 2 || tokens[i + j]->token_type == 4)
			{
				if (tokens[i + j + 1])
				{
					new_cmd->out_file = tokens[i + j + 1]->value;
					j++;					
				}
			}
			j++;
		}
		if (tokens[i + j] && tokens[i + j]->token_type == 0)
			i = i + j + 1;
		else
			i += j;
		j = 0;
		index++;
	}
	return (head);
}
