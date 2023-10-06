/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:10:32 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/06 22:50:55 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	edit_in_string(t_exec **exp, t_envp *env)
{
	int	i;

	i = 0;
	while ((*exp)->env_string[i] 
		&& ft_strncmp((*exp)->env_string[i], "SHLVL=", 6) != 0)
		i++;
	if ((*exp)->env_string[i])
	{
		free((*exp)->env_string[i]);
		(*exp)->env_string[i] = ft_strdup(env->env);
	}
}

void	export(t_exec **exec)
{
	t_export	*head;

	if (!(*exec))
	{
		g_var.status = 1;
		return ;
	}
	head = (*exec)->exp;
	if ((*exec)->exp)
		sort_list(&(*exec)->exp);
	if ((*exec)->cmd->nbr_arg == 0)
	{
		while (head)
		{
			printf("declare -x %s\n", head->exp);
			head = head->next;
		}
		g_var.status = 0;
	}
	else
		add_to_export(exec);
	if ((*exec)->nbr_cmd > 1)
		exit(g_var.status);
}

int	check_error_export_norr(char *cmd, int i)
{
	if (cmd[i] == '-')
	{
		ft_putstr_fd("export: usage: export [-nf] [na", 2);
		ft_putstr_fd("me[=value] ...] or export -p \n", 2);
		g_var.status = 1;
		return (0);
	}
	else if (cmd[i] == ')' || cmd[i] == '(')
	{
		ft_putstr_fd("minishell: syntax error near ", 2);
		ft_putstr_fd("unexpected token `", 2);
		ft_putchar_fd(cmd[i], 2);
		ft_putstr_fd("'\n", 2);
		g_var.status = 1;
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_var.status = 1;
		return (0);
	}
}
