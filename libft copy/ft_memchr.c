/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 00:29:34 by saboulal          #+#    #+#             */
/*   Updated: 2022/11/03 21:44:46 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

void	*ft_memchr(const void *mb, int sc, size_t len)
{
	unsigned int	i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *)mb;
	while (i < len)
	{
		if (s[i] == (unsigned char )sc)
			return (s + i);
		i++;
	}
	return (NULL);
}
