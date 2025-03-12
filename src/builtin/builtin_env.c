/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:26:40 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/12 10:53:43 by kyang            ###   ########.fr       */
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

static int	check_export(char *name, char *line, t_shell *shell)
{
	if (name[0] && !ft_isalpha(name[0]) && name[0] != '_')
	{
		shell->status = 1;
		return (error_msg(RED EXPORT RESET, line), 0);
	}
	return (1);
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
	if (!check_export(name, line, shell))
		return ;
	value = get_var_value(line);
	builtin_unset(name, shell);
	if (!value)
		value = ft_calloc(1, sizeof(char));
	if (!value)
		return (error_msg(MEM, "builtin_export"));
	if (put_env_var(line, name, value, shell) == -1)
		shell->status = 1;
	else
		shell->status = 0;
	if (is_path(name))
		get_paths(shell);
	free(name);
	free(value);
}
