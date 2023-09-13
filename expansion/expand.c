/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:32:32 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/12 20:36:39 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../lexer.h"

char	*trim_quotes(char *token, int quotes_len)
{
	char	*trimed_token;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(token);
	trimed_token = ft_calloc(len - quotes_len + 1);
	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] != -1)
		{
			trimed_token[j] = token[i];
			j++;
		}
		i++;
	}
	free(token);
	return (trimed_token);
}

char	*quotes_removal(char *token)
{
	int		i;
	char	c;
	int		quotes_len;

	i = 0;
	quotes_len = 0;
	while (token[i])
	{
		if (token[i] == '"' || token[i] == '\'')
		{
			c = token[i];
			token[i] = -1;
			i = next_quote(i + 1, c, token);
			token[i] = -1;
			quotes_len++;
		}
		i++;
	}
	if (!quotes_len)
		return (token);
	return (trim_quotes(token, quotes_len));
}

t_lexer *expand_lexer(t_lexer *our_lexer)
{
	t_lexer *lexer;
	t_lexer *first;

	lexer = our_lexer;
	while(lexer)
	{
		if(lexer->type== WORD)
		{
			lexer->token = parameter_expansion(lexer->token);
			lexer = word_spliting(lexer);
		}
		lexer = lexer->next;
	}
	lexer = our_lexer;
	our_lexer = remove_empty_tokens(lexer,lexer,NULL);
	first = our_lexer;
	while(our_lexer)
	{
		if(lexer->type == WORD)
			our_lexer->token = quotes_removal(our_lexer->token);
		our_lexer = our_lexer->next;
	}
	return (first);
}