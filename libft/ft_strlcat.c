/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:46:41 by kyang             #+#    #+#             */
/*   Updated: 2024/11/11 12:40:35 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t			dl;
	size_t			sl;
	unsigned int	j;

	j = 0;
	dl = ft_strlen(dest);
	sl = ft_strlen(src);
	if (dl >= dstsize)
		return (sl + dstsize);
	while (src[j] && dl + j < dstsize - 1)
	{
		dest[dl + j] = src[j];
		j++;
	}
	dest[dl + j] = '\0';
	return (sl + dl);
}
/*
int	main(void)
{
	char s1[] = "Hello";
	char s2[] = " there";
	char s11[] = "Hello";
	char s22[] = " there";

	printf("%zu\n",ft_strlcat(s1, s2, 3));
	printf("%s\n",s1);

	printf("%zu\n",strlcat(s11, s22, 3));
	printf("%s\n", s11);
	return (0);
}*/
