/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 00:38:11 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 08:18:27 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_quote_else(char **str, int *i, char **src)
{
	int		j;
	char	*sr;

	j = *i;
	while (*str[j] && (*str[j] != '\'' && *str[j] != '"'))
		j++;
	sr = ft_substr(*str, *i, j);
	*src = ft_strjoin(*src, sr);
	*i = (*i) + (j - (*i));
}

char	*remove_quote(char *str)
{
	int		i;
	char	*src;

	i = 0;
	if (!str)
		return (NULL);
	src = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '"')
			remove_quote_d(&str, &i, &src);
		else if (str[i] == '\'')
			remove_quote_s(&str, &i, &src);
		else
			remove_quote_else(&str, &i, &src);
		if (!str[i])
			break ;
		i++;
	}
	return (src);
}

t_lexer	*expand_lexer(t_lexer *tokens, t_envp *env)
{
	t_lexer	*token;
	t_lexer	*head;

	token = tokens;
	while (token)
	{
		if (token->type == WORD)
		{
			token = word_spliting(token);
			token->token = get_name(token->token, env, token);
		}
		token = token->next;
	}
	token = tokens;
	tokens = remove_empty_tokens(token, token, NULL);
	head = tokens;
	return (head);
}

void	remove_quote_d(char **str, int *i, char **src)
{
	int		j;
	char	*sr;

	j = *i;
	while (*str[j] && *str[j] == '"')
		j++;
	*i = j;
	while (*str[j] && *str[j] != '"')
		j++;
	sr = ft_substr(*str, *i, j - (*i));
	*src = ft_strjoin(*src, sr);
	*i = j;
}

void	remove_quote_s(char **str, int *i, char **src)
{
	int		j;
	char	*sr;

	j = *i;
	while (*str[j] && *str[j] == '\'')
		j++;
	*i = j;
	while (*str[j] && *str[j] != '\'')
		j++;
	sr = ft_substr(*str, *i, j - (*i));
	*src = ft_strjoin(*src, sr);
	*i = j;
}
