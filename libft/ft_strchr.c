/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:20:46 by saboulal          #+#    #+#             */
/*   Updated: 2022/11/03 21:27:30 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *str, int search)
{
	unsigned int	i;
	char			*s;

	i = 0;
	s = (char *)str;
	while (s[i] != (char)search && s[i])
	{
		i++;
	}
	if (s[i] == (char)search)
	{
		return (&s[i]);
	}
	return (0);
}
