/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:30:53 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/13 17:25:36 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../headers/lexer.h"
void	*ft_calloc(size_t nm)
{

	void	*p;

	p = (char *)malloc(nm);
	if (!p)
		return (NULL);
	ft_bzero(p, nm);
	return (p);
}
