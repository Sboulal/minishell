/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_norm_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 00:53:23 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 00:53:56 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

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