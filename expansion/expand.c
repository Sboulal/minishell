/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:32:32 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/24 22:21:11 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../headers/lexer.h"

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
	if(!token)
		return(NULL);
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

t_lexer	*remove_empty_tokens(t_lexer *tokens, t_lexer *head, t_lexer *prev)
{
	while (tokens)
	{
		if (*(tokens->token) == 0)
		{
			if (prev == NULL)
			{
				head = tokens->next;
				free_token_word(tokens, tokens->token);
				tokens = head;
			}
			else
			{
				prev->next = tokens->next;
				free_token_word(tokens, tokens->token);
				tokens = prev->next;
			}
		}
		else
		{
			prev = tokens;
			tokens = tokens->next;
		}
	}
	return (head);
}

char *remove_quote(char *str)
{
	int i;
	char *src;
	char *sr;
	int j;
	

	i = 0;
	if (!str)
		return (NULL);
	src = ft_strdup("");
	while(str[i])
	{
		if(str[i] == '"')
		{
			j = i;
			while (str[j] && str[j] == '"')
				j++;
			i = j;
			while (str[j] && str[j] != '"')
				j++;
			sr = ft_substr(str, i, j - i);
			src = ft_strjoin3(src, sr);
			i = j;
		}
		else if(str[i] == '\'')
		{
			j = i;
			while (str[j] && str[j] == '\'')
				j++;
			i = j;
			while (str[j] && str[j] != '\'')
				j++;
			sr = ft_substr(str, i, j - i);
			src = ft_strjoin3(src, sr);
			i = j;
		}
		else
		{
			j = i;
			while (str[j] && (str[j] != '\'' && str[j] != '"'))
				j++;
			sr = ft_substr(str, i, j);
			src = ft_strjoin3(src, sr);
			i = i + (j - i);
		}
		if (!str[i])
			break;
		i++;
	}
	free(str);
	return (src);
}

t_lexer	*expand_lexer(t_lexer *tokens,t_envp *env)
{
	t_lexer	*token;
	t_lexer	*head;

	token = tokens;
	while (token)
	{
		if (token->type == WORD)
		{
			token->token = get_name(token->token,env);
			token = word_spliting(token);
		}
		token = token->next;
	}
	token = tokens;
	tokens = remove_empty_tokens(token, token, NULL);
	head = tokens;
	while (tokens)
	{
		if (tokens->type == WORD && tokens->token)
			tokens->token = remove_quote(tokens->token);
		tokens = tokens->next;
	}
	return (head);
}
