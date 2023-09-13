/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:37:29 by nkhoudro          #+#    #+#             */
/*   Updated: 2022/11/01 11:56:06 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*my_dst;
	unsigned char	*my_src;
	size_t			i;

	i = 0;
	my_dst = (unsigned char *)dst;
	my_src = (unsigned char *)src;
	if (my_dst == my_src)
		return (my_dst);
	if (dst > src)
	{
		while (len--)
		{
			my_dst[len] = my_src[len];
		}
	}
	else
	{
		while (i < len)
		{
			my_dst[i] = my_src[i];
			i++;
		}
	}
	return (dst);
}
