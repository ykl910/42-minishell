/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:18:20 by kyang             #+#    #+#             */
/*   Updated: 2024/11/06 19:18:41 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
/*
int	main() 
{
	char *content = "Hello, world!";
	t_list *node = ft_lstnew(content);

	if (node) {
		printf("Node content: %s\n", node->content);
		free(node); // Free the allocated memory after use
	} else {
		printf("Memory allocation failed.\n");
	}
	return 0;
}*/
