/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:56:54 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/28 20:58:31 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_var.status = 1;
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
		printf("Quit: %d\n", SIGQUIT);
		g_var.status = 131;
		return ;
	}
	if (sig == SIGINT)
	{
		rl_catch_signals = 0;
		printf("\n");
		g_var.status = 130;
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
