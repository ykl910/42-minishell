/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:39:14 by kyang             #+#    #+#             */
/*   Updated: 2024/11/16 12:00:40 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putuint(unsigned int nb)
{
	if (nb >= 10)
		ft_putuint(nb / 10);
	ft_putchar("0123456789"[nb % 10]);
}

int	ft_printf_u(va_list args)
{
	unsigned int	i;
	char			*s;
	int				c;

	i = va_arg(args, unsigned int);
	ft_putuint(i);
	s = ft_uitoa(i);
	c = ft_strlen(s);
	free(s);
	return (c);
}
