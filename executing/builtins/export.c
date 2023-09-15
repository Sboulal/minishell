/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:27 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/15 02:45:55 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"

void	edit_in_g_variable(t_exec *exec, char **str, t_export *head, int num)
{
	t_envp	*env;

	env = exec->env;
	head->variable = str[0];
	if (num == 2)
		head->value = ft_strjoin(head->value, str[1]);
	else
		head->value = str[1];
	head->exp = ft_strjoin(str[0], "=");
	head->exp = ft_strjoin(head->exp, "\"");
	head->exp = ft_strjoin(head->exp, head->value);
	head->exp = ft_strjoin(head->exp, "\"");
	while (env->next && ft_strcmp(env->variable, str[0]) != 0)
		env = env->next;
	if (env)
	{
		env->variable = head->variable;
		env->value = head->value;
		env->env = head->exp;
		edit_in_string(env);
	}
}

int	check_argument_export(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if ((!ft_isalpha(str[i])) && (!ft_isdigit(str[i]))
			&& str[i] != '_' && str[i] != '=')
		{
			if (str[i] == '+' && str[i + 1] != '=')
			{
				print_error_nor(str);
				return (1);
			}
			if (str[i] != '+')
			{
				print_error_norr(str, i);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	add_back_envstring(t_envp *env)
{
	t_envp	*head;
	int		i;

	head = env;
	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	g_var.env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	head = env;
	while (head)
	{
		if (head->env)
			g_var.env[i++] = ft_strdup(head->env);
		head = head->next;
	}
	g_var.env[i] = NULL;
}

void	edit_add(t_exec *exec, int i, int num)
{
	t_export	*head;
	char		**str;

	head = exec->exp;
	if (check_argument_export(exec->cmd->arg[i]))
		return ;
	str = list_clean(exec->cmd->arg[i], num);
	while (head->next && (ft_strcmp(head->variable, str[0]) != 0))
		head = head->next;
	if (!head->next && (ft_strcmp(head->variable, str[0]) != 0))
	{
		add_back_exp(&exec->exp, list_exp(exec->cmd->arg[i]));
		add_back_env(&exec->env, list_env(exec->cmd->arg[i]));
		add_back_envstring(exec->env);
		// printf("ha ana\n");
	}
	else
	{
		if (ft_strchr(exec->cmd->arg[i], '='))
			edit_in_g_variable(exec, str, head, num);
	}
}

void	add_to_export(t_exec *exec)
{
	int	i;
	int	num;

	i = 0;
	while (exec->cmd->arg[i])
	{
		num = check_export(exec->cmd->arg[i]);
		if (num)
		{
			edit_add(exec, i, num);
		}
		i++;
	}
}
