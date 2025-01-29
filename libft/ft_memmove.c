/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:15:58 by kyang             #+#    #+#             */
/*   Updated: 2024/11/06 16:34:54 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	i = 0;
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (d < s)
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (len > 0)
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	}
	return (dst);
}
/*
int	main(void)
{
	// Test 1: Basic Test with Non-overlapping Memory
	char src1[] = "Hello, World!";
	char dst1[20];
	memmove(dst1, src1, 13);
	ft_memmove(dst1, src1, 13);

	printf("Test 1 - Non-overlapping memory:\n");
	printf("memmove result: %s\n", dst1);
	printf("ft_memmove result: %s\n\n", dst1);

	// Test 2: Overlapping Memory (dst after src)
	char overlap_src1[] = "1234567890";
	memmove(overlap_src1 + 4, overlap_src1, 6);
	ft_memmove(overlap_src1 + 4, overlap_src1, 6);

	printf("Test 2 - Overlapping (dst after src):\n");
	printf("memmove result: %s\n", overlap_src1);
	printf("ft_memmove result: %s\n\n", overlap_src1);

	// Test 3: Overlapping Memory (dst before src)
	char overlap_src2[] = "abcdefghij";
	memmove(overlap_src2, overlap_src2 + 3, 7);
	ft_memmove(overlap_src2, overlap_src2 + 3, 7);

	printf("Test 3 - Overlapping (dst before src):\n");
	printf("memmove result: %s\n", overlap_src2);
	printf("ft_memmove result: %s\n\n", overlap_src2);

	// Test 4: Zero bytes to copy
	char src4[] = "This is a test";
	char dst4[20] = "No change";
	memmove(dst4, src4, 0);
	ft_memmove(dst4, src4, 0);

	printf("Test 4 - Zero bytes to copy:\n");
	printf("memmove result: %s\n", dst4);
	printf("ft_memmove result: %s\n\n", dst4);

	// Test 5: Copy within the same memory block (dst == src)
	char same_block[] = "Overlap test";
	memmove(same_block, same_block, 12);
	ft_memmove(same_block, same_block, 12);

	printf("Test 5 - Copy within the same memory block:\n");
	printf("memmove result: %s\n", same_block);
	printf("ft_memmove result: %s\n\n", same_block);

	return 0;
}*/
