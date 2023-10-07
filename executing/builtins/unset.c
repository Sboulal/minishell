/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:47 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/07 05:49:33 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	ft_delete(t_envp **list)
{
	t_envp	*head;
	t_envp	*tmp;

	head = (*list)->next;
	tmp = (*list)->next->next;
	(*list)->next = tmp;
	free(head->env);
	free(head->value);
	free(head->variable);
	free(head);
	g_var.sig_status = 0;
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
	free(head->exp);
	free(head->value);
	free(head->variable);
	free(head);
	g_var.sig_status = 0;
}

int	is_identifier(char c)
{
	if (!c)
		return (0);
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	unset_export_norm(t_export *head, t_exec **exp, int i)
{
	(*exp)->exp = (*exp)->exp->next;
	free(head->exp);
	free(head->value);
	free(head->variable);
	free(head);
	i++;
	return (i);
}

void	delete_export_norm(t_export *head, char *arg)
{
	if (head->next
		&& ft_strcmp(arg, head->next->variable) == 0)
		ft_delete_export(&head);
	else
		g_var.sig_status = 127;
}
