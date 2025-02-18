/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:24:13 by kyang             #+#    #+#             */
/*   Updated: 2025/02/18 10:39:33 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	struct_init(t_shell *shell)
{
	shell->ast = NULL;
	shell->shell_env = NULL;
	shell->token_lst = NULL;
	shell->paths = NULL;
	shell->prompt_type = AST_CMD;
	shell->status = 0;
}

static char	*str_fusion(char *buffer, char *line)
{
	char	*temp;

	temp = ft_strjoin(buffer, line);
	if (!temp)
		return (free(buffer), NULL);
	free(buffer);
	return (temp);
}

static bool	add_subpath(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		path[i] = str_fusion(path[i], "/\0");
		if (!path[i])
			return (false);
		i++;
	}
	return (true);
}

static void	*get_paths(t_shell *shell)
{
	int		i;
	t_env	*tempenv;
	char	*temp;
	char	**paths;

	i = 0;
	if (!shell->shell_env)
		return ;
	tempenv = shell->shell_env;
	while (tempenv && ft_strncmp(tempenv->name, "PATH", 5))
		tempenv = tempenv->next;
	if (!tempenv)
		return ;
	temp = ft_strdup(tempenv->value);
	if (!temp)
		return ;
	paths = ft_split(temp, ':');
	free(temp);
	if (!paths)
		return ;
	if (!add_subpath(paths))
		return (ft_free_tab((void **)paths));
	shell->paths = paths;
	return (NULL);
}

void	shell_init(t_shell *shell, char **envp)
{
	struct_init(shell);
	import_env(shell, envp);
	get_paths(shell);
}
