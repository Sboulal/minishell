/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:19:50 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 00:05:32 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	free_unset(t_exec **exp, t_envp *head)
{
	(*exp)->env = (*exp)->env->next;
	free(head->env);
	free(head->value);
	free(head->variable);
	free(head);
}

void	unset_env_norm(t_exec **exp, int i, int num, t_envp *head)
{
	char	**arg;

	arg = (*exp)->cmd->arg;
	while (arg[i])
	{
		num = check_unset_env((*exp)->cmd->arg[i]);
		if (num)
		{
			head = (*exp)->env;
			if (head && ft_strcmp(arg[i], head->variable) == 0)
			{
				free_unset(exp, head);
				i++;
				continue ;
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
	int		num;
	t_envp	*head;

	i = 0;
	if (!(*exp) || !(*exp)->exp)
		return ;
	unset_export(exp, arg);
	if (!(*exp)->env)
		return ;
	num = 0;
	head = NULL;
	unset_env_norm(exp, i, num, head);
	add_back_envstring((*exp)->env, exp);
	g_var.status = 0;
	if ((*exp)->nbr_cmd > 1)
		exit(g_var.status);
}

void	unset_export(t_exec **exp, char **arg)
{
	t_export	*head;
	int			i;
	int			num;

	i = 0;
	if (!exp || !(*arg))
		return ;
	while (arg[i])
	{
		num = check_unset((*exp)->cmd->arg[i]);
		if (num)
		{
			head = (*exp)->exp;
			if (head && ft_strcmp(arg[i], head->variable) == 0)
			{
				i = unset_export_norm(head, exp, i);
				continue ;
			}
			while (head->next && ft_strcmp(arg[i], head->next->variable))
				head = head->next;
			delete_export_norm(head, arg[i]);
		}
		i++;
	}
}

void	exit_program_norm(t_mini *cmd)
{
	printf("exit\n");
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->arg[0], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_var.status = 255;
	exit(g_var.status);
}
