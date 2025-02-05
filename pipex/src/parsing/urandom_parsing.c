/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   urandom_parsing_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:29:47 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/30 12:44:20 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	put_urandom(t_fd *fds)
{
	char	*buffer;

	buffer = ft_calloc(MAX_FILE_SIZE + 1, sizeof(char));
	if (!buffer)
		return (false);
	read(fds->urandom_fd, buffer, MAX_FILE_SIZE);
	close(fds->urandom_fd);
	ft_putstr_fd(buffer, fds->infile_fd);
	close(fds->infile_fd);
	free(buffer);
	return (true);
}

void	urandom_open(t_fd *fds, int ac, char **av)
{
	fds->infile_fd = open("temp.txt", O_CREAT | O_RDWR, 0644);
	if (fds->infile_fd < 0)
		error(OPEN_FD, "temp_file");
	fds->outfile_fd = open(av[ac - 1], O_CREAT | O_APPEND | O_RDWR, 0644);
	if (fds->outfile_fd < 0)
		error(PERM, av[ac - 1]);
	fds->urandom_fd = open(av[1], O_RDONLY, 0644);
	if (fds->urandom_fd < 0)
		error(PERM, av[1]);
}

void	check_urandom(t_data *data, char *arg)
{
	if (!arg || !*arg)
		return ;
	if (ft_strlen(arg) == 12 && !ft_strncmp(arg, "/dev/urandom", 12))
		data->is_urandom = true;
}
