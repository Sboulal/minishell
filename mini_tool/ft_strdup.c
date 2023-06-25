/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:54:29 by saboulal          #+#    #+#             */
/*   Updated: 2023/06/10 16:54:52 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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