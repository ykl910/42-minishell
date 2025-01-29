/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:07:53 by kyang             #+#    #+#             */
/*   Updated: 2024/11/11 12:40:32 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	int		i;
	int		j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	r = malloc(sizeof(char) * (i + j + 1));
	if (!r)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		r[i + j] = s2[j];
		j++;
	}
	r[i + j] = '\0';
	return (r);
}
/*
int	main(void)
{
	printf("%s\n", ft_strjoin("Hello ", "there"));
	printf("%s\n", ft_strjoin("Hi", ""));
	printf("%s\n", ft_strjoin("123", "yo"));
	printf("%s\n", ft_strjoin("", ""));
	return 0;
}*/
