/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:19:02 by kyang             #+#    #+#             */
/*   Updated: 2024/11/11 12:39:39 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
/*
int	main() 
{
	// Test 1: Size of an empty list
	t_list *empty_list = NULL;
	printf("Test 1: Size of an empty list: \
	%d (Expected: 0)\n", ft_lstsize(empty_list));

	// Test 2: Size of a list with one element
	int *data = malloc(sizeof(int)); // Allocate memory for integer
	*data = 1;
	t_list *single_node = ft_lstnew(data);
	printf("Test 2: Size of a list with one element: \
	%d (Expected: 1)\n", ft_lstsize(single_node));

	// Test 3: Size of a list with multiple elements
	int *data1 = malloc(sizeof(int));
	*data1 = 2;
	int *data2 = malloc(sizeof(int));
	*data2 = 2;
	int *data3 = malloc(sizeof(int));
	*data3 = 3;

	t_list *node1 = ft_lstnew(data1);
	t_list *node2 = ft_lstnew(data2);
	t_list *node3 = ft_lstnew(data3);
	node1->next = node2;
	node2->next = node3;

	printf("Test 3: Size of a list with three elements: \
	%d (Expected: 3)\n", ft_lstsize(node1));

	// Free allocated memory
	free(single_node->content);
	free(single_node);

	// Free memory for the three nodes
	free(node1->content);
	free(node2->content);
	free(node3->content);
	free(node1);
	free(node2);
	free(node3);

	return 0;
}*/