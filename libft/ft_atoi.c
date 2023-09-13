/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:18:11 by saboulal          #+#    #+#             */
/*   Updated: 2022/11/03 21:40:46 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_isspace(char s)
{
	if (s == '\t' || s == '\v'
		|| s == '\r' || s == '\f'
		|| s == ' ' || s == '\n')
		return (1);
	return (0);
}

static int	ft_handel(long temp, long res, long sign)
{
	if (res / 10 != temp)
	{
		if (sign == -1)
			return (0);
		return (-1);
	}
	return (3);
}

int	ft_atoi(const char *str)
{
	long	res;
	long	sign;
	long	temp;
	int		i;

	sign = 1;
	res = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		temp = res;
		res = (res * 10) + str[i] - '0';
		if (ft_handel(temp, res, sign) != 3)
			return (ft_handel(temp, res, sign));
		i++;
	}
	return (res * sign);
}
