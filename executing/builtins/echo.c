/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:07 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/22 23:21:44 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"

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

// int	check_arg(char **args, int k, int nbr, int len)
// {
// 	int	i;

// 	i = 0;
// 	if (!(*args))
// 		return (0);
// 	while (args[k][i])
// 	{
// 		if (!check_echo_arg(k, i, args))
// 			len++;
// 		if (check_echo_arg(k, i, args))
// 		{
// 			i = 0;
// 			while (args[k][i])
// 			{
// 				if (args[k][i] != '\'' && args[k][i] != '\"')
// 					printf("%c", args[k][i++]);
// 			}
// 			len = print_in_echo(args, k, nbr, len);
// 			return (print_in_echo(args, k, nbr, len));
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// void	print_echo(char **arg, int nbr, t_exec *exp)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = 1;

// 	if (!(*arg) || !arg)
// 		return ;
// 	while (arg[i])
// 	{
// 		len = check_arg(arg, i, nbr, len);
// 		if (len)
// 		{
// 			if (len == 1)
// 				printf("\n");
// 			if (exp->nbr_cmd > 1)
// 				exit(0);
// 			return ;
// 		}
// 		else
// 			i++;
// 	}
// 	g_var.status = 0;
// 	exit (0);
// }
// int	check_arg(char **arg)
// {
// 	int j;

// 	j = 0;
// 	k = 0;
// 	while (arg[i][j])
// 	{
// 		if ((arg[i][j] == 'n' && arg[i][0] == '-') || (arg[i][j] == 'n' && arg[i - 1][j] == 'n') )
// 			k++;
// 		j++;
// 	}
// }
int	check_firs_arg(char **arg, int i)
{
	int j;
	int k;

	j = 1;
	k = 0;
	if (!(*arg))
		return (k);
	while (arg[i] && arg[i][j])
	{
		if ((arg[i][j] == 'n' && arg[i][0] == '-')
		|| (arg[i][0] == '-' && arg[i][j] == 'n'
		&& (arg[i][j + 1] == 'n'
		|| arg[i][j + 1] == '\0'
		|| (arg[i][j] == 'n' && arg[i][j] == ' '))))
			k++;
		else
			return (k);
		j++;
	}
	return (k);
}
void	print_in_echo(char **arg, int n)
{
	int i;
	int len; 
	int lent;

	i = 0;
	int d;
	if (n == 0)
	{
		printf("\n");
		return ;
	}
	len = check_firs_arg(arg, 0);
	lent = ft_strlen(arg[0]);
	lent = lent - 1;
	if (len < lent || len > lent || len == 0)
	{
		while (arg[i])
		{
			if (i != 0 || !arg[i])
				printf(" ");
			printf("%s",arg[i]);
			i++;
		}
		printf("\n");
	}
	else
	{
		i = 1;
		while (arg[i])
		{
			len = check_firs_arg(arg, i);
			lent = ft_strlen(arg[i]);
			lent = lent - 1;
			if (len == lent)
				i++;
			else
				break;
		}
		d = i;
		while (arg[i])
		{
			if (i != d)
				printf(" ");
			printf("%s",arg[i]);
			i++;
		}
	}
	//g_var.status = 0;
	exit(g_var.status);
}

