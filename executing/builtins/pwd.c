/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:42 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/07 05:49:33 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	print_error_nor(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_var.sig_status = 127;
}

void	print_error_norr(char *str, int i)
{
	(void)i;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_var.sig_status = 127;
}

void	get_pwd(t_exec **exp)
{
	char	s[PATH_MAX];

	getcwd(s, PATH_MAX);
	if (*s)
		printf("%s\n", s);
	g_var.sig_status = 0;
	if ((*exp)->nbr_cmd > 1)
		exit(g_var.sig_status);
}
