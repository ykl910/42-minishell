/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:31:38 by kyang             #+#    #+#             */
/*   Updated: 2024/11/16 12:00:28 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putp(unsigned long int nb)
{
	if (nb >= 16)
		ft_putp(nb / 16);
	ft_putchar("0123456789abcdef"[nb % 16]);
}

int	ft_printf_p(va_list args)
{
	void		*p;
	uintptr_t	add;
	char		*s;
	int			c;

	p = va_arg(args, void *);
	add = (uintptr_t)p;
	if (!add || add == 0)
	{
		ft_putstr("(nil)");
		return (5);
	}
	ft_putstr("0x");
	ft_putp(add);
	s = ft_uitoh(add);
	c = ft_strlen(s) + 2;
	free(s);
	return (c);
}
