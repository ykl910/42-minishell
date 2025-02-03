/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:33:36 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/03 14:35:38 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int n)
{
	char *r;
	int i;

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
