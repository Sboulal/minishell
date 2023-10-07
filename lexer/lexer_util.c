/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:45:16 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 01:17:12 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

int	next_quote(int i, char quote, char *str)
{
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}

static char	*get_next_word(char *s, int *index)
{
	int		i;
	int		j;
	int		k;
	char	*word;

	k = 0;
	i = *index;
	while ((s[i] == ' ' || s[i] == '\t') && s[i])
		i++;
	j = i;
	while (!(s[i] == ' ' || s[i] == '\t') && s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i = next_quote(i + 1, s[i], s);
		i++;
	}
	word = ft_calloc(i - j + 1);
	while (j < i)
	{
		word[k] = s[j];
		k++;
		j++;
	}
	*index = i;
	return (word);
}

int	count_string(char *str)
{
	int	count;
	int	i;
	int	flag;

	flag = 1;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			if (str[i] == '"' || str[i] == '\'')
				i = next_quote(i + 1, str[i], str);
			if (i == -1)
				return (-1);
			if (flag != 0)
				count++;
			flag = 0;
		}
		else
			flag = 1;
		i++;
	}
	return (count);
}

char	**skip_vid(char *str)
{
	char	**res;
	int		wc;
	int		i;
	int		j;

	wc = count_string(str);
	if (wc == -1)
		return (NULL);
	res = malloc((wc + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (i < wc)
	{
		res[i] = get_next_word(str, &j);
		i++;
	}
	res[i] = NULL;
	return (res);
}
