/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_norm_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 00:53:23 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 06:25:11 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expand_do(char *token, int *i, char **str, t_envp *env)
{
	int		k;
	char	*key;
	char	*val;

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

char	*get_name_quot(char *token, t_envp *env)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup("");
	while (token[i])
	{
		if (expand_exit(token, &i, &str))
			continue ;
		if (expand_exit_null(token, &i, &str))
			continue ;
		if (!expand_do(token, &i, &str, env))
			continue ;
		else if (expand_do(token, &i, &str, env) == 2)
			break ;
		str = ft_strjoin3(str, to_string(token[i]));
		i++;
	}
	return (str);
}

t_lexer	*remove_empty_tokens(t_lexer *tokens, t_lexer *head, t_lexer *prev)
{
	while (tokens)
	{
		if (*(tokens->token) == 0)
		{
			remove_empty_norm(&tokens, &prev, &head);
		}
		else
		{
			prev = tokens;
			tokens = tokens->next;
		}
	}
	return (head);
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

void	remove_empty_norm(t_lexer **tokens, t_lexer **prev, t_lexer **head)
{
	if (*prev == NULL)
		remove_empty_first(tokens, head);
	else if (!(*tokens)->next)
		remove_empty_last(tokens, prev);
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
