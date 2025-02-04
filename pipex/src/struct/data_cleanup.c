/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:52:27 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/29 14:09:30 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	lst_free(t_lst **cmd_lst)
{
	t_lst	*temp;
	t_lst	*next;

	if (!cmd_lst || !*cmd_lst)
		return ;
	temp = *cmd_lst;
	while (temp != NULL)
	{
		next = temp->next;
		if (temp->name)
			ft_free_tab((void **)temp->name);
		if (temp->path)
			free(temp->path);
		free(temp);
		temp = next;
	}
	*cmd_lst = NULL;
}

void	data_cleanup(t_data *data)
{
	if (data->is_here_doc || data->is_urandom)
		unlink("temp.txt");
	if (data->fds.infile_fd > 0)
		close(data->fds.infile_fd);
	if (data->fds.outfile_fd > 0)
		close(data->fds.outfile_fd);
	if (data->cmd_lst)
		lst_free(&data->cmd_lst);
}
