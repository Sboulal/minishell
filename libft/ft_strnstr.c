/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:42:35 by saboulal          #+#    #+#             */
/*   Updated: 2022/11/09 01:02:01 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;
	char	*s;

	s = (char *)str;
	i = 0;
	j = 0;
	if (!to_find[j])
		return (s);
	if (n == 0)
		return (NULL);
	while (s[i] != '\0' && i < n)
	{
		while (s[i + j] && to_find[j] && to_find[j] == s[i + j] && (i + j) < n)
			j++;
		if (!to_find[j])
			return (s + i);
		j = 0;
		i++;
	}
	return (NULL);
}
