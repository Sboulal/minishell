/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:22 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/28 20:58:31 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static int	ft_at(const char *str)
{
	long	i;
	long	res;
	long	rv;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		rv = res;
		res = (res * 10) + (str[i] - '0');
		if (res / 10 != rv)
			return (-1);
		i++;
	}
	if (str[i])
	{
		g_var.status = 255;
		exit(g_var.status);
	}
	if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
		return (255);
	return (res);
}

int	ft_me_atoi(const char *str)
{
	int	i;
	int	sgn;
	int	res;

	i = 0;
	sgn = 1;
	res = 0;
	if (!str)
		return (0);
	while ((str[i] > 8 && str[i] < 14) || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			g_var.status = 247;
			// exit(g_var.status);
		}
		i++;
	}
	res = ft_at(str + i);
	return (res * sgn);
}
void	exit_program(t_mini *cmd, t_exec *exp)
{
	int	i;

	i = 0;
	if (cmd->nbr_arg > 1)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_var.status = 1;
		return ;
	}
	if (cmd->nbr_arg == 0)
	{
		if (exp->nbr_cmd == 1)
			ft_putstr_fd("exit\n", 2);
		exit(g_var.status);
	}
	if (cmd->nbr_arg == 1)
	{
		g_var.status = ft_me_atoi(cmd->arg[0]);
		if (g_var.status < 0)
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->arg[0], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			g_var.status = 255;
		}
		if (g_var.status > INT_MAX || g_var.status < INT_MIN)
		{
			ft_putstr_fd("exit\n", 2);
			g_var.status = 255;
			exit(g_var.status);
		}
		else
		{
			while (cmd->arg[0][i])
			{
				if (ft_isdigit(cmd->arg[0][i]))
					i++;
				else
				{
					ft_putstr_fd("exit\n", 2);
					g_var.status = 255;
					ft_putstr_fd("minishell: exit: ", 2);
					ft_putstr_fd(cmd->arg[0], 2);
					ft_putstr_fd(": numeric argument required\n", 2);
					exit(g_var.status);
				}
			}
		}
	}
	g_var.status = ft_atoi(cmd->arg[0]);
	if (exp->nbr_cmd == 1)
		exit(g_var.status);
}