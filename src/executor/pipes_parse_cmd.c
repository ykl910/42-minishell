/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   V2pipes_parse_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:09:02 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/03 14:52:58 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_cmd_arg(char ***cmd, char *arg)
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

int	parse_cmd(t_cmd **clst_node, t_ast_node *ast_node)
{
	char **args;
	int i;
	int status;

	i = 0;
	status = 0;
	args = quotes_handler(ast_node->value);
	if (!args)
		return (-1);
	while (args[i])
	{
		if (!is_redir(*clst_node, args, &i))
		{
			status = add_cmd_arg(&((*clst_node)->cmd), args[i]);
			i++;
		}
		if (status == -1)
			return (ft_free_tab((void **)args), -1);
	}
	return (ft_free_tab((void **)args), 0);
}
