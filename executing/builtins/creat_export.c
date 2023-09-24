/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:43:07 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/24 07:50:08 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"

t_export	*put_int_export(t_export *new, char *env, int num)
{
	char	**str;
	char	*tmp;

	str = list_clean(env, num);
	new->variable = ft_strdup(str[0]);
	if (str[1])
		new->value = ft_strdup(str[1]);
	else 
		tmp = ft_substr(str[0], ft_strlen(str[0]) - 1, ft_strlen(str[0]));
	if (ft_strchr(env, '='))
	{
		new->exp = ft_strjoin(str[0], "=");
		new->exp = ft_strjoin2(new->exp, "\"");
		if (str[1])
			new->exp = ft_strjoin2(new->exp, new->value);
		new->exp = ft_strjoin2(new->exp, "\"");
	}
	else
		new->exp = ft_strdup(str[0]);
	new->next = NULL;
	return (tabfree(str), new);
}

t_export	*list_exp(char *env)
{
	t_export	*new;
	int			num;
	int			i;

	i = 0;
	if (!env)
		return (NULL);
	new = (t_export *)malloc(sizeof(t_export));
	if (!new)
		return (NULL);
	num = check_export(env);
	if (num)
	{
		new = put_int_export(new, env, num);
		return (new);
	}
	return (new);
}

t_export	*ft_lst_exp(t_export *exp)
{
	t_export	*lst;

	lst = exp;
	if (!lst)
		return (NULL);
	if (!(lst->next))
		return (lst);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	add_back_exp(t_export **lst, t_export *new)
{
	if (*lst == 0)
	{
		(*lst) = new;
		return ;
	}
	ft_lst_exp(*lst)->next = new;
}

void	creat_exp(t_export **exp, t_envp *env)
{
	if (!env)
	{
		g_var.status = 127;
		return ;
	}
	while (env)
	{
		add_back_exp(exp, list_exp(env->env));
		env = env->next;
	}
}
