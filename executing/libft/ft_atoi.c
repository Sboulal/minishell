/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:36:26 by nkhoudro          #+#    #+#             */
/*   Updated: 2022/11/01 18:09:43 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_at(const char *str, int sgn)
{
	long	i;
	long	res;
	long	rv;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		rv = res;
		res = (res * 10) + (str[i] - '0');
		if (res / 10 != rv)
		{
			if (sgn == -1)
				return (0);
			return (-1);
		}
		i++;
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	long	i;
	long	sgn;
	long	res;

	i = 0;
	sgn = 1;
	res = 0;
	while ((str[i] > 8 && str[i] < 14) || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sgn *= (-1);
		i++;
	}
	res = ft_at(str + i, sgn);
	return (res * sgn);
}
