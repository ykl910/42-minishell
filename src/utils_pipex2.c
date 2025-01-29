/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:43:06 by kyang             #+#    #+#             */
/*   Updated: 2025/01/29 17:40:52 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_split2(char **split)
{
	int	i;

	i = 1;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_splits(char **split1, char **split2, char *arg)
{
	if (split1)
		free_split(split1);
	if (split2)
		free_split2(split2);
	if (arg)
		free(arg);
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}
