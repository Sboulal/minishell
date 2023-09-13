/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 00:31:30 by saboulal          #+#    #+#             */
/*   Updated: 2022/11/03 21:20:54 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *f, const char *s, size_t len)
{
	size_t	i;

	i = 0;
	if ((!f || !s) && !len)
		return (0);
	while ((f[i] || s[i]) && i < len)
	{
		if (f[i] != s[i])
			return ((unsigned char )f[i] - (unsigned char )s[i]);
		i++;
	}
	return (0);
}
