/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:39:41 by kyang             #+#    #+#             */
/*   Updated: 2024/11/06 18:51:51 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && i < n - 1)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
/*
int	main(void)
{
	char *s1 = "ABCDFF";
	char *s2 = "ABCDEE";
	char *s3 = "AB";
	char *s4 = "";
	char *s5 = "ABC";
	char *s6 = "ABC";
	int n = 2;

	printf("%d\n",ft_strncmp(s1, s2, 5));
	printf("%d\n",strncmp(s1, s2, 5));

	printf("%d\n",ft_strncmp(s3, s4, n));
	printf("%d\n",strncmp(s3, s4, n));
	
	printf("%d\n",ft_strncmp(s5, s6, n));
	printf("%d\n",strncmp(s5, s6, n));
	return (0);
}*/
