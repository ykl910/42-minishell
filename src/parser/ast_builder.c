/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:33:09 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/11 15:48:50 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// char	**create_arg(t_token *token_lst, int *token_index)
// {
// 	int		i;
// 	char	**args;

// 	i = 0;
// 	args = NULL;
// 	while (token_lst[*token_index + i].token_type == TOKEN_TEXT)
// 		i++;
// 	args = ft_calloc(i + 1, sizeof(char));
// 	if (!args)
// 		return (NULL);
// 	i = 0;
// 	while (token_lst[*token_index].token_type == TOKEN_TEXT)
// 	{
// 		args[i] = ft_strdup(token_lst[*token_index].value);
// 		if (!args[i])
// 			return (ft_free_tab((void **)args), NULL);
// 		(*token_index)++;
// 		i++;
// 	}
// 	return (args);
// }

// t_ast	*parse_cmd(t_token *token_lst, int *token_index)
// {
// 	t_ast	*current;

// 	current = NULL;
// 	if (token_lst[*token_index].token_type == TOKEN_TEXT)
// 	{
// 		ft_printf("cmd \n");
// 		current = malloc(sizeof(t_ast));
// 		if (!current)
// 			return (NULL);
// 		current->node_type = COMMAND;
// 		current->args = create_arg(token_lst, token_index);
// 	}
// 	if (token_lst[*token_index].token_type == TOKEN_LPAREN)
// 	{
// 		ft_printf("SUBSHELL \n");
// 		(*token_index)++;
// 		current = malloc(sizeof(t_ast));
// 		if (!current)
// 			return (NULL);
// 		current->node_type = SUBSHELL;
// 		current->subshell = parse_logic_operator(token_lst, token_index);
// 		if (token_lst[*token_index].token_type != TOKEN_RPAREN)
// 			return (ft_printf("ERROR\n"), NULL);
// 		(*token_index)++;
// 	}
// 	if (token_lst[*token_index].token_type == TOKEN_REDIRECT_IN
// 		|| token_lst[*token_index].token_type == TOKEN_HERE_DOC
// 		|| token_lst[*token_index].token_type == TOKEN_REDIRECT_OUT
// 		|| token_lst[*token_index].token_type == TOKEN_REDIRECT_APPEND)
// 	{
// 		ft_printf("redir: ");
// 		current = malloc(sizeof(t_ast));
// 		if (!current)
// 			return (NULL);
// 		if (token_lst[*token_index].token_type == TOKEN_REDIRECT_IN)
// 		{
// 			ft_printf("<\n");
// 			current->node_type = REDIR_IN;
// 		}
// 		else if (token_lst[*token_index].token_type == TOKEN_HERE_DOC)
// 		{
// 			ft_printf("<<\n");
// 			current->node_type = HEREDOC;
// 		}
// 		else if (token_lst[*token_index].token_type == TOKEN_REDIRECT_OUT)
// 		{
// 			ft_printf(">\n");
// 			current->node_type = REDIR_OUT;
// 		}
// 		else
// 		{
// 			ft_printf(">>\n");
// 			current->node_type = REDIR_APPEND;
// 		}
// 		(*token_index)++;
// 		if (token_lst[*token_index].token_type != TOKEN_TEXT)
// 			return (NULL);
// 		current->redir_file = ft_strdup(token_lst[*token_index].value);
// 		if (!current->redir_file)
// 			return (NULL);
// 		(*token_index)++;
// 	}
// 	return (current);
// }

// t_ast	*parse_pipe(t_token *token_lst, int *token_index)
// {
// 	t_ast	*left;
// 	t_ast	*current;

// 	left = parse_cmd(token_lst, token_index);
// 	current = NULL;
// 	while (token_lst[*token_index].token_type == TOKEN_PIPE)
// 	{
// 		ft_printf("pipe \n");
// 		current = malloc(sizeof(t_ast));
// 		if (!current)
// 			return (NULL);
// 		current->node_type = PIPE;
// 		current->args = NULL;
// 		current->subshell = NULL;
// 		current->redir_file = NULL;
// 		current->next = NULL;
// 		(*token_index)++;
// 		current->left_node = left;
// 		current->right_node = parse_cmd(token_lst, token_index);
// 		left = current;
// 	}
// 	return (left);
// }

// t_ast	*parse_logic_operator(t_token *token_lst, int *token_index)
// {
// 	t_ast	*left;
// 	t_ast	*current;

// 	left = parse_pipe(token_lst, token_index);
// 	current = NULL;
// 	while (token_lst[*token_index].token_type == TOKEN_AND
// 		|| token_lst[*token_index].token_type == TOKEN_OR)
// 	{
// 		ft_printf("logical operator :");
// 		current = malloc(sizeof(t_ast));
// 		if (!current)
// 			return (NULL);
// 		if (token_lst[*token_index].token_type == TOKEN_AND)
// 		{
// 			ft_printf("&&\n");
// 			current->node_type = AND;
// 		}
// 		else
// 		{
// 			ft_printf("||\n");
// 			current->node_type = OR;
// 		}
// 		current->args = NULL;
// 		current->subshell = NULL;
// 		current->redir_file = NULL;
// 		current->next = NULL;
// 		(*token_index)++;
// 		current->left_node = left;
// 		current->right_node = parse_pipe(token_lst, token_index);
// 		left = current;
// 	}
// 	return (left);
// }

// t_ast	*parser(t_token *token_lst)
// {
// 	int	token_index;

// 	token_index = 0;
// 	return (parse_logic_operator(token_lst, &token_index));
// }
