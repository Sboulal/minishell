/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:57:55 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/06 22:59:29 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	edit_add(t_exec **exec, int i, int num)
{
	t_export	*head;
	char		**str;

	head = (*exec)->exp;
	if (!head)
	{
		edit_add_more(exec, i);
		return ;
	}
	str = list_clean((*exec)->cmd->arg[i], num);
	while (head->next && (ft_strcmp(head->variable, str[0]) != 0))
		head = head->next;
	if (!head->next && (ft_strcmp(head->variable, str[0]) != 0))
		edit_add_more(exec, i);
	else
	{
		if (ft_strchr((*exec)->cmd->arg[i], '='))
			edit_in_g_variable(exec, str, head, num);
	}
	tabfree(str);
}

void	add_to_export(t_exec **exec)
{
	int	i;
	int	num;

	i = 0;
	while ((*exec)->cmd->arg[i])
	{
		num = check_export((*exec)->cmd->arg[i]);
		if (num)
			edit_add(exec, i, num);
		i++;
	}
}

void	add_back_envstring(t_envp *env, t_exec **exp)
{
	t_envp	*head;
	int		i;

	if (!env)
	{
		tabfree((*exp)->env_string);
		(*exp)->env_string = NULL;
		return ;
	}
	i = cpt_env(env);
	tabfree((*exp)->env_string);
	(*exp)->env_string = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(*exp)->env_string)
		return ;
	i = 0;
	head = env;
	while (head)
	{
		if (head->env)
			(*exp)->env_string[i++] = ft_strdup(head->env);
		head = head->next;
	}
	(*exp)->env_string[i] = NULL;
}

void	edit_add_more(t_exec **exec, int i)
{
	t_export	*exp;
	t_envp		*env;

	exp = list_exp((*exec)->cmd->arg[i]);
	env = list_env((*exec)->cmd->arg[i]);
	add_back_exp(&(*exec)->exp, exp);
	add_back_env(&(*exec)->env, env);
	add_back_envstring((*exec)->env, exec);
}
