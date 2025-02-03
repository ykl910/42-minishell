/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:41:34 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/04 15:55:07 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*string;
	unsigned char	a;
	size_t			i;

	string = (unsigned char *)s;
	a = c;
	i = 0;
	while (i < n)
	{
		if (string[i] == a)
			return (&string[i]);
		i++;
	}
	return (NULL);
}
