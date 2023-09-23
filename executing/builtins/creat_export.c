/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:43:07 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/23 16:51:48 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"

t_export	*put_int_export(t_export *new, char *env, int num)
{
	char	**str;
	char 	*tmp1;
	char 	*tmp;
	char 	*tmp2;
	int 	i;

	str = list_clean(env, num);
	new->variable = ft_strdup(str[0]);
	
	if (str[1])
		new->value = ft_strdup(str[1]);
	else 
		tmp = ft_substr(str[0], ft_strlen(str[0]) - 1, ft_strlen(str[0]));
	if (ft_strchr(env, '='))
	{
		tmp1 = ft_strjoin(str[0], "=");
		tmp2 = ft_strjoin(tmp1, "\"");
		free(tmp1);
		if (tmp)
			tmp1 = ft_strjoin(tmp2, new->value);
		new->exp = ft_strjoin(tmp1, "\"");
	}
	else
		new->exp = ft_strdup(str[0]);
	new->next = NULL;
	i = 0;
	// free(tmp);
	// free(tmp1);
	// free(tmp2);
	while (str[i])
		free(str[i++]);
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
