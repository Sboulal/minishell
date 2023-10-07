/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 09:08:42 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/07 09:09:25 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exand_do_quot(char *token, t_gn *gn, t_envp *env, int k)
{
	char	*key;
	char	*val;

	key = ft_substr(token, k + 1, (gn->i) - k - 2);
	val = get_env_value(key, env);
	if (ft_strcmp(gn->str, key) == 0)
	{
		if (gn->str)
			free(gn->str);
		free(key);
		gn->str = ft_strdup(val);
		free(val);
	}
	else
	{
		free(key);
		key = ft_substr(gn->str, 0, ft_strlen(gn->str) - ft_strlen(key));
		if (gn->str)
			free(gn->str);
		gn->str = ft_strjoin3(key, val);
	}
}

char	*ft_strdup_1(char	*str)
{
	int		len;
	char	*s;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	s = malloc (len + 1);
	if (s == NULL)
		return (NULL);
	ft_strlcpy(s, str, len + 1);
	free(str);
	return (s);
}

int	expand_dolar(char *token, int *i, char **str, t_envp *env)
{
	t_gn	*gn;
	int		k;

	if (expand_singl(token, i, str) == 1)
		return (0);
	k = *i;
	if (expand_doubl(token, i, str, env) == 1)
	{
		gn = malloc(sizeof(t_gn));
		gn->i = *i;
		gn->str = ft_strdup_1(*str);
		exand_do_quot(token, gn, env, k);
		*i = gn->i;
		return (*str = ft_strdup_1(gn->str), free(gn), 0);
	}
	return (1);
}
