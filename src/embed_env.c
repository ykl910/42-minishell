/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   embed_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:15:11 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/04 17:38:20 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	embed_env(t_env **env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		builtin_export(envp[i], env);
		i++;
	}
}
