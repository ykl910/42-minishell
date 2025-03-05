/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_parse_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:11:17 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/05 11:59:30 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**append_args_exec(char **origin_args, char *new_arg)
{
	char	**new_args;
	int		i;

	i = 0;
	i = ft_tabsize((void **)origin_args);
	new_args = ft_calloc((i + 2), sizeof(char *));
	if (!new_args)
		return (NULL);
	i = 0;
	while (origin_args[i])
	{
		new_args[i] = ft_strdup(origin_args[i]);
		if (!new_args[i])
			return (error_msg(MEM, "append_args(1)"),
				ft_free_tab((void **)new_args), NULL);
		i++;
	}
	ft_free_tab((void **)origin_args);
	new_args[i] = ft_strdup(new_arg);
	if (!new_args[i])
		return (error_msg(MEM, "append_args(2)"),
			ft_free_tab((void **)new_args), NULL);
	return (new_args);
}

int	create_cmd(char ***cmd, char *arg)
{
	int		cmd_size;
	char	**temp;

	temp = NULL;
	if (!cmd || !*cmd)
		cmd_size = 0;
	else
		cmd_size = ft_tabsize((void **)*cmd);
	if (cmd_size == 0)
	{
		*cmd = ft_calloc(2, sizeof(char *));
		if (!*cmd)
			return (error_msg(MEM, "create cmd(1)"), -1);
		*cmd[0] = ft_strdup(arg);
		if (!(*cmd)[0])
			return (error_msg(MEM, "create_cmd(2)"), -1);
		return (0);
	}
	temp = append_args_exec(*cmd, arg);
	if (!temp)
		return (-1);
	*cmd = temp;
	return (0);
}

void	parse_simple_cmd(t_ast_node *node, t_shell *shell)
{
	char	**args;
	int		i;

	i = 0;
	args = quotes_handler(node->value, shell);
	if (!args)
		return ;
	while (args[i])
	{
		if (!simple_is_redir(node, args, &i))
		{
			if (create_cmd(&(node->cmd), args[i]) == -1)
				return ;
			i++;
		}
	}
	unlink("/tmp/hdoc");
	ft_free_tab((void **)args);
}
