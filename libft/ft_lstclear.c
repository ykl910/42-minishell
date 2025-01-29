/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:25:55 by kyang             #+#    #+#             */
/*   Updated: 2024/11/11 12:39:16 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	del(void *content)
{
	free(content);
}*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*t;

	if (lst && del)
	{
		while (*lst)
		{
			t = (*lst)->next;
			del((*lst)->content);
			free(*lst);
			*lst = t;
		}
		*lst = NULL;
	}
}
/*
int 	main()
{
	// Create a simple linked list with three nodes
	t_list *head = ft_lstnew(malloc(sizeof(int)));
	t_list *second = ft_lstnew(malloc(sizeof(int)));
	t_list *third = ft_lstnew(malloc(sizeof(int)));

	// Check allocation
	if (!head || !second || !third) {
		printf("Memory allocation failed\n");
		return 1;
	}

	// Set values for each node's content
	*(int *)(head->content) = 1;
	*(int *)(second->content) = 2;
	*(int *)(third->content) = 3;

	// Link the nodes
	head->next = second;
	second->next = third;

	// Print list content before clearing
	printf("List content before clearing:\n");
	t_list *current = head;
	while (current) {
		printf("%d -> ", *(int *)(current->content));
		current = current->next;
	}
	printf("NULL\n");

	// Clear the list
	ft_lstclear(&head, del);

	// Verify that the list has been cleared
	if (head == NULL) {
		printf("List has been successfully cleared.\n");
	} else {
		printf("List clearing failed.\n");
	}

	return 0;
}*/
