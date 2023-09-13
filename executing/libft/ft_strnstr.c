/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:38:08 by nkhoudro          #+#    #+#             */
/*   Updated: 2022/10/31 15:40:12 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		if (len - i < ft_strlen(needle))
			return (NULL);
		if (ft_strncmp(haystack + i, needle, ft_strlen(needle)) == 0)
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
