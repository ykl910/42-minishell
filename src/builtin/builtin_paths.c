/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:28:53 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/04 14:29:15 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(char **cmd, t_shell *shell)
{
	char	*home_path;
	int		arg_size;

	arg_size = ft_tabsize((void **)cmd);
	home_path = NULL;
	if (arg_size == 1)
	{
		home_path = getenv("HOME");
		if (!home_path)
		{
			shell->status = 1;
			error_msg(RED DF RESET, "you are lost ...");
			return ;
		}
		chdir(home_path);
	}
	if (arg_size > 1 && chdir(cmd[1]) == -1)
	{
		shell->status = 1;
		error_msg(RED DF RESET, cmd[1]);
		return ;
	}
	update_env(&shell->shell_env);
	shell->status = 0;
}

void	builtin_pwd(t_shell *shell)
{
	t_env	*current;
	char	*cwd;

	cwd = NULL;
	current = shell->shell_env;
	while (current)
	{
		if (!ft_strncmp(current->name, "PWD", ft_strlen(current->name)))
		{
			ft_printf("%s\n", current->value);
			return ;
		}
		current = current->next;
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		error_msg(RED DF RESET, "you are lost ...");
	else
	{
		ft_printf("%s\n", cwd);
		free(cwd);
	}
}
