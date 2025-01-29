/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:23:58 by kyang             #+#    #+#             */
/*   Updated: 2024/11/11 12:39:20 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	del(void *content)
{
	free(content);
}
*/
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}
/*
int	main() 
{
	// Allocate memory for content and create a node
	int *data = malloc(sizeof(int));
	if (data == NULL) 
		return 1; // Handle allocation failure
	*data = 42;

	// Create a list node with the data
	t_list *node = ft_lstnew(data);

	// Print address of content and node before deletion
	printf("Node address: %p\n", (void *)node);
	printf("Node content address: %p (Expected to be freed)\n", \
	 (void *)node->content);
	printf("Node content value: %d\n", *(int *)node->content);

	// Delete the node using ft_lstdelone
	ft_lstdelone(node, del);

	// After deleting, you cannot safely access node or node->content.
	printf("Node and content should now be freed.\n");

	return 0;
}*/
