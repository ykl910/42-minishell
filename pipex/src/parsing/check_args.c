/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:47:59 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/03 17:47:50 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	temp_doc_open(t_fd *fds, int ac, char **av)
{
	fds->infile_fd = open("temp.txt", O_CREAT | O_RDWR, 0644);
	if (fds->infile_fd < 0)
		error(OPEN_FD, "Here_doc temp_file");
	fds->outfile_fd = open(av[ac - 1], O_CREAT | O_APPEND | O_RDWR, 0644);
	if (fds->outfile_fd < 0)
		error(PERM, av[ac - 1]);
}

static void	open_in_out(t_fd *fds, int ac, char **av)
{
	fds->infile_fd = open(av[1], O_RDWR, 0644);
	if (fds->infile_fd < 0)
	{
		error(PERM, av[1]);
		fds->infile_fd = open("/dev/null", O_RDONLY);
	}
	fds->outfile_fd = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fds->outfile_fd < 0)
	{
		error(PERM, av[ac - 1]);
		fds->outfile_fd = open("/dev/null", O_WRONLY);
	}
}

static void	check_file_descriptors(t_data *data, int ac, char **av)
{
	if (data->is_here_doc)
		temp_doc_open(&data->fds, ac, av);
	else if (data->is_urandom)
		urandom_open(&data->fds, ac, av);
	else
		open_in_out(&data->fds, ac, av);
}

static void	check_here_doc(t_data *data, char *arg)
{
	if (!arg || !*arg)
		return ;
	if (ft_strlen(arg) == 8 && !ft_strncmp(arg, "here_doc", 8))
		data->is_here_doc = true;
}

bool	check_args(t_data *data, int ac, char **av)
{
	check_here_doc(data, av[1]);
	check_urandom(data, av[1]);
	if ((data->is_here_doc && ac < 5) || (!data->is_here_doc && ac < 4))
		return (data->return_value = 1, error(ARG, NULL), false);
	check_file_descriptors(data, ac, av);
	if (data->is_here_doc)
	{
		if (!put_here_doc(&data->fds, av[2]))
			return (data->return_value = 1, error(MEM, "put_here_doc"), false);
		re_open_temp_doc(&data->fds);
	}
	if (data->is_urandom)
	{
		if (!put_urandom(&data->fds))
			return (data->return_value = 1, error(MEM, "put_urandom"), false);
		re_open_temp_doc(&data->fds);
	}
	return (true);
}
