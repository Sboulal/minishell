/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:22 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/14 13:37:35 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"

void	exit_program(t_mini *cmd)
{
	int	i;

	i = 0;
	if (cmd->nbr_arg != 1 && cmd->nbr_arg != 0)
	{
		printf("bash: exit: too many arguments\n");
		g_var.status = 1;
		return ;
	}
	g_var.status = ft_atoi(cmd->arg[0]);
	while (cmd->arg[0][i])
	{
		if (ft_isalpha(cmd->arg[0][i]))
			i++;
		else
		{
			printf("bash: exit: %s: numeric argument required\n", cmd->arg[0]);
			return ;
		}
	}
	printf("exit\n");
	exit(0);
}
