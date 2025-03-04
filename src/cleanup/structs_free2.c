/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_free2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:29:51 by alacroix          #+#    #+#             */
/*   Updated: 2025/03/04 14:19:12 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_clist(t_cmd **cmd_lst)
{
	t_cmd	*temp;
	t_cmd	*next;

	if (!cmd_lst || !*cmd_lst)
		return ;
	temp = *cmd_lst;
	while (temp != NULL)
	{
		next = temp->next;
		if (temp->abs_path)
			free(temp->abs_path);
		if (temp->cmd)
			ft_free_tab((void **)temp->cmd);
		if (temp->fd_in > -1)
			close(temp->fd_in);
		if (temp->fd_out > -1)
			close(temp->fd_out);
		free(temp);
		temp = next;
	}
	*cmd_lst = NULL;
}

void	free_exit(int *exit_status, t_shell *shell)
{
	int	status;

	status = *exit_status;
	if (shell->shell_env)
		free_env(&shell->shell_env);
	if (shell->token_lst)
		free_tokens(&shell->token_lst);
	if (shell->paths)
		ft_free_tab((void **)shell->paths);
	if (shell->ast)
		free_ast(shell->ast);
	if (shell->clist)
		free_clist(&shell->clist);
	if (shell->prompt)
		free(shell->prompt);
	rl_clear_history();
	exit(status);
}
