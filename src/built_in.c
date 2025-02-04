/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:51:20 by kyang             #+#    #+#             */
/*   Updated: 2025/02/04 17:42:49 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(char **cmd)
{
	const char	*home_path;

	home_path = NULL;
	if (!cmd[1])
	{
		home_path = getenv("HOME");
		if (!home_path)
			return (error("HOME not set", NULL));
		chdir(home_path);
		free(home_path);
	}
	if (chdir(cmd[1]) == -1)
		error(FILE_DIR, cmd[1]);
}

void	builtin_echo(char **cmd)
{
	int		i;
	bool	new_line;

	i = 0;
	new_line = true;
	if (cmd[1] && !ft_strncmp(cmd[1], "-n", ft_strlen(cmd[1])))
	{
		new_line = false;
		i = 2;
	}
	while (cmd[i])
	{
		ft_printf("%s", cmd[i]);
		if (cmd[i + 1])
			ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
}

void	builtin_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (error(MEM, "builtin_pwd"));
	ft_printf("%s\n", path);
	free(path);
}

void	builtin_export(char *line, t_env **env)
{
	char	*name;
	char	*value;

	if(!line)
		return ;
	name = get_var_name(line);
	if (!name)
		return ;
	value = get_var_value(line);
	if (!*env)
		create_head_env_lst(name, value, env);
	else
		create_node_env_lst(name, value, env);
}

void	built_in_exec(t_command **cmd, t_env **env)
{
	int	cmd_size;

	cmd_size = 0;
	if (!(*cmd)->name[0])
		return ;
	cmd_size = ft_strlen((*cmd)->name[0]);
	if (!ft_strncmp((*cmd)->name[0], "cd", cmd_size))
		builtin_cd((*cmd)->name);
	if (!ft_strncmp((*cmd)->name[0], "echo", cmd_size))
		builtin_echo((*cmd)->name);
	if (!ft_strncmp((*cmd)->name[0], "pwd", cmd_size))
		builtin_pwd();
	if (!ft_strncmp((*cmd)->name[0], "export", cmd_size))
		builtin_export((*cmd)->name[1], env);
	if (!ft_strncmp((*cmd)->name[0], "unset", cmd_size))
	if (!ft_strncmp((*cmd)->name[0], "exit", cmd_size))
}
