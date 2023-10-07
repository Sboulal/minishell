/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:43:09 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 00:54:06 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

int	get_name_len(char *token, int i)
{
	int	name_len;

	name_len = 1;
	if (token[i + 1] == '?')
		return (-1);
	if (!(ft_toupper(token[i + 1]) || ft_tolower(token[i + 1])
			|| token[i + 1] == '_'))
		return (0);
	name_len = 1;
	while (is_env_name(token[i + 1]))
	{
		i++;
		name_len++;
	}
	return (name_len);
}

char	*to_string(char c)
{
	char	*s;

	s = malloc(2);
	s[0] = c;
	s[1] = '\0';
	return (s);
}

int	expand_exit(char *token, int *i, char **str)
{
	if (token[*i] == '$' && token[(*i) + 1] == '?')
	{
		*str = ft_strjoin3(*str, (ft_itoa(g_var.status)));
		(*i) += 2;
		return (1);
	}
	return (0);
}

int	expand_exit_null(char *token, int *i, char **str)
{
	if (token[*i] == '$' && token[(*i) + 1] == '\0')
	{
		*str = ft_strjoin2(*str, "$");
		(*i)++;
		return (1);
	}
	return (0);
}

int	expand_do_nor(char *token, int **i, char **str)
{
	if (!(ft_isalpha(token[**i]) || token[**i] == '_' ))
	{
		*str = ft_strjoin2(*str, "$");
		if (token[**i] == '\0')
			return (2);
		*str = ft_strjoin3(*str, to_string(token[(**i)++]));
		return (0);
	}
	return (1);
}
