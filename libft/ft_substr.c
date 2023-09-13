/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:34:55 by saboulal          #+#    #+#             */
/*   Updated: 2023/06/10 16:53:43 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	unsigned int	count;

	i = 0;
	if (!s)
		return (NULL);
	count = ft_strlen(s);
	if (start > count)
		return (ft_strdup(""));
	if (count <= start + len)
		len = count - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	while (s[start] && i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
