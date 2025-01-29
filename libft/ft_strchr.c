/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:14:05 by kyang             #+#    #+#             */
/*   Updated: 2024/12/09 22:01:17 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
/*
int	main(void) 
{
	// Test 1: Basic Character Found
	const char *str1 = "Hello, World!";
	char ch1 = 'o';
	char *result1_std = strchr(str1, ch1);
	char *result1_ft = ft_strchr(str1, ch1);
	printf("Test 1 - Basic Character Found:\n");
	printf("Standard strchr result: %s\n", result1_std);
	printf("ft_strchr result: %s\n\n", result1_ft);

	// Test 2: Character Not Found
	const char *str2 = "Hello, World!";
	char ch2 = 'z';
	char *result2_std = strchr(str2, ch2);
	char *result2_ft = ft_strchr(str2, ch2);
	printf("Test 2 - Character Not Found:\n");
	printf("Standard strchr result: %s\n", result2_std);
	printf("ft_strchr result: %s\n\n", result2_ft);

	// Test 3: First Character
	const char *str3 = "Hello, World!";
	char ch3 = 'H';
	char *result3_std = strchr(str3, ch3);
	char *result3_ft = ft_strchr(str3, ch3);
	printf("Test 3 - First Character:\n");
	printf("Standard strchr result: %s\n", result3_std);
	printf("ft_strchr result: %s\n\n", result3_ft);

	// Test 4: Last Character
	const char *str4 = "Hello, World!";
	char ch4 = '!';
	char *result4_std = strchr(str4, ch4);
	char *result4_ft = ft_strchr(str4, ch4);
	printf("Test 4 - Last Character:\n");
	printf("Standard strchr result: %s\n", result4_std);
	printf("ft_strchr result: %s\n\n", result4_ft);

	// Test 5: Empty String
	const char *str5 = "";
	char ch5 = 'a';
	char *result5_std = strchr(str5, ch5);
	char *result5_ft = ft_strchr(str5, ch5);
	printf("Test 5 - Empty String:\n");
	printf("Standard strchr result: %s\n", result5_std);
	printf("ft_strchr result: %s\n\n", result5_ft);

	// Test 6: Null Character
	const char *str6 = "Hello, World!";
	char ch6 = 0;
	char *result6_std = strchr(str6, ch6);
	char *result6_ft = ft_strchr(str6, ch6);
	printf("Test 6 - Null Character:\n");
	printf("Standard strchr result: %s\n", result6_std);
	printf("ft_strchr result: %s\n\n", result6_ft);

	printf("libftTester:%d\n",ft_strchr(str6, 'H' + 256) == str6);
	printf("%s",ft_strchr(str6, 'H' + 256));
	return 0;
}*/