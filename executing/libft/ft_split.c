/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:31:09 by nkhoudro          #+#    #+#             */
/*   Updated: 2022/11/01 10:52:41 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **p, int last)
{
	int	i;

	i = 0;
	while (i < last)
	{
		free(p[i]);
		i++;
	}
	free(p);
}

static int	ft_skip(char const *s, int i, char c);

static int	ft_malloc(char const *s, char **p, char c, int nwords)
{
	int	i;
	int	j;
	int	r;

	j = 0;
	r = 0;
	while (r < nwords)
	{
		j = ft_skip(s, j, c);
		i = 0;
		while (s[j] && s[j] != c)
		{
			i++;
			j++;
		}
		p[r] = (char *)malloc(sizeof(char) * (i + 1));
		if (!p[r])
		{
			ft_free(p, r);
			return (0);
		}
		r++;
	}
	return (1);
}

static int	ft_skip(char const *s, int i, char c)
{
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

static int	ft_word(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		i = ft_skip(s, i, c);
		if (s[i] && s[i] != c)
			words++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		count;
	int		i;
	int		j;
	int		r;

	if (!s)
		return (NULL);
	count = ft_word(s, c);
	p = (char **) malloc(sizeof(char *) * (count + 1));
	if (!p || ft_malloc(s, p, c, count) == 0)
		return (NULL);
	j = 0;
	i = 0;
	while (j < count)
	{
		r = 0;
		i = ft_skip(s, i, c);
		while (s[i] && s[i] != c)
			p[j][r++] = s[i++];
		p[j][r] = '\0';
		j++;
	}
	p[j] = NULL;
	return (p);
}
