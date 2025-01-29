/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:12:29 by kyang             #+#    #+#             */
/*   Updated: 2024/11/06 19:12:41 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ilen(long n)
{
	int	l;

	l = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		l += 1;
	}
	while (n > 0)
	{
		l++;
		n /= 10;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	int		l;
	char	*r;
	long	num;

	num = n;
	l = ilen(n);
	r = malloc(sizeof(char) * (l + 1));
	if (!r)
		return (NULL);
	r[l] = '\0';
	if (n < 0)
		num *= -1;
	while (l > 0)
	{
		r[l - 1] = (num % 10) + 48;
		num /= 10;
		l--;
	}
	if (n < 0)
		r[0] = '-';
	return (r);
}
/*
int	main(void)
{
	printf("%d\n", ilen(-42));
	printf("%s\n", ft_itoa(42));
	printf("%s\n", ft_itoa(-42));
	printf("%s\n", ft_itoa( 100));
	printf("%s\n", ft_itoa(-2147483648));
	return (0);
}*/