/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:09:47 by kyang             #+#    #+#             */
/*   Updated: 2024/11/06 16:10:55 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}
/*
int	main(void)
{
	char	buffer1[10];
	char	buffer2[10];
	int	i;

	bzero(buffer1, 10);
	ft_bzero(buffer2, 10);

	printf("Results of bzero: ");
	for (i = 0; i < 10; i++)
		printf("%d ", buffer1[i]);
	printf("\n");

	printf("Results of ft_bzero: ");
	for (i = 0; i < 10; i++)
		printf("%d ", buffer2[i]);
	printf("\n");
	return 0;
}*/
