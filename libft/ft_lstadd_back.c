/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:23:43 by kyang             #+#    #+#             */
/*   Updated: 2024/11/11 12:39:06 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (new && lst)
	{
		if (*lst == NULL)
		{
			*lst = new;
		}
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}
/*
void	print_list(t_list *lst) 
{
    while (lst) {
        printf("%d -> ", *(int *)lst->content);
        lst = lst->next;
    }
    printf("NULL\n");
}

int	main() 
{
    t_list *head = NULL;
    t_list *new_node;

    // Test case 1: Adding a single element to an empty list
	int *data1 = malloc(sizeof(int));
	if (data1 == NULL) 
		return 1; // Handle allocation failure
	*data1 = 42;
    new_node = ft_lstnew(data1);
    ft_lstadd_back(&head, new_node);
    printf("List after adding 42: ");
    print_list(head);

    // Test case 2: Adding another element
	int *data2 = malloc(sizeof(int));
	if (data2 == NULL) 
		return 1; // Handle allocation failure
	*data2 = 43;
    new_node = ft_lstnew(data2);
    ft_lstadd_back(&head, new_node);
    printf("List after adding 43: ");
    print_list(head);

    // Test case 3: Adding more elements
	int	*data3 = malloc(sizeof(int));
	if (data3 == NULL)
		return 1;
	*data3 = 44;
    new_node = ft_lstnew(data3);
    ft_lstadd_back(&head, new_node);
    printf("List after adding 44: ");
    print_list(head);

    return 0;
}*/