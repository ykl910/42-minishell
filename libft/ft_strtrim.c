/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:10:32 by kyang             #+#    #+#             */
/*   Updated: 2024/11/13 11:17:41 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*fill_char(char const *s1, char *r, int i, int j)
{
	int	k;

	k = 0;
	while (k < j)
	{
		r[k] = s1[i + k];
		k++;
	}
	r[k] = '\0';
	return (r);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*r;
	int		l;
	int		i;
	int		j;
	int		b;

	l = ft_strlen(s1);
	b = l;
	i = 0;
	while (s1[i] && is_set(s1[i], set))
		i++;
	while (s1[b - 1] && is_set(s1[b - 1], set))
		b--;
	if (i + (l - b) < l)
		j = b - i;
	else
		j = l;
	r = malloc(sizeof(char) * (j + 1));
	if (!r)
		return (NULL);
	return (fill_char(s1, r, i, j));
}

// int	main(void) 
// {
// 	printf("%s\n", ft_strtrim("  true   ", " "));
// 	printf("%s\n", ft_strtrim("  true!   ", "! "));
// 	printf("%s\n", ft_strtrim("  true   ", ""));
// 	printf("%s\n", ft_strtrim("", " "));
// 	printf("%s\n", ft_strtrim("   xxx   xxx", " x"));
// 	printf("%s\n", ft_strtrim("   xxxtripouille   xxx", " x"));
// 	printf("%s\n", ft_strtrim("123", ""));
// 	printf("%s\n", ft_strtrim("", ""));
// 	printf("%s\n", ft_strtrim("", "123"));
// 	return 0;
// }