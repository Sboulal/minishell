/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:20:15 by nkhoudro          #+#    #+#             */
/*   Updated: 2022/11/01 18:29:25 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcon(size_t d, char const *s1, char const *s2)
{
	char		*p;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	p = ft_calloc(1, d);
	if (!p)
		return (NULL);
	while (i < d)
	{
		if (i < ft_strlen(s1))
			p[i] = s1[i];
		else
			p[i] = s2[j++];
		i++;
	}
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		d;
	size_t		j;
	int			mys2;
	char		*p;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	mys2 = ft_strlen(s2);
	d = ft_strlen(s1) + mys2 + 1;
	p = ft_strcon(d, s1, s2);
	return (p);
}
