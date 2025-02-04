/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:51:20 by kyang             #+#    #+#             */
/*   Updated: 2025/02/04 14:17:15 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(char *line)
{
	char		**cmd;
	const char	*home_path;

	if (!line)
		return ;
	cmd = ft_split(line, ' ');
	home_path = NULL;
	if (!cmd)
		return (error(MEM, "built_in_cd"));
	if (!ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])))
	{
		if (!cmd[1])
		{
			home_path = getenv("HOME");
			if (!home_path)
				return (error("HOME not set", NULL));
			chdir(home_path);
		}
		else if (chdir(cmd[1]) == -1)
			error(FILE_DIR, cmd[1]);
	}
}

void	builtin_echo(char *line)
{

}
