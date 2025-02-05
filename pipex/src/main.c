/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:03:32 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/29 14:09:58 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data_init(&data);
	if (!check_args(&data, argc, argv))
		return (data_cleanup(&data), data.return_value);
	if (!create_cmd_lst(&data, argc, argv, envp))
		return (data_cleanup(&data), data.return_value);
	run_cmds(&data, envp);
	return (data_cleanup(&data), data.return_value);
}
