/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:49:08 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/28 11:41:03 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	data_init(t_data *data)
{
	data->cmd_lst = NULL;
	data->fds.infile_fd = -1;
	data->fds.outfile_fd = -1;
	data->fds.urandom_fd = -1;
	data->cmd_lst_size = 0;
	data->is_here_doc = false;
	data->is_urandom = false;
	data->return_value = 0;
}
