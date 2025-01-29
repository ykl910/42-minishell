/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:02:47 by kyang             #+#    #+#             */
/*   Updated: 2024/12/11 17:07:25 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int hex_char_to_int(char c)
{
	if (c >= '0' && c <= '9') {
		return c - '0';
	} else if (c >= 'A' && c <= 'F') {
		return c - 'A' + 10;
	} else if (c >= 'a' && c <= 'f') {
		return c - 'a' + 10;
	}
	return (-1);
}

int ft_hextoi(const char* hex_str)
{
	int	result;
	int	i;
	int	digit;

	result = 0;
	i = 0;
	if (hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X'))
	{
		i = 2;
	}
	while (hex_str[i])
	{
		digit = hex_char_to_int(hex_str[i]);
		if (digit == -1)
			return (-1);
		result = result * 16 + digit;
		i++;
	}
	return (result);
}
