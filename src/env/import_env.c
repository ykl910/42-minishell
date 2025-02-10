/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:37:14 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/10 19:07:43 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	import_env(t_env **env, char **envp, int *status)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		builtin_export(envp[i], env, status);
		i++;
	}
}
