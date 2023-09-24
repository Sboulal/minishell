/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:48:54 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/24 08:22:18 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
char	*ft_strjoin(char const	*s1, char const		*s2)
{
	char	*s;
	size_t	len_s1;
	size_t	len_s2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	s = malloc (sizeof(char) * (len_s1 + len_s2 + 1));
	if (!s)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[j])
		s[len_s1++] = s2[j++];
	s[len_s1] = '\0';
	
	return (s);
}
char	*ft_strjoin2(char	*s1, char	*s2)
{
	char	*s;
	size_t	len_s1;
	size_t	len_s2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	s = malloc (sizeof(char) * (len_s1 + len_s2 + 1));
	if (!s)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[j])
		s[len_s1++] = s2[j++];
	s[len_s1] = '\0';
	free(s1);	
	return (s);
}

char	*ft_strjoin3(char	*s1, char	*s2)
{
	char	*s;
	size_t	len_s1;
	size_t	len_s2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	s = malloc (sizeof(char) * (len_s1 + len_s2 + 1));
	if (!s)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[j])
		s[len_s1++] = s2[j++];
	s[len_s1] = '\0';
	free(s1);
	free(s2);
	return (s);
}