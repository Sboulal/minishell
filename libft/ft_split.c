/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:45:51 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/10 15:49:38 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*tabfree(char **tab)
{
	size_t	j;

	j = 0;
	while (tab[j])
		free(tab[j++]);
	free(tab);
	return (NULL);
}

static int	words(char const *str, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] && str[i] != c)
		{
			i++;
			j++;
		}
		while (str[i] && str[i] != c)
			i++;
	}
	return (j);
}

static char	**alloc_fill(const char *s, int start, int end, char c)
{
	char	**tab;
	int		i;

	i = 0;
	tab = (char **) malloc((words(s, c) + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	while (i < words(s, c) && s[start])
	{
		start = end;
		while (s[start] && s[start] == c)
			start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		tab[i] = ft_substr(s, start, end - start);
		if (!tab[i])
		{
			tabfree(tab);
			return (NULL);
		}
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		start;
	int		end;

	end = 0;
	start = 0;
	if (!s)
		return (NULL);
	tab = alloc_fill(s, start, end, c);
	if (!tab)
		return (NULL);
	return (tab);
}
