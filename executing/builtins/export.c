/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:27 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/05 22:00:43 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	edit_in_g_variable(t_exec **exec, char **str, t_export *head, int num)
{
	t_envp	*env;

	if (!(*exec))
		return ;
	env = (*exec)->env;
	head->variable = ft_strdup(str[0]);
	if (num == 2)
		head->value = ft_strjoin2(head->value, str[1]);
	else
		head->value = str[1];
	free(head->exp);
	head->exp = ft_strjoin(str[0], "=");
	head->exp = ft_strjoin2(head->exp, "\"");
	head->exp = ft_strjoin2(head->exp, head->value);
	head->exp = ft_strjoin2(head->exp, "\"");
	while (env->next && ft_strcmp(env->variable, str[0]) != 0)
		env = env->next;
	tabfree(str);
	if (env)
	{
		free(env->variable);
		free(env->value);
		free(env->env); 
		env->variable = head->variable;
		env->value = head->value;
		env->env = head->exp;
		edit_in_string(exec, env);
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
void	add_back_envstring(t_envp *env, t_exec **exp)
{
	t_envp	*head;
	char	**s;
	int		i;

	if (!env)
	{
		tabfree((*exp)->env_string);
		(*exp)->env_string = NULL;
		return;
	}
	i = cpt_env(env);
	s = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	head = env;
	while (head)
	{
		if (head->env)
			s[i++] = ft_strdup(head->env);
		head = head->next;
	}
	s[i] = NULL;
	tabfree((*exp)->env_string);
	(*exp)->env_string = s;
}
void edit_add_more(t_exec **exec, int i)
{
	add_back_exp(&(*exec)->exp, list_exp((*exec)->cmd->arg[i]));
	add_back_env(&(*exec)->env, list_env((*exec)->cmd->arg[i]));
	add_back_envstring((*exec)->env, exec);
}
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
	free(str[0]);
	free(str[1]);
	free(str);
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
