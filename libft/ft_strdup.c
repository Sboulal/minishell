/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:56:44 by saboulal          #+#    #+#             */
/*   Updated: 2022/11/03 21:26:58 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strdup(const char	*str)
{
	int		i;
	int		len;
	char	*s;

	i = 0;
	len = ft_strlen(str);
	s = malloc (len + 1);
	if (s == NULL)
		return (NULL);
	ft_strlcpy(s, str, len + 1);
	return (s);
}
