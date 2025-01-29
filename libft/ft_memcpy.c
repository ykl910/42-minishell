/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:11:03 by kyang             #+#    #+#             */
/*   Updated: 2024/11/06 16:15:47 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	i = 0;
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
/*
int main(void)
{
	char buffer1[20] = "Original string";
	char buffer2[20] = "Original string";
	char src1[] = "New data";
	char src2[] = "New data";

	// Test 1: Copy a string
	memcpy(buffer1, src1, sizeof(src1));
	ft_memcpy(buffer2, src2, sizeof(src2));

	printf("Test 1 - Copy string\n");
	printf("Standard memcpy result: %s\n", buffer1);
	printf("ft_memcpy result:       %s\n\n", buffer2);

	// Test 2: Copy integer array
	int int_src[] = {1, 2, 3, 4, 5};
	int int_dest1[5];
	int int_dest2[5];

	memcpy(int_dest1, int_src, sizeof(int_src));
	ft_memcpy(int_dest2, int_src, sizeof(int_src));

	printf("Test 2 - Copy integer array\n");
	printf("Standard memcpy result: ");
	for (int i = 0; i < 5; i++) printf("%d ", int_dest1[i]);
	printf("\nft_memcpy result:       ");
	for (int i = 0; i < 5; i++) printf("%d ", int_dest2[i]);
	printf("\n\n");
	return 0;
}*/
