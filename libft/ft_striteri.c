/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:13:41 by kyang             #+#    #+#             */
/*   Updated: 2024/11/06 19:41:18 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void	do_sth(unsigned int i, char *c)
{
	if (i % 2 == 0)
		*c = '0';
}

int	main(void)
{
	char	a[] = "aaaa";
	ft_striteri(a, do_sth);
	printf("%s", a);
	return (0);
}*/
