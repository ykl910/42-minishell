/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:51:20 by kyang             #+#    #+#             */
/*   Updated: 2025/02/04 19:54:06 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(char **cmd, int status)
{
	const char	*home_path;

	home_path = NULL;
	if (!cmd[1])
	{
		home_path = getenv("HOME");
		if (!home_path)
			return (error("HOME not set", NULL), status = 1);
		chdir(home_path);
		free(home_path);
	}
	if (chdir(cmd[1]) == -1)
		return (error(FILE_DIR, cmd[1]), status = 1);
	status = 0;
}

void	builtin_echo(char **cmd, int status)
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
	status = 0;
}

void	builtin_pwd(int status)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (error(MEM, "builtin_pwd"), status = 1);
	ft_printf("%s\n", path);
	free(path);
	status = 0;
}

void	builtin_export(char *line, t_env **env, int status)
{
	char	*name;
	char	*value;

	if (!line)
		return ;
	name = get_var_name(line);
	if (!name)
		return (status = 0);
	value = get_var_value(line);
	if (!*env)
	{
		if (!create_head_env_lst(name, value, env))
			return (free(name), free(value), status = 1);
	}
	else
	{
		if (!create_node_env_lst(name, value, env))
			return (free(name), free(value), status = 1);
	}
	free(name);
	free(value);
	status = 0;
}

void	builtin_unset(char *target, t_env **env, int status)
{
	int		target_size;
	t_env	*current;
	t_env	*prev;

	if (!env || !*env || !target)
		return (status == 0);
	target_size = current = *env;
	prev = NULL;
	if (!ft_strncmp(target, current->name, target_size))
	{
		*env = current->next;
		return (free(current), status = 0);
	}
	while (current && ft_strncmp(target, current->name, target_size))
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return (status = 0);
	prev->next = current->next;
	free(current);
	status = 0;
}

void	builtin_env(t_env **env, int status)
{
	t_env	*current;

	if (!env || !*env)
		return (status = 0);
	current = *env;
	while (current)
	{
		ft_printf("%s=", current->name);
		if (!current->value)
			ft_printf("\n");
		else
			ft_printf("%s\n", current->value);
		current = current->next;
	}
	status = 0;
}

void	builtin_exit(char **args, int status)
{
	long	exit_code;

	exit_code = 0;
	ft_printf("exit\n");
	if (args[1])
	{
		if (is_numerical(args[1]))
		{
			exit_code = ft_atol(args[1]);
			if (INT_MIN > exit_code || exit_code > INT_MAX)
				return (error(EXIT, NULL), exit(255));
			else if (args[2])
				return (error(ARG, NULL), status = 1);
		}
		else
			return (error(ARG, NULL), exit(255));
	}
	exit((unsigned char)exit_code);
}

void	built_in_exec(t_shell *shell, t_command *cmd)
{
	int	name_size;

	name_size = 0;
	if (!cmd->name[0])
		return ;
	name_size = ft_strlen(cmd->name[0]);
	if (!ft_strncmp(cmd->name[0], "cd", name_size))
		builtin_cd(cmd->name, shell->status);
	if (!ft_strncmp(cmd->name[0], "echo", name_size))
		builtin_echo(cmd->name, shell->status);
	if (!ft_strncmp(cmd->name[0], "pwd", name_size))
		builtin_pwd(shell->status);
	if (!ft_strncmp(cmd->name[0], "export", name_size))
		builtin_export(cmd->name[1], shell->env, shell->status);
	if (!ft_strncmp(cmd->name[0], "unset", name_size))
		builtin_unset(cmd->name[1], shell->env, shell->status);
	if (!ft_strncmp(cmd->name[0], "env", name_size))
		builtin_env(shell->env, shell->status);
	if (!ft_strncmp(cmd->name[0], "exit", name_size))
		builtin_exit(cmd->name, shell->status);
}
