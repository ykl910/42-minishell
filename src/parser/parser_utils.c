/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:13:25 by kyang             #+#    #+#             */
/*   Updated: 2025/02/07 11:48:04 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*Revoir la maniere de free si erreur -> retour main et appel fonction free de struct(s)*/
char	**append_args(char **origin_args, char *new_arg)
{
	char	**new_args;
	int		i;

	i = 0;
	while (origin_args[i])
		i++;
	new_args = ft_calloc((i + 2), sizeof(char *));
	if (!new_args)
		return (NULL);
	i = 0;
	while (origin_args[i])
	{
		new_args[i] = ft_strdup(origin_args[i]);
		if (!new_args[i])
			return (ft_putstr_fd("malloc error app.arg\n", STDERR_FILENO),
				ft_free_tab((void **)new_args), NULL);
		i++;
	}
	ft_free_tab((void **)origin_args);
	new_args[i] = ft_strdup(new_arg);
	if (!new_args[i])
		return (ft_putstr_fd("malloc error at app.args\n", STDERR_FILENO),
			ft_free_tab((void **)new_args), NULL);
	return (new_args);
}

int	get_precedence(e_token token)
{
	if (token == TOKEN_AND || token == TOKEN_OR)
		return (1);
	else if (token == TOKEN_PIPE)
		return (2);
	else if (token == TOKEN_REDIRECT_IN || token == TOKEN_REDIRECT_OUT
		|| token == TOKEN_HERE_DOC || token == TOKEN_REDIRECT_APPEND)
		return (3);
	else if (token == TOKEN_LPAREN)
		return (4);
	else
		return (0);
}

e_command	get_command_type(e_token token_type)
{
	if (token_type == TOKEN_AND)
		return (COMMAND_AND);
	else if (token_type == TOKEN_OR)
		return (COMMAND_OR);
	else if (token_type == TOKEN_PIPE)
		return (COMMAND_PIPE);
	else if (token_type == TOKEN_REDIRECT_IN)
		return (COMMAND_REDIRECT_IN);
	else if (token_type == TOKEN_REDIRECT_OUT)
		return (COMMAND_REDIRECT_OUT);
	else if (token_type == TOKEN_HERE_DOC)
		return (COMMAND_HERE_DOC);
	else if (token_type == TOKEN_REDIRECT_APPEND)
		return (COMMAND_REDIRECT_APPEND);
	else
		return (COMMAND_SIMPLE);
}

t_ast_node	*create_node(e_command type, t_ast_node *left, t_ast_node *right,
		char *value)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (ft_putstr_fd("malloc error create node\n", STDERR_FILENO),
			NULL);
	node->node_type = type;
	node->left = left;
	node->right = right;
	node->value = ft_calloc(2, sizeof(char *));
	if (!node->value)
		return (ft_putstr_fd("malloc error create node\n", STDERR_FILENO),
			NULL);
	if (value)
		node->value[0] = ft_strdup(value);
	else
		node->value[0] = NULL;
	return (node);
}
