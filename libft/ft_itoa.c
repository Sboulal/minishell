/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:01:06 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 01:10:59 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*check_n(int nb)
{
	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	if (nb == 0)
		return (ft_strdup("0"));
	return (NULL);
}

static int	ft_len(int nb)
{
	int		len;

	len = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

static char	*ft_etap(char *p, long n, int i)
{
	i = ft_len(n);
	if (!p)
		return (0);
	p[i--] = '\0';
	if (n == 0)
	{
		p[0] = 48;
		return (p);
	}
	if (n < 0)
	{
		p[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		p[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (p);
}

char	*ft_itoa(int nb)
{
	char	*str;
	int		i;

	if (nb == -2147483648 || nb == 0)
		return (check_n(nb));
	i = ft_len(nb);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str = ft_etap(str, nb, i);
	if (!str)
		return (0);
	str[i] = '\0';
	return (str);
}
