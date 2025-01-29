/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:02:37 by kyang             #+#    #+#             */
/*   Updated: 2024/11/12 16:58:02 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	i;
	size_t	j;

	r = malloc(sizeof(const char) * (len + 1));
	if (!s || !r)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			r[j] = s[i];
			j++;
		}
		i++;
	}
	r[j] = '\0';
	return (r);
}
/*
int	main(void)
{
	//printf("%s\n", ft_substr("Hello there", 0, 11));
	//printf("%s\n", ft_substr("Hello there", 2, 11));
	//printf("%s\n", ft_substr("Hello there", 2, 3));
	printf("%d",ft_substr("tripouille", 100, 1)== "");
	//printf("%s\n", ft_substr("tripouille", 100, 1));
	return (0);
}*/
