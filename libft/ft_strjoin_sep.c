/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_sep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:27:24 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/13 16:27:42 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_sep(char *s1, char *s2, char sep)
{
	int		i;
	int		j;
	char	*buffer;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	buffer = ft_calloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	while (s1[++i])
		buffer[i] = s1[i];
	buffer[i] = sep;
	j = i + 1;
	i = -1;
	while (s2[++i])
		buffer[j++] = s2[i];
	return (buffer);
}
