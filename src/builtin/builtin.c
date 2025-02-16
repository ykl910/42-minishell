/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:39:57 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/16 14:52:05 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(char **cmd, t_shell *shell)
{
	char	*home_path;

	home_path = NULL;
	if (!cmd[1])
	{
		home_path = getenv("HOME");
		if (!home_path)
		{
			shell->status = 1;
			return ;
		}
		chdir(home_path);
		free(home_path);
	}
	if (chdir(cmd[1]) == -1)
	{
		shell->status = 1;
		return ;
	}
	update_env(&shell->shell_env);
	shell->status = 0;

}

void	builtin_echo(char **cmd, t_shell *shell)
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
	shell->status = 0;
}

void	builtin_pwd(int *status)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		*status = 1;
		return ;
	}
	ft_printf("%s\n", path);
	free(path);
	*status = 0;
}

void	builtin_export(char *line, t_env **env, int *status)
{
	char	*name;
	char	*value;

	if (!line)
		return ;
	name = get_var_name(line);
	if (!name)
		return ;
	value = get_var_value(line);
	if (!*env)
	{
		if (!create_head_env_lst(&name, &value, env))
		{
			*status = 1;
			return (free(name), free(value));
		}
	}
	else
	{
		if (!create_node_env_lst(&name, &value, env))
		{
			*status = 1;
			return (free(name), free(value));
		}
	}
	*status = 0;
}

void	builtin_unset(char *target, t_env **env, int *status)
{
	int		target_size;
	t_env	*current;
	t_env	*prev;

	*status = 0;
	if (!env || !*env || !target)
		return ;
	target_size = ft_strlen(target);
	current = *env;
	prev = NULL;
	if (!ft_strncmp(target, current->name, target_size))
	{
		*env = current->next;
		return (free(current));
	}
	while (current && ft_strncmp(target, current->name, target_size))
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return ;
	prev->next = current->next;
	free(current);
}

void	builtin_env(t_env **env, int *status)
{
	t_env	*current;

	*status = 0;
	if (!env || !*env)
		return ;
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
}

void	builtin_exit(char **args, int *status)
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
				return (exit(255));
			else if (args[2])
			{
				*status = 1;
				return ;
			}
		}
		else
			return (exit(255));
	}
	exit((unsigned char)exit_code);
}

int	built_in_exec(t_shell *shell, t_ast_node *node)
{
	int	name_size;

	name_size = 0;
	if (!node->cmd)
		return ;
	name_size = ft_strlen(node->cmd[0]);
	if (!ft_strncmp(node->cmd[0], "cd", name_size))
		return(builtin_cd(node->cmd, shell->status), 0);
	else if (!ft_strncmp(node->cmd[0], "echo", name_size))
		return(builtin_echo(node->cmd, shell->status), 0);
	else if (!ft_strncmp(node->cmd[0], "pwd", name_size))
		return(builtin_pwd(shell->status), 0);
	else if (!ft_strncmp(node->cmd[0], "export", name_size))
		return(builtin_export(node->cmd[1], shell->shell_env, shell->status), 0);
	else if (!ft_strncmp(node->cmd[0], "unset", name_size))
		return(builtin_unset(node->cmd[1], shell->shell_env, shell->status), 0);
	else if (!ft_strncmp(node->cmd[0], "env", name_size))
		return(builtin_env(shell->shell_env, shell->status), 0);
	else if (!ft_strncmp(node->cmd[0], "exit", name_size))
		return(builtin_exit(node->cmd, shell->status), 0);
	else
		return (-1);
}

