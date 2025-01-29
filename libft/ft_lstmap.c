/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:37:10 by kyang             #+#    #+#             */
/*   Updated: 2024/11/11 12:39:32 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
void	del(void *content)
{
	free(content);
}

void	*f(void *content)
{
	int *new_content = malloc(sizeof(int));
	if (new_content) 
	{
		*new_content = *((int *)content) + 1;
	}
	return new_content;
}*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*t;

	if (!lst)
		return (NULL);
	new_lst = 0;
	while (lst)
	{
		t = ft_lstnew(f(lst->content));
		if (!t)
		{
			ft_lstclear(&new_lst, del);
			return (0);
		}
		ft_lstadd_back(&new_lst, t);
		lst = lst->next;
	}
	return (new_lst);
}
/*
void print_list(t_list *lst) {
    while (lst) {
        printf("%d -> ", *(int *)lst->content);
        lst = lst->next;
    }
    printf("NULL\n");
}

int main() {
    t_list *lst = NULL;
    t_list *mapped_lst;

    // Creating a test list with integers
    int *value1 = malloc(sizeof(int));
    *value1 = 5;
    t_list *node1 = ft_lstnew(value1);

    int *value2 = malloc(sizeof(int));
    *value2 = 10;
    t_list *node2 = ft_lstnew(value2);

    int *value3 = malloc(sizeof(int));
    *value3 = 15;
    t_list *node3 = ft_lstnew(value3);

    // Building the linked list
    ft_lstadd_back(&lst, node1);
    ft_lstadd_back(&lst, node2);
    ft_lstadd_back(&lst, node3);

    // Print original list
    printf("Original list:\n");
    print_list(lst);

    // Apply ft_lstmap to increment each element by 1
    mapped_lst = ft_lstmap(lst, f, del);

    // Print the new list after transformation
    printf("Mapped list (after incrementing each value by 1):\n");
    print_list(mapped_lst);

    // Free original list (content will be freed by ft_lstclear)
    ft_lstclear(&lst, del);

    // Free mapped list (content will be freed by ft_lstclear)
    ft_lstclear(&mapped_lst, del);

    return 0;
}*/