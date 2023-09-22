/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:42 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/22 02:24:23 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"

void	print_error_nor(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_var.status = 127;
}

void	print_error_norr(char *str, int i)
{
	(void)i;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_var.status = 127;
}
