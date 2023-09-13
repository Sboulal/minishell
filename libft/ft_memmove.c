/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:40:16 by saboulal          #+#    #+#             */
/*   Updated: 2022/11/06 09:58:01 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char *)dest;
	b = (unsigned char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (b > a)
	{
		while (i < len)
		{
			a[i] = b[i];
			i++;
		}
	}
	else
	{
		while (len--)
		{
			a[len] = b[len];
		}
	}
	return (dest);
}
