/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:35:02 by kyang             #+#    #+#             */
/*   Updated: 2024/11/06 16:45:38 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (dstsize > 0)
	{
		while (i < dstsize - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[j])
		j++;
	return (j);
}
/*
int	main(void) 
{
	// Test 1: Basic Copy Test
	char dst1[20];
	const char src1[] = "Hello, World!";
	size_t len1_std = strlcpy(dst1, src1, sizeof(dst1));
	size_t len1_ft = ft_strlcpy(dst1, src1, sizeof(dst1));

	printf("Test 1 - Basic Copy Test:\n");
	printf("Standard strlcpy result: %s, length: %zu\n", dst1, len1_std);
	printf("ft_strlcpy result: %s, length: %zu\n\n", dst1, len1_ft);

	// Test 2: Exact Fit Test
	char dst2[13];
	const char src2[] = "Hello, World!";
	size_t len2_std = strlcpy(dst2, src2, sizeof(dst2));
	size_t len2_ft = ft_strlcpy(dst2, src2, sizeof(dst2));

	printf("Test 2 - Exact Fit Test:\n");
	printf("Standard strlcpy result: %s, length: %zu\n", dst2, len2_std);
	printf("ft_strlcpy result: %s, length: %zu\n\n", dst2, len2_ft);

	// Test 3: Truncation Test
	char dst3[8];
	const char src3[] = "Hello, World!";
	size_t len3_std = strlcpy(dst3, src3, sizeof(dst3));
	size_t len3_ft = ft_strlcpy(dst3, src3, sizeof(dst3));

	printf("Test 3 - Truncation Test:\n");
	printf("Standard strlcpy result: %s, length: %zu\n", dst3, len3_std);
	printf("ft_strlcpy result: %s, length: %zu\n\n", dst3, len3_ft);

	// Test 4: Empty Source Test
	char dst4[20];
	const char src4[] = "";
	size_t len4_std = strlcpy(dst4, src4, sizeof(dst4));
	size_t len4_ft = ft_strlcpy(dst4, src4, sizeof(dst4));

	printf("Test 4 - Empty Source Test:\n");
	printf("Standard strlcpy result: %s, length: %zu\n", dst4, len4_std);
	printf("ft_strlcpy result: %s, length: %zu\n\n", dst4, len4_ft);

	// Test 5: Empty Destination Size Test
	char dst5[10];
	const char src5[] = "Hello";
	size_t len5_std = strlcpy(dst5, src5, 0);
	size_t len5_ft = ft_strlcpy(dst5, src5, 0);

	printf("Test 5 - Empty Destination Size Test:\n");
	printf("Standard strlcpy length: %zu\n", len5_std);
	printf("ft_strlcpy length: %zu\n\n", len5_ft);

	// Test 6: Source Longer than Destination Test
	char dst6[4];
	const char src6[] = "ABCDEFG";
	size_t len6_std = strlcpy(dst6, src6, sizeof(dst6));
	size_t len6_ft = ft_strlcpy(dst6, src6, sizeof(dst6));

	printf("Test 6 - Source Longer than Destination Test:\n");
	printf("Standard strlcpy result: %s, length: %zu\n", dst6, len6_std);
	printf("ft_strlcpy result: %s, length: %zu\n\n", dst6, len6_ft);

	return 0;
}*/
