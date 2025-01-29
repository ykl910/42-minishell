/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:12:29 by kyang             #+#    #+#             */
/*   Updated: 2024/11/11 23:57:12 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	uilen(unsigned int n)
{
	int	l;

	l = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		l++;
		n /= 10;
	}
	return (l);
}

char	*ft_uitoa(unsigned int n)
{
	int		l;
	char	*r;

	l = uilen(n);
	r = malloc(sizeof(char) * (l + 1));
	if (!r)
		return (NULL);
	r[l] = '\0';
	while (l > 0)
	{
		r[l - 1] = (n % 10) + 48;
		n /= 10;
		l--;
	}
	return (r);
}
/*
int	main(void)
{
	printf("%d\n", uilen(-42));
	printf("%s\n", ft_uitoa(42));
	printf("%s\n", ft_uitoa(-42));
	printf("%s\n", ft_uitoa( 100));
	printf("%s\n", ft_uitoa(-2147483648));
	return (0);
}*/