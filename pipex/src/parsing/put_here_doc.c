/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:35:05 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/29 17:30:45 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	is_limiter(char *line, char *limiter)
{
	if ((ft_strsize_comp(line, limiter) - 1) != 0)
		return (false);
	if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
		return (true);
	return (false);
}

void	re_open_temp_doc(t_fd *fds)
{
	fds->infile_fd = open("temp.txt", O_RDWR, 0644);
	if (fds->infile_fd < 0)
		error(OPEN_FD, "Here_doc temp_file");
}

bool	put_here_doc(t_fd *fds, char *limiter)
{
	int		i;
	char	*line;
	char	*buffer;

	i = 0;
	line = NULL;
	buffer = ft_calloc(1, sizeof(char));
	if (!buffer)
		return (false);
	while (i < MAX_FILE_SIZE)
	{
		ft_printf("heredoc> ");
		line = get_next_line(STDIN_FILENO);
		if (!line || is_limiter(line, limiter))
			break ;
		buffer = str_fusion(buffer, line);
		if (!buffer)
			return (free(line), false);
		free(line);
		i++;
	}
	ft_putstr_fd(buffer, fds->infile_fd);
	if (line)
		free(line);
	return (close(fds->infile_fd), free(buffer), true);
}
