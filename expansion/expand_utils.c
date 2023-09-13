/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:43:09 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/13 17:25:36 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../headers/lexer.h"

int	get_name_len(char *token, int i)
{
	int	name_len;

	if (token[i + 1] == '?')
		return (2);
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

char	*get_name_here(char *token)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = -1;
	while (token[i])
	{
		name_len = -1;
		if (token[i] == '$')
			name_len = get_name_len(token, i);
		if (name_len == 0)
			token[i] = -1;
		if (name_len > 0)
			break ;
		i++;
	}
	if (name_len == 0 || name_len == -1)
		return (NULL);
	return (ft_substr(token, i, i + name_len));
}

int	replace_before_name_here(char *new_token, char *token)
{
	int	i;

	i = 0;
	while (token[i] != '$')
	{
		new_token[i] = token[i];
		i++;
	}
	return (i);
}
char	*replace_name_value(char *token, char *name, char *value)
{
	char	*new_token;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	new_token = ft_calloc(ft_strlen(token)
			+ (ft_strlen(value) - ft_strlen(name)) + 1);
	i = replace_before_name_here(new_token, token);
	k = i;
	j = 0;
	while (value[j])
	{
		if (value[j] == '$')
			value[j] = -1;
		new_token[i++] = value[j++];
	}
	k += ft_strlen(name);
	while (token[k])
		new_token[i++] = token[k++];
	free(token);
	return (new_token);
}

char	*get_env_value(char *name)
{
	t_envp	*tmp;

	tmp = g_var.envp;
	if (*name == '?')
		return (ft_itoa(g_var.status));
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (!ft_strcmp(tmp->variable, name))
		{
			if (tmp->value)
				return (tmp->value);
			return ("");
		}
		tmp = tmp->next;
	}
	return ("");
}

char	*get_name(char *token)
{
	int	i;
	int	name_len;
	int	dbl_quote;

	i = 0;
	name_len = -1;
	dbl_quote = -1;
	while (token[i])
	{
		name_len = -1;
		if (token[i] == '"')
			dbl_quote *= -1;
		if (token[i] == '\'' && dbl_quote == -1)
			i = next_quote(i + 1, token[i], token);
		if (token[i] == '$')
			name_len = get_name_len(token, i);
		if (name_len == 0)
			token[i] = -1;
		if (name_len > 0)
			break ;
		i++;
	}
	if (name_len == 0 || name_len == -1)
		return (NULL);
	return (ft_substr(token, i, i + name_len));
}

char	*parameter_expansion(char *token)
{
	char	*name;
	char	*value;
	char	*new_token;

	name = get_name(token);
	if (!name)
	{
		expands_dollars_dollars(token);
		return (token);
	}
	value = get_env_value(name + 1);
	new_token = replace_name_value(token, name, value);
	if (*(name + 1) == '?')
		free(value);
	free(name);
	return (parameter_expansion(new_token));
}