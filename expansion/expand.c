/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:32:32 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 05:53:58 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	return (trimed_token);
}

char	*quotes_removal(char *token)
{
	int		i;
	char	c;
	int		quotes_len;

	i = 0;
	quotes_len = 0;
	if (!token)
		return (NULL);
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

void	free_node(t_lexer *tokens)
{
	if (tokens->token)
		free(tokens->token);
	tokens->token = NULL;
	free(tokens);
	tokens = NULL;
}

void	remove_empty_first(t_lexer **tokens, t_lexer **prev, t_lexer **head)
{
	t_lexer	*tmp;

	(void)prev;
	if (!(*tokens)->next || (*tokens)->type == LIMITER)
	{
		if ((*tokens)->y == 1)
		{
			if ((*tokens)->token)
				free((*tokens)->token);
			(*tokens)->token = ft_strdup("");
			(*tokens) = (*tokens)->next;
		}
		else 
		{
			tmp = (*tokens)->next;
			free_node((*tokens));
			(*tokens) = tmp;
			(*head) = (*tokens);
		}
	}
	else
	{
		if ((*tokens)->y == 1)
		{
			if ((*tokens)->token)
				free((*tokens)->token);
			(*tokens)->token = ft_strdup("");
			(*tokens) = (*tokens)->next;
		}
		else 
		{
			tmp = (*tokens)->next;
			free_node((*tokens));
			(*tokens) = tmp;
			(*head) = (*tokens);
		}
	}
}

void	remove_empty_norm(t_lexer **tokens, t_lexer **prev, t_lexer **head)
{
	if (*prev == NULL)
	{
		remove_empty_first(tokens, prev, head);
	}
	else if (!(*tokens)->next)
	{
		if ((*tokens)->y == 1)
		{
			if ((*tokens)->token)
				free((*tokens)->token);
			(*tokens)->token = ft_strdup("");
			(*tokens) = (*tokens)->next;
		}
		else
		{
			free_node((*tokens));
			(*prev)->next = NULL;
			(*tokens) = (*prev)->next;
		}
	}
	else
	{
		if ((*tokens)->y == 1)
		{
			if ((*tokens)->token)
				free((*tokens)->token);
			(*tokens)->token = ft_strdup("");
			(*tokens) = (*tokens)->next;
		}
		else
		{
			(*prev)->next = (*tokens)->next;
			free_node((*tokens));
			(*tokens) = (*prev)->next;
		}
	}
}
