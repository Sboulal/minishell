/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:56:54 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/14 13:38:39 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/exec.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	sig(void)
{
	rl_catch_signals = 0;
	if ((signal(SIGINT, handle_signal) == SIG_ERR))
	{
		g_var.status = 1;
		perror("signal");
		return (1);
	}
	if ((signal(SIGQUIT, SIG_IGN) == SIG_ERR))
	{
		g_var.status = 1;
		perror("signal");
		return (1);
	}
	return (0);
}

void	sig_add(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("Quit\n");
		return ;
	}
	if (sig == SIGINT)
	{
		rl_catch_signals = 0;
		printf("\n");
		return ;
	}
}

int	sig_cmd(void)
{
	if ((signal(SIGQUIT, sig_add) == SIG_ERR))
	{
		perror("signal");
		g_var.status = 1;
		return (1);
	}
	if ((signal(SIGINT, sig_add) == SIG_ERR))
	{
		perror("signal");
		g_var.status = 1;
		return (1);
	}
	return (0);
}
