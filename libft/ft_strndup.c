/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:59:34 by kyang             #+#    #+#             */
/*   Updated: 2025/01/30 18:26:43 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int n)
{
	char	*r;
	int		i;

	r = malloc(sizeof(char) * (n + 1));
	if (!r)
		return (NULL);
	i = 0;
	while (i < n)
	{
		r[i] = s1[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}
