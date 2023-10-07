/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:38:56 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/07 05:49:33 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	protect_list_env(t_envp *new, char *env)
{
	if (!new)
		return (1);
	if (!(ft_strchr(env, '=')))
	{
		free(new);
		return (1);
	}
	return (0);
}

t_envp	*list_env(char *env)
{
	t_envp	*new;
	int		num;
	char	**str;

	if (!env)
		return (NULL);
	new = (t_envp *) malloc(sizeof(t_envp));
	if (protect_list_env(new, env))
		return (NULL);
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
	if (!lst || !new) 
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
		g_var.sig_status = 127;
		return ;
	}
	while ((*lst)->env_string[i])
	{
		add_back_env(&(*lst)->env, list_env((*lst)->env_string[i]));
		i++;
	}
}
