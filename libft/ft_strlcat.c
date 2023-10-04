/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:30:16 by saboulal          #+#    #+#             */
/*   Updated: 2022/11/12 04:01:26 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{	
	size_t		x;
	size_t		y;
	size_t		l_dest;
	size_t		i;

	i = 0;
	x = ft_strlen(src);
	if (size == 0)
		return (x);
	y = ft_strlen(dest);
	l_dest = y;
	if (y >= size)
		return (x + size);
	while (l_dest < size - 1 && src[i])
	{
		dest[l_dest] = src[i++];
		l_dest++;
	}
	dest[l_dest] = '\0';
	return (y + x);
}
