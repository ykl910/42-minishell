/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:58:20 by kyang             #+#    #+#             */
/*   Updated: 2024/11/12 11:42:35 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count != 0 && (count * size) / count != size)
		return (NULL);
	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, (count * size));
	return (p);
}
/*
int	main(void) 
{
	int *int_ptr;
	char *char_ptr;
	int test_passed;
	size_t i;

	// Test 1: Small Allocation (5 ints)
	int_ptr = (int *)ft_calloc(5, sizeof(int));
	test_passed = 1;
	if (int_ptr) {
		for (i = 0; i < 5; i++) {
			if (int_ptr[i] != 0) {
				test_passed = 0;
				break;
			}
		}
	} else {
		test_passed = 0;
	}
	printf("Test 1 - Small Allocation (5 ints): \
	%s\n", test_passed ? "PASSED" : "FAILED");
	free(int_ptr);

	// Test 2: Large Allocation (1000 chars)
	char_ptr = (char *)ft_calloc(1000, sizeof(char));
	test_passed = 1;
	if (char_ptr) {
		for (i = 0; i < 1000; i++) {
			if (char_ptr[i] != 0) {
				test_passed = 0;
				break;
			}
		}
	} else {
		test_passed = 0;
	}
	printf("Test 2 - Large Allocation (1000 chars): \
	%s\n", test_passed ? "PASSED" : "FAILED");
	free(char_ptr);

	// Test 3: Zero Allocation (count = 0)
	int_ptr = (int *)ft_calloc(0, sizeof(int));
	printf("Test 3 - Zero Allocation (count = 0): \
	%s\n", int_ptr ? "PASSED" : "FAILED");
	free(int_ptr);

	// Test 4: Zero Size Parameter (size = 0)
	int_ptr = (int *)ft_calloc(5, 0);
	printf("Test 4 - Zero Size Parameter (size = 0): \
	%s\n", int_ptr ? "PASSED" : "FAILED");
	free(int_ptr);
	return 0;
}*/
