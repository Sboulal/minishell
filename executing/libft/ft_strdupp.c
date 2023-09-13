/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:16:13 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/07/12 11:21:37 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdupp(const char *s1)
{
	char	*c;
	int		i;
	int		j;

	i = 0;
	c = malloc(sizeof(char ) * (ft_strlen((char *)s1) + 1));
	if (c == NULL)
		return (NULL);
	if (!s1)
	{
		c[i] = '\0';
		return (c);
	}
    j = 0;
	while (s1[i])
	{
        if (s1[i] != '\'' && s1[i] != '\"')
        {
		    c[j] = (char )s1[i];
            j++;
        }
		i++;
	}
	c[j] = '\0';
	return (c);
}