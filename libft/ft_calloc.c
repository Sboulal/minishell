/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:30:53 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 02:09:14 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_calloc(size_t nm)
{
	void	*p;

	p = (char *)malloc(nm);
	if (!p)
		return (NULL);
	ft_bzero(p, nm);
	return (p);
}
