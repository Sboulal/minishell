/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:49:08 by saboulal          #+#    #+#             */
/*   Updated: 2023/07/11 21:26:36 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	*ft_calloc(size_t em, size_t emz)
{
	size_t	i;
	char	*p;

	i = 0;
	if ((em * emz) / emz != em)
		return (NULL);
	p = (char *)malloc(em * emz);
	if (!p)
		return (NULL);
	ft_bzero(p, em * emz);
	return (p);
}