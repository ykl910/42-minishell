/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:21:59 by kyang             #+#    #+#             */
/*   Updated: 2024/11/11 12:39:27 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
/*
int main() {
	// Test 1: Last node of an empty list
	t_list *empty_list = NULL;
	t_list *last_node_empty = ft_lstlast(empty_list);
	printf("Test 1: Last node of an empty list: %s \
(Expected: NULL)\n", last_node_empty ? "Not NULL" : "NULL");

	// Test 2: Last node of a list with one element
	int *data1 = malloc(sizeof(int)); // Allocate memory for integer
	if (data1 == NULL) return 1; // Handle memory allocation failure
	*data1 = 4; // Assign value
	t_list *single_node = ft_lstnew(data1); // Create single node
	t_list *last_node_single = ft_lstlast(single_node);
	printf("Test 2: Last node of a single-element list: %p \
(Expected: %p)\n", last_node_single, single_node);

	// Test 3: Last node of a list with multiple elements
	int *data2 = malloc(sizeof(int)); // Allocate memory for second integer
	if (data2 == NULL) return 1; // Handle memory allocation failure
	*data2 = 2; // Assign value

	int *data3 = malloc(sizeof(int)); // Allocate memory for third integer
	if (data3 == NULL) return 1; // Handle memory allocation failure
	*data3 = 3; // Assign value

	t_list *node1 = ft_lstnew(data1);
	t_list *node2 = ft_lstnew(data2);
	t_list *node3 = ft_lstnew(data3);
	node1->next = node2;
	node2->next = node3;

	t_list *last_node_multi = ft_lstlast(node1);
	printf("Test 3: Last node of a multi-element list: %p \
(Expected: %p)\n", last_node_multi, node3);

	// Free allocated memory
//	free(single_node->content); // Free data from single node
	free(single_node); // Free the single node
	free(node1->content); // Free data from first node
	free(node1); // Free the first node
	free(node2->content); // Free data from second node
	free(node2); // Free the second node
	free(node3->content); // Free data from third node
	free(node3); // Free the third node

	return 0;
}*/
