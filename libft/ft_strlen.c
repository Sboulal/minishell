/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:01:45 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/14 22:07:24 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0 ;
	if (!str)
		return (i);
	while (str[i])
	{
		i++;
	}
	return (i);
}
