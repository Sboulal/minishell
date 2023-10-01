/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:43:09 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/28 20:58:31 by saboulal         ###   ########.fr       */
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

char *to_string(char c)
{
	char *s;
	s = malloc(2);
	s[0] = c;
	s[1] = '\0';

	return s;
}

char	*get_name(char *token ,t_envp *env) 
{
	int	i;

	i = 0;
	char *str = ft_strdup("");
	int k;
	char *key;
	char *val;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] == '?')
		{
			str = ft_strjoin3(str, (ft_itoa(g_var.status)));
			i += 2;
			continue;
		}
		if (token[i] == '$' && token[i + 1] == '\0')
		{
			str = ft_strjoin2(str, "$");
			i++;
			continue;
		}
		else if (token[i] == '\'')
		{
			k = i;
			i = next_quote(i + 1, token[i], token);
			key = ft_substr(token, k, i - k - 1);
			str = ft_strjoin3(str, key);
		}
		if (token[i] == '$')
		{
			i++;
			if (!(ft_isalpha(token[i]) || token[i] == '_'))
			{
				str = ft_strjoin2(str, "$");
				if (token[i] == '\0')
					break;
				str = ft_strjoin3(str, to_string(token[i++]));
				continue;
			}
			k = i;
			while (is_identifier(token[i]))
				i++;
			key = ft_substr(token, k, i - k);
			val = get_env_value(key, env);
			if (ft_strlen(val) != 0)
				str = ft_strjoin2(str, val);
			if (val)
				free(val);
			continue;
		}
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

char	*get_env_value(char *name, t_envp *env)
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
