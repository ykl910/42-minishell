/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:54:23 by kyang             #+#    #+#             */
/*   Updated: 2024/11/12 11:13:51 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] && needle[j] && \
			haystack[i + j] == needle[j] && (i + j) < len)
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}
/*
int	main(void) 
{
	// Test 1: Basic Match
	printf("Test 1 - Basic Match:\n");
	printf("ft_strnstr: %s\n", ft_strnstr("Hello, World!", "World", 13));
	printf("strnstr: %s\n\n", strnstr("Hello, World!", "World", 13));

	// Test 2: Partial Match Beyond Limit
	printf("Test 2 - Partial Match Beyond Limit:\n");
	printf("ft_strnstr: %s\n", ft_strnstr("Hello, World!", "World", 5));
	printf("strnstr: %s\n\n", strnstr("Hello, World!", "World", 5));

	// Test 3: Exact Match at End
	printf("Test 3 - Exact Match at End:\n");
	printf("ft_strnstr: %s\n", ft_strnstr("Hello, World!", "World", 12));
	printf("strnstr: %s\n\n", strnstr("Hello, World!", "World", 12));

	// Test 4: Substring Not Found
	printf("Test 4 - Substring Not Found:\n");
	printf("ft_strnstr: %s\n", ft_strnstr("Hello, World!", "Planet", 13));
	printf("strnstr: %s\n\n", strnstr("Hello, World!", "Planet", 13));

	// Test 5: Empty Haystack
	printf("Test 5 - Empty Haystack:\n");
	printf("ft_strnstr: %s\n", ft_strnstr("", "Hello", 5));
	printf("strnstr: %s\n\n", strnstr("", "Hello", 5));

	// Test 6: Empty Needle
	printf("Test 6 - Empty Needle:\n");
	printf("ft_strnstr: %s\n", ft_strnstr("Hello, World!", "", 5));
	printf("strnstr: %s\n\n", strnstr("Hello, World!", "", 5));

	// Test 7: Both Haystack and Needle Empty
	printf("Test 7 - Both Haystack and Needle Empty:\n");
	printf("ft_strnstr: %s\n", ft_strnstr("", "", 5));
	printf("strnstr: %s\n\n", strnstr("", "", 5));

	// Test 8: Zero Length (n = 0)
	printf("Test 8 - Zero Length (n = 0):\n");
	printf("ft_strnstr: %s\n", ft_strnstr("Hello, World!", "Hello", 0));
	printf("strnstr: %s\n\n", strnstr("Hello, World!", "Hello", 0));
	return 0;
}*/