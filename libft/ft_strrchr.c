/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:14:56 by kyang             #+#    #+#             */
/*   Updated: 2024/12/09 22:00:46 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	if (c == '\0')
		return ((char *)&s[i]);
	while (i > 0)
	{
		if ((unsigned char)s[i - 1] == (unsigned char)c)
			return ((char *)&s[i - 1]);
		i--;
	}
	return (0);
}
/*
int	main(void) 
{
	// Test 1: Basic Character Found (multiple occurrences)
	const char *str1 = "Hello, World!";
	char ch1 = 'o';
	printf("Test 1 - Basic Character Found:\n");
	printf("Standard strrchr result: %s\n", strrchr(str1, ch1));
	printf("ft_strrchr result: %s\n\n", ft_strrchr(str1, ch1));

	// Test 2: Character Not Found
	const char *str2 = "Hello, World!";
	char ch2 = 'z';
	printf("Test 2 - Character Not Found:\n");
	printf("Standard strrchr result: %s\n", strrchr(str2, ch2));
	printf("ft_strrchr result: %s\n\n", ft_strrchr(str2, ch2));

	// Test 3: First Character (from End)
	const char *str3 = "Hello, World!";
	char ch3 = 'H';
	printf("Test 3 - First Character (from End):\n");
	printf("Standard strrchr result: %s\n", strrchr(str3, ch3));
	printf("ft_strrchr result: %s\n\n", ft_strrchr(str3, ch3));

	// Test 4: Last Character
	const char *str4 = "Hello, World!";
	char ch4 = '!';
	printf("Test 4 - Last Character:\n");
	printf("Standard strrchr result: %s\n", strrchr(str4, ch4));
	printf("ft_strrchr result: %s\n\n", ft_strrchr(str4, ch4));

	// Test 5: Empty String
	const char *str5 = "";
	char ch5 = 'a';
	printf("Test 5 - Empty String:\n");
	printf("Standard strrchr result: %s\n", strrchr(str5, ch5));
	printf("ft_strrchr result: %s\n\n", ft_strrchr(str5, ch5));

	// Test 6: Null Character
	const char *str6 = "Hello, World!";
	char ch6 = '\0';
	printf("Test 6 - Null Character:\n");
	printf("Standard strrchr result: %s\n", strrchr(str6, ch6));
	printf("ft_strrchr result: %s\n\n", ft_strrchr(str6, ch6));

	return 0;
}*/
