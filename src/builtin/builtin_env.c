/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:26:40 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/04 15:20:22 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_shell *shell)
{
	t_env	*current;

	shell->status = 0;
	if (!shell->shell_env)
		return ;
	current = shell->shell_env;
	while (current)
	{
		ft_printf("%s=", current->name);
		if (!current->value)
			ft_printf("\n");
		else
			ft_printf("%s\n", current->value);
		current = current->next;
	}
}

void	builtin_export(char *line, t_shell *shell)
{
	char	*name;
	char	*value;

	if (!line)
		return ;
	name = get_var_name(line);
	if (!name)
		return ;
	value = get_var_value(line);
	builtin_unset(name, shell);
	if (!value)
		value = ft_calloc(1, sizeof(char));
	if (!value)
	{
		error_msg(MEM, "builtin_export");
		return ;
	}
	if (put_env_var(line, name, value, shell) == -1)
		shell->status = 1;
	else
		shell->status = 0;
	if (is_path(name))
		get_paths(shell);
	free(name);
	free(value);
}
