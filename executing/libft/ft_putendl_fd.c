/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 21:59:48 by nkhoudro          #+#    #+#             */
/*   Updated: 2022/10/29 15:50:37 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	n;
	int		i;

	i = 0;
	n = '\n';
	if (s != NULL)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
		write(fd, &n, 1);
	}
}
