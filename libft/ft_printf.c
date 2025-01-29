/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:11:32 by kyang             #+#    #+#             */
/*   Updated: 2024/11/15 19:52:11 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_type(const char *s, int *i, va_list args, int *c)
{
	(*i)++;
	if (s[*i] == 'c')
		*c += ft_printf_c(args);
	else if (s[*i] == 's')
		*c += ft_printf_s(args);
	else if (s[*i] == 'p')
		*c += ft_printf_p(args);
	else if (s[*i] == 'd' || s[*i] == 'i')
		*c += ft_printf_d(args);
	else if (s[*i] == 'u')
		*c += ft_printf_u(args);
	else if (s[*i] == 'x')
		*c += ft_printf_hl(args);
	else if (s[*i] == 'X')
		*c += ft_printf_hu(args);
	else if (s[*i] == '%')
	{
		ft_putchar('%');
		*c += 1;
	}
	(*i)++;
}

int	ft_printf(const char *s, ...)
{
	va_list		args;
	int			i;
	int			c;

	va_start(args, s);
	i = 0;
	c = 0;
	while (s[i])
	{
		while (s[i] != '%' && s[i])
		{
			ft_putchar(s[i++]);
			c++;
		}
		if (s[i])
			ft_print_type(s, &i, args, &c);
	}
	va_end(args);
	return (c);
}
