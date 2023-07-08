/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:37:15 by nkhoudro          #+#    #+#             */
/*   Updated: 2022/10/31 15:15:51 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	ch;

	ch = (unsigned char)c;
	p = (unsigned char *)s;
	while (n-- > 0)
	{
		if (*p == ch)
			return (p);
			p++;
	}
	return (NULL);
}
