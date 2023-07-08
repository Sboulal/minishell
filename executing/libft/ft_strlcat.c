/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:37:46 by nkhoudro          #+#    #+#             */
/*   Updated: 2022/10/29 15:55:04 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lents;
	size_t	i;
	size_t	j;
	size_t	lnsrc;

	i = 0;
	lnsrc = ft_strlen(src);
	if (dstsize == 0)
		return (lnsrc);
	lents = ft_strlen(dst);
	j = lents;
	if (dstsize <= lents)
		return (dstsize + lnsrc);
	while ((j < dstsize - 1) && i < lnsrc)
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (lents + lnsrc);
}
