/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:16 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/06 22:32:39 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

char	*get_env(t_envp *list_env)
{
	while (list_env && ft_strncmp(list_env->variable, "HOME", 5))
		list_env = list_env->next;
	if (!list_env)
		return (NULL);
	return (list_env->value);
}

void	sort_utile(t_export *head, t_export *tomp)
{
	char	*tmp;
	char	*tmp1;
	char	*tmp2;

	tmp1 = head->exp;
	tmp = head->value;
	tmp2 = head->variable;
	head->exp = tomp->exp;
	head->value = tomp->value;
	head->variable = tomp->variable;
	tomp->exp = tmp1;
	tomp->value = tmp;
	tomp->variable = tmp2;
}

void	builtins(t_exec **exp, t_mini *cmd)
{
	if ((ft_strcmp(cmd->cmd, "env") == 0) && cmd->nbr_arg == 0)
		print_env(*exp);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(cmd->arg[0], 2);
		ft_putstr_fd("' No such file or directory\n", 2);
		g_var.status = 127;
	}
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		exit_program(cmd, *exp);
	else if ((ft_strcmp(cmd->cmd, "echo") == 0))
		print_in_echo(cmd->arg, cmd->nbr_arg);
	else if ((ft_strcmp(cmd->cmd, "pwd") == 0))
		get_pwd(exp);
	else if ((ft_strcmp(cmd->cmd, "unset") == 0 && cmd->nbr_arg != 0))
		unset_env((exp), cmd->arg);
	else if ((ft_strcmp(cmd->cmd, "cd") == 0))
		cd_derc(cmd->arg, &(*exp)->env, exp, cmd);
	else if ((ft_strcmp(cmd->cmd, "export") == 0))
		export(exp);
}

int	protect_exit(t_mini *cmd, t_exec *exp)
{
	if (cmd->nbr_arg == 0)
	{
		if (exp->nbr_cmd == 1)
			printf("exit\n");
		exit(g_var.status);
	}
	return (0);
}
