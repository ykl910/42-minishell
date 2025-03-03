/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_parse_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:11:17 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/03 15:12:11 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	temp = append_args(*cmd, arg);
	if (!temp)
		return (-1);
	*cmd = temp;
	return (0);
}

void	parse_simple_cmd(t_ast_node *node)
{
	char	**args;
	int		i;

	i = 0;
	args = quotes_handler(node->value);
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
