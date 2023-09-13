/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:47 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/13 17:29:41 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"

void	ft_delete(t_envp **list)
{
	t_envp	*head;
	t_envp	*tmp;

	head = (*list)->next;
	tmp = (*list)->next->next;
	(*list)->next = tmp;
	free(head);
	g_var.status = 0;
}

void	ft_delete_export(t_export **list)
{
	t_export	*head;
	t_export	*tmp;

	if (!list)
		return ;
	head = (*list)->next;
	tmp = (*list)->next->next;
	(*list)->next = tmp;
	free(head);
	g_var.status = 0;
}

void	unset_export(t_exec *exp, char **arg)
{
	t_export	*head;
	int			i;

	i = 0;
	if (!exp)
		return ;
	while (arg[i])
	{
		head = exp->exp;
		while (ft_strncmp(arg[i], head->next->variable, ft_strlen(arg[i])))
			head = head->next;
		if (head->next
			&& ft_strncmp(arg[i], head->next->variable, ft_strlen(arg[i])) == 0)
			ft_delete_export(&head);
		else
			g_var.status = 127;
		i++;
	}
}

void	unset_env(t_exec *exp, char **arg)
{
	int		i;
	int		k;
	t_envp	*head;

	i = 0;
	if (!exp)
		return ;
	unset_export(exp, arg);
	while (arg[i])
	{
		if (ft_strchr(arg[i], '='))
		{
			head = exp->env;
			k = ft_strlen(arg[i]);
			while (ft_strncmp(arg[i], head->next->variable, k))
				head = head->next;
			if (head->next && ft_strncmp(arg[i], head->next->variable, k))
				ft_delete(&head);
			else
				g_var.status = 127;
		}
		i++;
	}
	g_var.status = 0;
	exit(0);
}
