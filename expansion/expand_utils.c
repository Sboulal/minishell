/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:43:09 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/06 20:53:59 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/lexer.h"

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

// this function returns the first occurence of a variable name 
// if we have an occurence of a $ alone we just mark it with -1 
// to not interump with further calls to this function
// we will change the -1 latter

char *to_string(char c)
{
	char *s;
	s = malloc(2);
	s[0] = c;
	s[1] = '\0';

	return s;
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

int	expand_do(char *token, int *i, char **str, t_envp *env)
{
	int k;
	char *key;
	char *val;

	if (token[*i] == '$')
	{
		(*i)++;
		if (expand_do_nor(token, &i, str) == 0)
			return (0);
		if (expand_do_nor(token, &i, str) == 2)
			return (2);
		k = *i;
		while (is_identifier(token[*i]))
			(*i)++;
		key = ft_substr(token, k, (*i) - k);
		val = get_env_value(key, env);
		free(key);
		if (ft_strlen(val) != 0)
			*str = ft_strjoin2(*str, val);
		free(val);
		return (0);
	}
	return (1);
}

char	*get_name_quot(char *token ,t_envp *env) // get value
{
	int	i;

	i = 0;
	char *str = ft_strdup("");
	while (token[i])
	{
		if (expand_exit(token, &i, &str))
			continue;
		if (expand_exit_null(token, &i, &str))
			continue;
		if (!expand_do(token, &i, &str, env))
			continue;
		else if (expand_do(token, &i, &str, env) == 2)
			break;
		str = ft_strjoin3(str, to_string(token[i]));
		i++;
	}
	return (str);
}


int	expand_singl(char *token, int *i, char **str)
{
	int	k;

	if (token[*i] == '\'')
	{
		k = *i;
		k++;
		*i = next_quote((*i) + 1, token[*i], token);
		while (k < (*i))
		{
			if (token[k] && token[k] != '\'')
				*str = ft_strjoin3(*str, to_string(token[k]));
			k++;
		}
		(*i)++;
		return (1);
	}
	return (0);
}

int	expand_doubl(char *token, int *i, char **str, t_envp *env)
{
	int	k;
	char *key;
	char *s;

	if (token[*i] == '"')
	{
		k = *i;
		*i = next_quote((*i) + 1, token[*i], token);
		key = ft_substr(token, k + 1, (*i) - k - 1);
		s = get_name_quot(key, env);
		free(key);
		*str = ft_strjoin3(*str, s);
		(*i)++;
		return (1);
	}
	return (0);
}
char	*get_name(char *token ,t_envp *env) // get value
{
	int	i;
	char *str;

	i = 0;
	str = ft_strdup("");
	while (token[i])
	{
		if (expand_exit(token, &i, &str))
			continue;
		if (expand_exit_null(token, &i, &str))
			continue;
		if (expand_singl(token, &i, &str))
			continue;
		if (expand_doubl(token, &i, &str, env))
			continue;
		if (!expand_do(token, &i, &str, env))
			continue;
		else if (expand_do(token, &i, &str, env) == 2)
			break;
		str = ft_strjoin3(str, to_string(token[i]));
		i++;
	}
	free(token);
	return (str);
}


int	replace_before_name(char *new_token, char *token)
{
	int	i;
	int	dbl_quotes;
	int	sgl_quotes;

	dbl_quotes = 0;
	sgl_quotes = 0;
	i = 0;
	while (token[i] != '$' || sgl_quotes)
	{
		if (token[i] == '\'' && !dbl_quotes)
			sgl_quotes = !sgl_quotes;
		if (token[i] == '"')
			dbl_quotes = !dbl_quotes;
		new_token[i] = token[i];
		i++;
	}
	return (i);
}

char	*get_env_value(char *name,t_envp *env)
{
	t_envp	*tmp;

	tmp = env;
	if (*name == '?')
		return (ft_itoa(g_var.status));
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (!ft_strcmp(tmp->variable, name))
		{
			if (tmp->value)
				return (ft_strdup(tmp->value));
			return (ft_strdup(""));
		}
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}
