/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:47 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/28 21:00:00 by saboulal         ###   ########.fr       */
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
	free(head->exp);
	free(head->value);
	free(head->variable);
	free(head);
	g_var.status = 0;
}
int is_identifier(char c)
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
void	delete_export_norm(t_export *head,char *arg)
{
	if (head->next
		&& ft_strcmp(arg, head->next->variable) == 0)
		ft_delete_export(&head);
	else
		g_var.status = 127;
}
void	unset_export(t_exec **exp, char **arg)
{
	t_export	*head;
	int			i;
	int num;

	i = 0;
	if (!exp || !(*arg))
		return ;
	while (arg[i])
	{
		num = check_unset((*exp)->cmd->arg[i]);
		if (num)
		{
			head = (*exp)->exp;
			if (head &&  ft_strcmp(arg[i], head->variable) == 0)
			{
				i = unset_export_norm(head, exp, i);
				continue;
			}
			while (head->next && ft_strcmp(arg[i], head->next->variable))
				head = head->next;
			delete_export_norm(head, arg[i]);
		}
		i++;
	}
}
void free_unset(t_exec **exp, t_envp *head)
{
	(*exp)->env = (*exp)->env->next;
	free(head->env);
	free(head->value);
	free(head->variable);
	free(head);
}
void	unset_env_norm(char **arg, t_exec **exp, int i, int num, t_envp *head)
{
	while (arg[i])
	{
		num = check_unset_env((*exp)->cmd->arg[i]);
		if (num)
		{
			head = (*exp)->env;
			if (head &&  ft_strcmp(arg[i], head->variable) == 0)
			{
				free_unset(exp, head);
				i++;
				continue;
			}
			while (head->next && ft_strcmp(arg[i], head->next->variable))
				head = head->next;
			if (head->next
				&& ft_strcmp(arg[i], head->next->variable) == 0)
					ft_delete(&head);
			else
				g_var.status = 127;
		}
		i++;
	}
}
void	unset_env(t_exec **exp, char **arg)
{
	int		i;
	int num;
	t_envp	*head;

	i = 0;
	if (!(*exp) || !(*exp)->exp)
		return ;
	unset_export(exp, arg);
	if (!(*exp)->env)
		return ;
	num = 0;
	head = NULL;
	unset_env_norm(arg, exp, i, num, head);
	add_back_envstring((*exp)->env, exp);
	g_var.status = 0;
	if ((*exp)->nbr_cmd > 1)
		exit(g_var.status);
}

