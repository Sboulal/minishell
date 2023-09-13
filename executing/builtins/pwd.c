/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:42 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/13 17:29:41 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"

void	print_error_nor(char *str)
{
	printf("bash: export: '%s':", str);
	printf("not a valid identifier\n");
	g_var.status = 127;
}

void	print_error_norr(char *str, int i)
{
	printf("bash: syntax error near ");
	printf("unexpected token '%c'\n", str[i]);
	g_var.status = 127;
}
