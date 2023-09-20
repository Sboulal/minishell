/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:32:32 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/20 18:24:24 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../headers/lexer.h"

// this function copies the token string into a new 
// allocated string without copying the -1 occurenccense=

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
int cont_word(char *token)
{
	int i;
	int wc;

	wc = 0;
	i = 0;
	if (!token)
		return (0);
	while(token[i])
	{
		if(!is_identifier(token[i]))
			wc++;
		i++;	
	}
	if (is_identifier(token[i - 1]))
		wc++;
	return (wc);
}

int	ft_count_len_word(char *token)
{
	int i;

	i = 0;
	if (!token)
		return (0);
	while (token[i])
	{
		if (i != 0 && !is_identifier(token[i]))
			return (i);
		i++;
	}
	return (i);
}
char	*quotes_removal(char *token)
{
	int		i;
	char	c;
	int		quotes_len;

	i = 0;
	quotes_len = 0;
	if (!token)
		return (0);
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
char	**expand_dollars(char *token)
{
	int		i;
	char	**str;
	int 	k;
	int 	d;
	int		wc;
	int		quotes_len;
	int j;
	i = 0;
	quotes_len = 0;
	if (!token)
		return (NULL);
	wc = cont_word(token);
	str = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!str)
		return (NULL);
	k = 0;
	while (k < wc)
	{
		if (!is_identifier(token[i]))
		{
			if (token[i] != '\'')
			{
				quotes_len = ft_count_len_word(token + i);
				str[k] = ft_substr(token, i, quotes_len);
				k++;
				i = i + quotes_len;
			}
			else
			{
				i++;
				j = i;
				while (token[j] && token[j] !='\'')
					j++; 
				str[k] = ft_substr(token, i - 1, j + 1);
				k++;
				i = i + j;
			}
		}
		else 
		{
			d = number_word_ident(token);
			str[k] = ft_substr(token, i, d);
			k = k + 1;
			i = i + d;
		}
	}
	str[k] = NULL;
	return (free(token), str);
}
// char *delete_d(char *token, int *i)
// {
// 	int j;
// 	char *str;

// 	j = (*i);
// 	if (token[*i] &&  token[*i] == '"')
// 	{
// 		while(token[(*i)] && token[(*i)] != '"')
// 			(*i)++;
// 		str = ft_substr(token, j + 1, (*i) - 1);
// 			return (str);
// 	}
// 	while(token[(*i)] && token[(*i)] != '"')
// 		(*i)++;
// 	if ((token[(*i)] && token[*i] == '"'))
// 		str = ft_substr(token, j, (*i) - 1);
// 	return (str);
// }
char *delete_sing(char *token, int *i, char c)
{
	int j;
	char *str;

	j = (*i);
	str = NULL;
	if (token[*i] &&(token[*i] == c))
	{
		(*i)++;
		while(token[(*i)] && (token[(*i)] != c))
			(*i)++;
		if (token[(*i)])
			str = ft_substr(token, j + 1, (*i) - 1);
		else
			str = ft_substr(token, j + 1, (*i));
			return (str);
	}
	while(token[(*i)] && (token[(*i)] != c))
		(*i)++;
	if ((token[(*i)] && (token[*i] == c)))
		str = ft_substr(token, j, (*i) - 1);
	return (str);
}
char *delete(char *token, int *i)
{
	int j;
	char *str;

	j = (*i);
	while(token[(*i)] && (token[*i] != '\'' || token[*i] != '"'))
		(*i)++;
	str = ft_substr(token, j, (*i));
	return (str);
}
char *add_to(char *token, int *i)
{
	int j;
	char *str;

	j = (*i);
	(*i)++;
	while(token[(*i)] && token[(*i)] != '"' && token[(*i)] != '\'')
		(*i)++;
	str = ft_substr(token, j, (*i));
	return (str);
}
char *removal(char *token)
{
	int i;
	char *str;

	i = 0;
	if (!token)
		return (NULL);
	str = ft_strdup("");
	while (token[i])
	{
		if (token[i] == '"')
			str = ft_strjoin(str, delete_sing(token , &i, '"'));
		else if (token[i] == '\'')
			str = ft_strjoin(str, delete_sing(token , &i, '\''));
		else
			str = ft_strjoin(str, delete(token , &i));
	}
	return (str);
}
void tt(void)
{
	system("leaks minishell");
}
t_lexer *expand_lexer(t_lexer *our_lexer, t_envp *env)
{
	t_lexer *head;
	t_lexer *lexer;
	// t_lexer *l;
	char *s;
	char **str;

	head = our_lexer;
	lexer = NULL;
	while(head)
	{
		if(head->type == WORD)
		{
			// printf("%s", head->token);
			s = head->token;
			str = expand_dollars(s);
			// printf("%s\n", *str);
			add_back(&lexer, ft_strdup(parameter_expansion(str, env)));
			// l = lexer;
			// while (l && l->next)
			// 	l = l->next;
			// if (l->token)
			// 	l = word_spliting(l);
		}
		else
			add_back(&lexer, ft_strdup(head->token));
		head = head->next;
	}
	token_herdoc(lexer);
	head = lexer;
	while(head)
	{
		if(head->type == WORD)
			head->token = removal(head->token);
		head = head->next;
	}
	return (lexer);
}