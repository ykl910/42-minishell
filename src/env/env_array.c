/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:29:50 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/24 19:05:54 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_env_size(t_env *env)
{
	int		i;
	t_env	*current;

	i = 0;
	current = env;
	if (!env)
		return (i);
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

char	**env_lst_to_array(t_env *env)
{
	char	**env_array;
	int		env_size;
	t_env	*current;
	int		i;

	i = 0;
	env_array = NULL;
	current = env;
	if (!env)
		return (NULL);
	env_size = get_env_size(env);
	env_array = ft_calloc(env_size + 1, sizeof(char *));
	if (!env_array)
		return (NULL);
	while (current)
	{
		env_array[i] = current->key_val;
		i++;
		current = current->next;
	}
	return (env_array);
}
