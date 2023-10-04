/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:15:00 by saboulal          #+#    #+#             */
/*   Updated: 2022/11/12 02:29:19 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void	*dst, void	*src, size_t	n)
{
	char	*s;
	char	*a ;
	size_t	i;

	s = (char *)dst ;
	a = (char *)src;
	i = 0;
	if (src == dst)
		return (dst);
	while (i < n)
	{
		s[i] = a[i];
		i++;
	}
	return (s);
}
