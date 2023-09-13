/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:01:09 by nkhoudro          #+#    #+#             */
/*   Updated: 2022/11/01 12:11:45 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_in_set(char s1, char const *set)
{
	int	i;

	i = 0;
	while ((char)set[i])
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	int		i;
	int		j;
	int		d;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && ft_is_in_set(s1[i], set) == 1)
			i++;
	j = ft_strlen(s1);
	while (j > i && ft_is_in_set(s1[j - 1], set) == 1)
		j--;
	p = malloc((j - i) + 1);
	d = 0;
	if (p == NULL)
		return (NULL);
	while (i < j)
		p[d++] = s1[i++];
	p[d] = '\0';
	return (p);
}
