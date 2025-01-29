/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:53:32 by kyang             #+#    #+#             */
/*   Updated: 2024/11/06 19:39:09 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t					i;
	const unsigned char		*d1;
	const unsigned char		*d2;

	i = 0;
	d1 = (const unsigned char *)s1;
	d2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (d1[i] != d2[i])
			return (d1[i] - d2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void) 
{
	// Test 1: Basic Comparison
	const char arr1[] = "Hello";
	const char arr2[] = "Hello";
	printf("Test 1 - Basic Comparison:\n");
	printf("Standard memcmp result: %d\n", memcmp(arr1, arr2, sizeof(arr1)));
	printf("ft_memcmp result: %d\n\n", ft_memcmp(arr1, arr2, sizeof(arr1)));

	// Test 2: Different Arrays
	const char arr3[] = "Hello";
	const char arr4[] = "World";
	printf("Test 2 - Different Arrays:\n");
	printf("Standard memcmp result: %d\n", memcmp(arr3, arr4, sizeof(arr3)));
	printf("ft_memcmp result: %d\n\n", ft_memcmp(arr3, arr4, sizeof(arr3)));

	// Test 3: Partial Comparison
	const char arr5[] = "Hello, World!";
	const char arr6[] = "Hello, Everyone!";
	printf("Test 3 - Partial Comparison:\n");
	printf("Standard memcmp result: %d\n", memcmp(arr5, arr6, 5)); 
	printf("ft_memcmp result: %d\n\n", ft_memcmp(arr5, arr6, 5));

	// Test 5: Null Terminator in Comparison
	const char arr9[] = "Hello\0World";
	const char arr10[] = "Hello\0Everyone";
	printf("Test 5 - Null Terminator in Comparison:\n");
	printf("Standard memcmp result: %d\n", memcmp(arr9, arr10, sizeof(arr9)));
	printf("ft_memcmp result: %d\n\n", ft_memcmp(arr9, arr10, sizeof(arr9)));

	// Test 6: Same Prefix, Different Suffix
	const char arr11[] = "Hello, World!";
	const char arr12[] = "Hello, Universe!";
	printf("Test 6 - Same Prefix, Different Suffix:\n");
	printf("Standard memcmp result: %d\n", memcmp(arr11, arr12, sizeof(arr11)));
	printf("ft_memcmp result: %d\n\n", ft_memcmp(arr11, arr12, sizeof(arr11)));
	return 0;
}*/
