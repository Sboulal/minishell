/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:38:56 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/14 13:38:02 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"

t_envp	*list_env(char *env)
{
	t_envp	*new;
	int		num;
	char	**str;

	if (!env)
		return (NULL);
	new = (t_envp *) malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	if (!(ft_strchr(env, '=')))
		return (NULL);
	num = check_export(env);
	if (num)
	{
		str = list_clean(env, num);
		new->variable = str[0];
		new->value = str[1];
		new->env = ft_strjoin(str[0], "=");
		new->env = ft_strjoin(new->env, str[1]);
		// new->index = 0;
		new->next = NULL;
		return (free(str), new);
	}
	return (new);
}

t_envp	*ft_lst(t_envp *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	add_back_env(t_envp **lst, t_envp *new)
{
	if (!lst || !new)
		return ;
	if (*lst == 0)
	{
		(*lst) = new;
		return ;
	}
	ft_lst(*lst)->next = new;
}

void	creat_env(t_envp **lst)
{
	int	i;

	i = 0;
	if (!g_var.env[i])
	{
		g_var.status = 127;
		return ;
	}
	while (g_var.env[i])
	{
		add_back_env(lst, list_env(g_var.env[i]));
		i++;
	}
}

void	print_env(t_exec *exp)
{
	int	i;

	i = 0;
	if (!exp->env)
	{
		g_var.status = 127;
		return ;
	}
	while (exp->env)
	{
		printf("%s\n", exp->env->env);
		i++;
		exp->env = exp->env->next;
	}
	g_var.status = 0;
	exit(0);
}
