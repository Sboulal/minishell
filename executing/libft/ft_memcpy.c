/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:37:24 by nkhoudro          #+#    #+#             */
/*   Updated: 2022/11/01 11:45:36 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy( void	*destination, const void	*source, size_t size )
{
	char	*src;
	char	*dst;
	size_t	i;

	src = (char *)source;
	dst = destination;
	i = 0;
	if (dst == src)
		return (dst);
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}
