/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:39:14 by kyang             #+#    #+#             */
/*   Updated: 2024/11/16 12:00:17 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex_u(unsigned int nb)
{
	if (nb >= 16)
		ft_puthex_u(nb / 16);
	ft_putchar("0123456789ABCDEF"[nb % 16]);
}

int	ft_printf_hu(va_list args)
{
	unsigned int	i;
	char			*s;
	int				c;

	i = va_arg(args, unsigned int);
	ft_puthex_u(i);
	s = ft_uitoh(i);
	c = ft_strlen(s);
	free(s);
	return (c);
}
