/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:12:29 by kyang             #+#    #+#             */
/*   Updated: 2024/11/12 00:09:08 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	uihlen(unsigned long int n)
{
	int	l;

	l = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		l++;
		n /= 16;
	}
	return (l);
}

char	*ft_uitoh(unsigned long int n)
{
	int		l;
	char	*r;

	l = uihlen(n);
	r = malloc(sizeof(char) * (l + 1));
	if (!r)
		return (NULL);
	r[l] = '\0';
	while (l > 0)
	{
		r[l - 1] = "0123456789ABCDEF"[n % 16];
		n /= 16;
		l--;
	}
	return (r);
}
/*
int	main(void)
{
	printf("%d\n", uihlen(-42));
	printf("%s\n", ft_uitoh(42));
	printf("%s\n", ft_uitoh(-42));
	printf("%s\n", ft_uitoh( 100));
	printf("%s\n", ft_uitoh(-2147483648));
	return (0);
}*/