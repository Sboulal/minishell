/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:27 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/06 22:58:50 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	edit_in_g_variable_norm(t_export *head, char **str)
{
	free(head->exp);
	head->exp = ft_strjoin(str[0], "=");
	head->exp = ft_strjoin2(head->exp, "\"");
	head->exp = ft_strjoin2(head->exp, head->value);
	head->exp = ft_strjoin2(head->exp, "\"");
}

void	edit_in_g_variable_norm_env(t_export *head, t_exec **exec, t_envp *env)
{
	free(env->variable);
	free(env->value);
	free(env->env);
	env->variable = ft_strdup(head->variable);
	env->value = ft_strdup(head->value);
	env->env = ft_strjoin(env->variable, "=");
	env->env = ft_strjoin2(env->env, env->value);
	edit_in_string(exec, env);
}

void	edit_in_g_variable(t_exec **exec, char **str, t_export *head, int num)
{
	t_envp	*env;

	if (!(*exec))
		return ;
	env = (*exec)->env;
	free(head->variable);
	head->variable = ft_strdup(str[0]);
	if (num == 2)
		head->value = ft_strjoin2(head->value, str[1]);
	else
	{
		free(head->value);
		head->value = ft_strdup(str[1]);
	}
	edit_in_g_variable_norm(head, str);
	while (env->next && ft_strcmp(env->variable, str[0]) != 0)
		env = env->next;
	if (env)
		edit_in_g_variable_norm_env(head, exec, env);
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
			else if (str[i] == '+')
			{
				print_error_norr(str, i);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	cpt_env(t_envp *head)
{
	int	i;

	i = 0;
	if (!head)
		return (i);
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}
