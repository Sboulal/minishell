/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:07 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/14 15:45:04 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"

void	print_tab(char **arg, int i, int nbr)
{
	int	j;

	j = 0;
	while (arg[i])
	{
		j = 0;
		while (arg[i][j])
		{
			if (arg[i][j] != '\'' && arg[i][j] != '\"')
				printf("%c", arg[i][j]);
			j++;
		}
		i++;
		if (i < nbr)
			printf(" ");
	}
}

int	print_in_echo(char **args, int k, int nbr, int len)
{
	if (k < nbr && args[k + 1])
		printf(" ");
	k++;
	if (!args[k])
		return (len);
	print_tab(args, k, nbr);
	return (len);
}

int	check_echo_arg(int k, int i, char **args)
{
	if ((args[k][i] != 'n' || args[k][i + 1] != '\0')
	&& (args[k][i] != '-' || args[k][i + 1] != 'n'
	|| (args[k][i + 2] != 'n' && args[k][i + 2] != '\0' ))
	&& ((args[k][i + 1] != 'n'
	|| (args[k][i + 2] != 'n' && args[k][i + 2] != '\0' ))))
		return (1);
	return (0);
}

int	check_arg(char **args, int k, int nbr, int len)
{
	int	i;

	i = 0;
	if (!(*args))
		return (0);
	while (args[k][i])
	{
		if (!check_echo_arg(k, i, args))
			len++;
		if (check_echo_arg(k, i, args))
		{
			i = 0;
			while (args[k][i])
			{
				if (args[k][i] != '\'' && args[k][i] != '\"')
					printf("%c", args[k][i++]);
			}
			len = print_in_echo(args, k, nbr, len);
			return (print_in_echo(args, k, nbr, len));
		}
		i++;
	}
	return (0);
}

void	print_echo(char **arg, int nbr, t_exec *exp)
{
	int	i;
	int	len;

	i = 0;
	len = 1;

	if (!(*arg) || !arg)
		return ;
	while (arg[i])
	{
		len = check_arg(arg, i, nbr, len);
		if (len)
		{
			if (len == 1)
				printf("\n");
			if (exp->nbr_cmd > 1)
				exit(0);
			return ;
		}
		else
			i++;
	}
	g_var.status = 0;
	exit (0);
}
