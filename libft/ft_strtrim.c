/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:43:57 by saboulal          #+#    #+#             */
/*   Updated: 2022/11/03 21:18:36 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

static int	ft_count(char c, const char *set)
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

char	*ft_strtrim(char const *s1, char const *set)
{
	int	a;
	int	z;

	a = 0;
	if (!s1 || !set)
		return (NULL);
	z = ft_strlen(s1) - 1;
	if (s1[a] == '\0')
		return (ft_strdup(""));
	while (s1[a] && ft_count(s1[a], set))
		a++;
	while (s1[z] && ft_count(s1[z], set))
		z--;
	if (z == -1)
	{
		return (ft_substr(s1, a, 0));
	}
	return (ft_substr(s1, a, (z - a + 1)));
}
