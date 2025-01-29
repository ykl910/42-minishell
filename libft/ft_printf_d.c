/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:29:08 by kyang             #+#    #+#             */
/*   Updated: 2024/11/16 11:58:34 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int nb)
{
	long	n;
	int		x;

	n = nb;
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	if (n < 10)
	{
		x = n + 48;
		ft_putchar(x);
	}
	if (n >= 10)
	{
		x = (n % 10) + 48;
		n = n / 10;
		ft_putnbr(n);
		ft_putchar(x);
	}
}

int	ft_printf_d(va_list args)
{
	int		i;
	char	*s;
	int		c;

	i = va_arg(args, int);
	ft_putnbr(i);
	s = ft_itoa(i);
	c = ft_strlen(s);
	free(s);
	return (c);
}
