/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:43:07 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/14 14:42:29 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"

t_export	*put_int_export(t_export *new, char *env, int num)
{
	char	**str;

	str = list_clean(env, num);
	new->variable = str[0];
	new->value = str[1];
	if (ft_strchr(env, '='))
	{
		new->exp = ft_strjoin(str[0], "=");
		new->exp = ft_strjoin(new->exp, "\"");
		new->exp = ft_strjoin(new->exp, new->value);
		new->exp = ft_strjoin(new->exp, "\"");
	}
	else
		new->exp = str[0];
	new->next = NULL;
	return (free(str), new);
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
