/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:38:56 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/06 08:09:54 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

t_envp	*list_env(char *env)
{
	t_envp	*new;
	int		num;
	int		i;
	char	**str;

	if (!env)
		return (NULL);
	i = 0;
	new = (t_envp *) malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	if (!(ft_strchr(env, '=')))
	{
		free(new);
		return (NULL);
	}
	num = check_export(env);
	if (num)
	{
		str = list_clean(env, num);
		new->variable = ft_strdup(str[0]);
		new->value = ft_strdup(str[1]);
		new->env = ft_strjoin(str[0], "=");
		new->env = ft_strjoin2(new->env, str[1]);
		new->next = NULL;
		tabfree(str);
		return (new);
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
	if (!lst || !new) // zid F AKHRA
		return ;
	if (*lst == 0)
	{
		(*lst) = new;
		return ;
	}
	ft_lst(*lst)->next = new;
}

void	creat_env(t_exec **lst)
{
	int	i;

	i = 0;
	if (!(*lst)->env_string[i])
	{
		g_var.status = 127;
		return ;
	}
	while ((*lst)->env_string[i])
	{
		add_back_env(&(*lst)->env, list_env((*lst)->env_string[i]));
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
}
