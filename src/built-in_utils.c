/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:34:57 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/04 19:37:28 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *env_line)
{
	int		i;
	char	*name;

	i = 0;
	name = NULL;
	while (env_line[i] && env_line[i] != '=')
		i++;
	if(env_line[i] != '=')
		return (NULL);
	name = ft_strndup(env_line, i);
	if (!name)
		return (error(MEM, "get_var_name"), NULL);
	return (name);
}

char	*get_var_value(char *env_line)
{
	int		i;
	int		line_size;
	char	*value;

	i = 0;
	value = NULL;
	line_size = ft_strlen(env_line);
	while (env_line[i] && env_line[i] != '=')
		i++;
	if ((line_size - (i + 2)) == 0)
		return (NULL);
	value = ft_strdup(&env_line[i]);
	if (!value)
		return (error(MEM, "get_var_value"), NULL);
	return (value);
}

bool	create_head_env_lst(char *name, char *value, t_env **env)
{
	*env = malloc(sizeof(t_env));
	if (!*env)
		return (error(MEM, "create_head_env_lst"), false);
	(*env)->name = name;
	(*env)->value = value;
	(*env)->next = NULL;
	return (true);
}

bool	create_node_env_lst(char *name, char *value, t_env **env)
{
	t_env	*temp;
	t_env	*new;

	temp = *env;
	new = malloc(sizeof(t_env));
	if (!new)
		return (error(MEM, "create_node_env_lst"), false);
	new->name = name;
	new->value = value;
	new->next = NULL;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (true);
}

bool	is_numerical(char *str)
{
	int	i;

	i = 0;
	if(str[i] == '-' || str[i] == '+');
		i++;
	if(!str[i])
		return (false);
	while(str[i])
	{
		if(!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
