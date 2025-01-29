/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:11:43 by kyang             #+#    #+#             */
/*   Updated: 2024/11/17 22:56:16 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdint.h> 
# include "./libft.h"

int		ft_printf_c(va_list args);
int		ft_printf_s(va_list args);
int		ft_printf_p(va_list args);
int		ft_printf_d(va_list args);
int		ft_printf_u(va_list args);
int		ft_printf_hl(va_list args);
int		ft_printf_hu(va_list args);

void	ft_putchar(char c);
void	ft_putstr(char *s);
void	ft_putp(unsigned long int nb);
void	ft_putnbr(int nb);
void	ft_putuint(unsigned int nb);
void	ft_puthex_l(unsigned int nb);
void	ft_puthex_u(unsigned int nb);

int		ft_printf(const char *s, ...);

#endif