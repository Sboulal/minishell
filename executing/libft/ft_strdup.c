/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:59:45 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/07/12 10:19:13 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*c;
	int		i;

	i = 0;
	c = malloc(sizeof(char ) * (ft_strlen((char *)s1) + 1));
	if (c == NULL)
		return (NULL);
	if (!s1)
	{
		c[i] = '\0';
		return (c);
	}
	while (s1[i])
	{
		c[i] = (char )s1[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}
