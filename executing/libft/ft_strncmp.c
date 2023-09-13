/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:38:01 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/07/25 11:20:05 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*my_s1;
	unsigned char	*my_s2;
	size_t			i;

	i = 0;
	my_s1 = (unsigned char *)s1;
	my_s2 = (unsigned char *)s2;
	if (!my_s1)
		return( 0 - s2[i]);
	if (!my_s2)
		return( s1[i]);
	while (i < n && (my_s1[i] != '\0' || my_s2[i] != '\0'))
	{
		if (my_s1[i] != my_s2[i])
			return (my_s1[i] - my_s2[i]);
		i++;
	}
	return (0);
}
