/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:59:34 by kyang             #+#    #+#             */
/*   Updated: 2024/11/06 19:40:48 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*r;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	r = malloc(sizeof(char) * (i + 1));
	if (!r)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	return (r);
}
/*
int	main(void) 
{
	char *result_ft;
	char *result_std;

	// Test 1: Basic String
	result_ft = ft_strdup("Hello, World!");
	result_std = strdup("Hello, World!");
	printf("Test 1 - Basic String:\n");
	printf("ft_strdup: %s\n", result_ft);
	printf("strdup: %s\n\n", result_std);
	free(result_ft);
	free(result_std);

	// Test 2: Empty String
	result_ft = ft_strdup("");
	result_std = strdup("");
	printf("Test 2 - Empty String:\n");
	printf("ft_strdup: %s\n", result_ft);
	printf("strdup: %s\n\n", result_std);
	free(result_ft);
	free(result_std);

	// Test 3: String with Special Characters
	result_ft = ft_strdup("Special chars: \t\n\r\\\"'");
	result_std = strdup("Special chars: \t\n\r\\\"'");
	printf("Test 3 - Special Characters:\n");
	printf("ft_strdup: %s\n", result_ft);
	printf("strdup: %s\n\n", result_std);
	free(result_ft);
	free(result_std);

	// Test 4: Long String
	result_ft = ft_strdup("This is a very long string to test 
if ft_strdup handles longer inputs without errors.");
	result_std = strdup("This is a very long string to test 
if ft_strdup handles longer inputs without errors.");
	printf("Test 4 - Long String:\n");
	printf("ft_strdup: %s\n", result_ft);
	printf("strdup: %s\n\n", result_std);
	free(result_ft);
	free(result_std);

	return 0;
}*/
