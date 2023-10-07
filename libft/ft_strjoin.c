/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:48:54 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 01:37:49 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	norm_s(char *s1, char *s2)
{
	int	len_s1;
	int	len_s2;

	if (!s1 || !s2)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	return (0);
}

int	norm_3(char *s, char *s1)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	return (0);
}
