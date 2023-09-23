/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:38:56 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/23 14:50:06 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"

t_envp	*list_env(char *env)
{
	t_envp	*new;
	int		num;
	char 	*tmp1;
	char 	*tmp;
	char 	*tmp2;
	int i;
	char	**str;

	i = 0;
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
		tmp1 = str[0];
		tmp2 = str[1];
		new->variable = ft_strdup(tmp1);
		new->value = ft_strdup(tmp2);
		tmp = ft_strjoin(tmp1, "=");
		new->env = ft_strjoin(tmp, tmp2);
		free(tmp1);
		free(tmp2);
		free(tmp);
		free(str);
		new->next = NULL;
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
	if (!lst || !new)
		return ;
	if (*lst == 0)
	{
		(*lst) = new;
		return ;
	}
	ft_lst(*lst)->next = new;
}

void	creat_env(t_envp **lst, char **env)
{
	int	i;
	t_envp	*tmp;

	i = 0;
	if (!env[i])
	{
		g_var.status = 127;
		return ;
	}
	while (env[i])
	{
		tmp = list_env(env[i]);
		add_back_env(lst, tmp);
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
	exit(g_var.status);
}
