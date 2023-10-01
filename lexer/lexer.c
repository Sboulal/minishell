/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:09:34 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/28 20:59:04 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

int	is_operator(char c)
{
	if (c == '&'  || c == '(')
		return (1);
	if (c == ')' || c == '>' || c == '<')
		return (1);
	if (c == '|')
		return (1);
	return (0);
}

int	position_of_operator(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i = next_quote(i + 1, s[i], s);
		if (is_operator(s[i]))
			return (i);
		i++;
	}
	return (-1);
}

void	free_tokens(t_lexer *tokens)
{	
	t_lexer	*prev;
	// t_lexer	*head;

	// head = tokens;
	while (tokens)
	{
		prev = tokens;
		if (prev->token)
		{
			free(prev->token);
			prev->token = NULL;
		}
		if (prev)
		{
			free(prev);
			prev = NULL;
		}
		tokens = tokens->next;
	}
	// head = NULL;
}
void	free_all(t_lexer *tokens)
{
	t_lexer	*prev;

	while (tokens)
	{
		prev = tokens;
		free(tokens->token);
		tokens = tokens->next;
		free(prev);
	}
}