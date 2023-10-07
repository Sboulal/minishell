/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 00:52:20 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 06:11:50 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	int		k;
	char	*key;
	char	*s;

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

int get_name_u(char *token, t_envp *env, t_lexer *tokens, t_gn *gn)
{
	if (expand_exit(token, &gn->i, &gn->str))
		return (1);
	if (expand_exit_null(token, &gn->i, &gn->str))
		return (1);
	if (expand_singl(token, &gn->i, &gn->str))
	{
		tokens->y = 1;
		return (1);
	}
	if (expand_doubl(token, &gn->i, &gn->str, env))
	{
		tokens->y = 1;
		return (1);
	}
	return (0);
}

char	*get_name(char *token, t_envp *env, t_lexer *tokens)
{
	t_gn	gn;

	gn.i = 0;
	gn.str = ft_strdup("");
	while (token[gn.i])
	{
		if (get_name_u(token, env, tokens, &gn))
			continue ;
		if (!expand_do(token, &gn.i, &gn.str, env))
		{
			tokens->y = 2;
			continue ;
		}
		else if (expand_do(token, &gn.i, &gn.str, env) == 2)
		{
			tokens->y = 2;
			break ;
		}
		gn.str = ft_strjoin3(gn.str, to_string(token[gn.i]));
		gn.i++;
	}
	return (free(token), gn.str);
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
		return (ft_itoa(g_var.sig_status));
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
