/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:22 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/07 05:49:33 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static long long	ft_at(const char *str, int sgn)
{
	long long	i;
	long long	res;
	long long	rv;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		rv = res;
		res = (res * 10) + (str[i] - '0');
		if (res / 10 != rv)
		{
			if (sgn == -1)
				return (1);
			return (-1);
		}
		i++;
	}
	return (res);
}

long long	ft_atoi_exit(const char *str)
{
	long long	i;
	long long	sgn;
	long long	res;

	i = 0;
	sgn = 1;
	res = 0;
	while ((str[i] > 8 && str[i] < 14) || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sgn *= (-1);
		i++;
	}
	res = ft_at(str + i, sgn);
	return (res * sgn);
}

void	exit_caract(t_mini *cmd)
{
	printf("exit\n");
	g_var.sig_status = 255;
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->arg[0], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(g_var.sig_status);
}

void	exit_norm(t_mini *cmd)
{
	int	i;

	i = 0;
	while (cmd->arg && cmd->arg[0] && cmd->arg[0][i])
	{
		if ((!ft_isdigit(cmd->arg[0][i])
			&& ((cmd->arg[0][i] == '+'
				&& !ft_isdigit(cmd->arg[0][i + 1])) 
		|| (cmd->arg[0][i] == '-' 
				&& !ft_isdigit(cmd->arg[0][i + 1]))))
		|| (!ft_isdigit(cmd->arg[0][i]) 
				&& cmd->arg[0][i] != '+' && cmd->arg[0][i] != '-'))
			exit_caract(cmd);
		i++;
	}
	if (cmd->nbr_arg > 1)
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_var.sig_status = 1;
		exit(g_var.sig_status);
	}
}

void	exit_program(t_mini *cmd, t_exec *exp)
{
	long long	catch;

	if (cmd->nbr_arg == 0 && exp->nbr_cmd == 1)
	{
		printf("exit\n");
		exit(g_var.sig_status);
	}
	exit_norm(cmd);
	catch = ft_atoi_exit(cmd->arg[0]);
	if (catch == -1 && ft_strcmp(ft_itoa(catch), cmd->arg[0]))
		exit_program_norm(cmd);
	g_var.sig_status = (int)catch;
	if (protect_exit(cmd, exp))
		return ;
	if (exp->nbr_cmd == 1)
	{
		printf("exit\n");
		exit(g_var.sig_status);
	}
}
