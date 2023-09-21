/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:07 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/21 17:55:16 by nkhoudro         ###   ########.fr       */
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
	exit(0);
}

