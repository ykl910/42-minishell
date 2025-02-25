/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:44:03 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/25 13:32:48 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int g_signal = 0;

void	reopen_heredoc(int *infile_fd, char *file)
{
	*infile_fd = open("heredoc.txt", O_RDWR, 0644);
	if (*infile_fd < 0)
		handle_open_error(infile_fd, file);
}

static bool	is_limiter(char *line, char *limiter)
{
	if ((ft_strsize_comp(line, limiter) - 1) != 0)
		return (false);
	if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
		return (true);
	return (false);
}

static void	prompt(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
}

void	put_heredoc(int infile_fd, char *limiter)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	prompt(MAGENTA " ==HEREDOC==\n" RESET);
	while (i < MAX_FILE_SIZE)
	{
		prompt(MAGENTA "| " RESET);
		prompt(CYAN "-> " RESET);
		line = get_next_line(STDIN_FILENO);
		if (!line || is_limiter(line, limiter))
			break ;			
		write(infile_fd, line, ft_strlen(line));
		free(line);
		i++;
	}
	prompt(MAGENTA " ==EOF==\n" RESET);
	if (i == MAX_FILE_SIZE)
		prompt(RED "MAX_FILE_SIZE reached.\n" RESET);
	if (line)
		free(line);
	close(infile_fd);
}
