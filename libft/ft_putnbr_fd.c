/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:01:57 by saboulal          #+#    #+#             */
/*   Updated: 2022/11/03 21:29:39 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	long int	n;

	n = nb;
	if (n < 0)
	{
		ft_putchar_fd ('-', fd);
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr_fd ((n / 10), fd);
		ft_putnbr_fd ((n % 10), fd);
	}
	else
	{
		ft_putchar_fd ((n + '0'), fd);
	}
}
