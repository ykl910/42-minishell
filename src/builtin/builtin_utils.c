/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:40:38 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/21 16:20:51 by alacroix         ###   ########.fr       */
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
	if (env_line[i] != '=')
		return (NULL);
	name = ft_strndup(env_line, i);
	if (!name)
		return (error_msg(MEM, "get_var_name"), NULL);
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
	i++;
	if (i >= line_size)
		return (NULL);
	value = ft_strdup(&env_line[i]);
	if (!value)
		return (error_msg(MEM, "get_var_value"), NULL);
	return (value);
}

int	create_head_env_lst(char *key, char **name, char **value, t_env **env)
{
	*env = malloc(sizeof(t_env));
	if (!*env)
		return (error_msg(MEM, "create_head_env_lst"), -1);
	(*env)->name = *name;
	(*env)->value = *value;
	(*env)->key_val = key;
	(*env)->next = NULL;
	return (0);
}

int	create_node_env_lst(char *key, char **name, char **value, t_env **env)
{
	t_env	*temp;
	t_env	*new;

	temp = *env;
	new = malloc(sizeof(t_env));
	if (!new)
		return (error_msg(MEM, "create_node_env_lst"), -1);
	new->name = *name;
	new->value = *value;
	new->key_val = key;
	new->next = NULL;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (0);
}

int	put_env_var(char *line, char **name, char **value, t_shell *shell)
{
	if (!shell->shell_env)
		return (create_head_env_lst(line, name, value, &shell->shell_env));
	else
		return (create_node_env_lst(line, name, value, &shell->shell_env));
}

bool	is_numerical(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
