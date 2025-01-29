/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:27:19 by kyang             #+#    #+#             */
/*   Updated: 2024/11/11 12:39:23 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
void    print_content(void *content) 
{
	printf("%d ", *(int *)content);
}

int main() {
	// Create a simple list with two nodes
	int	*data1 = malloc(sizeof(int));
	if (!data1)
		return 0;
	*data1 = 10;
	int	*data2 = malloc(sizeof(int));
	if (!data2)
		return 0;
	*data2 = 20;
	t_list *head = ft_lstnew(data1);
	head->next = ft_lstnew(data2);

	// Test ft_lstiter by printing each element's content
	printf("List contents:\n");
	ft_lstiter(head, print_content);
	printf("\n");

	// Free each node's content and the nodes themselves
	free(head->next->content);
	free(head->next);
	free(head->content);
	free(head);

	return 0;
}*/
