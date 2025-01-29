/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:52:03 by kyang             #+#    #+#             */
/*   Updated: 2024/11/12 16:59:35 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*str;

	i = 0;
	str = (const unsigned char *)s;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return ((void *)&str[i]);
		i++;
	}
	return (0);
}
/*
int	main(void) 
{
	// Test 1: Basic Character Found (multiple occurrences)
	const char arr1[] = "Hello, World!";
	int ch1 = 'o';
	printf("Test 1 - Basic Character Found:\n");
	printf("Standard memchr result: %s\n", \
	(char *)memchr(arr1, ch1, sizeof(arr1)));
	printf("ft_memchr result: %s\n\n", \
	(char *)ft_memchr(arr1, ch1, sizeof(arr1)));

	// Test 2: Character Not Found
	const char arr2[] = "Hello, World!";
	int ch2 = 'z';
	printf("Test 2 - Character Not Found:\n");
	printf("Standard memchr result: %s\n", \
	(char *)memchr(arr2, ch2, sizeof(arr2)));
	printf("ft_memchr result: %s\n\n", \
	(char *)ft_memchr(arr2, ch2, sizeof(arr2)));

	// Test 3: First Byte in Array
	const char arr3[] = "Hello, World!";
	int ch3 = 'H';
	printf("Test 3 - First Byte in Array:\n");
	printf("Standard memchr result: %s\n", \
	(char *)memchr(arr3, ch3, sizeof(arr3)));
	printf("ft_memchr result: %s\n\n", \
	(char *)ft_memchr(arr3, ch3, sizeof(arr3)));

	// Test 4: Last Byte in Array
	const char arr4[] = "Hello, World!";
	int ch4 = '!';
	printf("Test 4 - Last Byte in Array:\n");
	printf("Standard memchr result: %s\n", \
	(char *)memchr(arr4, ch4, sizeof(arr4)));
	printf("ft_memchr result: %s\n\n", \
	(char *)ft_memchr(arr4, ch4, sizeof(arr4)));

	// Test 5: Null Byte
	const char arr5[] = "Hello\0World";
	int ch5 = '\0';
	printf("Test 5 - Null Byte:\n");
	printf("Standard memchr result: %s\n", \
	(char *)memchr(arr5, ch5, sizeof(arr5)));
	printf("ft_memchr result: %s\n\n", \
	(char *)ft_memchr(arr5, ch5, sizeof(arr5)));

	return 0;
}*/
