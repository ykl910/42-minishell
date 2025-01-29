/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:11:44 by kyang             #+#    #+#             */
/*   Updated: 2024/11/13 15:04:42 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_word(char const *s, char c)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	while (s[i])
	{
		if (!(s[i] == c || s[i] == '\0')
			&& (s[i + 1] == c || s[i + 1] == '\0'))
			t++;
		i++;
	}
	return (t);
}

char	**free_all(char **r, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free (r[i]);
		i++;
	}
	free (r);
	return (NULL);
}

void	fill(char const *s, char *r, int k, int *i)
{
	int	m;

	m = 0;
	while (m < k)
	{
		r[m] = s[*i + m];
		m++;
	}
	r[m] = '\0';
	*i += m;
}

int	allo(char const *s, char c, char **r, int j)
{
	int	i;
	int	k;

	i = 0;
	while (s[i])
	{
		if (s[i] == c || s[i] == '\0')
			i++;
		else
		{
			k = 0;
			while ((s[i + k] == c || s[i + k] == '\0') == 0)
				k++;
			r[j] = malloc(sizeof(char) * (k + 1));
			if (!r[j])
				return (free_all(r, j) != NULL);
			fill(s, r[j], k, &i);
			j++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**r;
	int		t;

	if (!s)
		return (NULL);
	t = count_word(s, c);
	r = malloc(sizeof(char *) * (t + 1));
	if (!r)
		return (NULL);
	if (!allo(s, c, r, 0))
		return (NULL);
	r[t] = 0;
	return (r);
}

// int	main(void) 
// {
// 	char	**r = ft_split("hello! there !  you ", '!');
// 	int	i = 0;
// 	while (r[i])	
// 	{
// 		printf("%s\n", r[i]);
// 		i++;
// 	}
// 	return (0);
// }