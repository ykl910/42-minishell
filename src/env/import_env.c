/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:37:14 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/26 18:58:13 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_old_path(t_env **env)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (!ft_strncmp(current->name, "PWD", ft_strlen(current->name)))
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

static int	chage_pwd(t_env **env, char *pwd)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (!ft_strncmp(current->name, "PWD", ft_strlen(current->name)))
		{
			free(current->value);
			current->value = ft_strdup(pwd);
			if (!current->value)
				return (-1);
			return (0);
		}
		current = current->next;
	}
	return (0);
}

static int	chage_old_pwd(t_env **env, char *old_pwd)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (!ft_strncmp(current->name, "OLDPWD", ft_strlen(current->name)))
		{
			free(current->value);
			current->value = ft_strdup(old_pwd);
			if (!current->value)
				return (-1);
			return (0);
		}
		current = current->next;
	}
	return (0);
}

void	update_env(t_env **env)
{
	char	*old_pwd;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	old_pwd = get_old_path(env);
	if (!old_pwd)
		return (free(pwd));
	if (chage_pwd(env, pwd) == -1)
		return (error_msg(MEM, "change_pwd"), free(pwd), free(old_pwd));
	if (chage_old_pwd(env, old_pwd) == -1)
		return (error_msg(MEM, "change_old_pwd"), free(pwd), free(old_pwd));
	free(pwd);
	free(old_pwd);
}

void	import_env(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		builtin_export(envp[i], shell);
		i++;
	}
}
