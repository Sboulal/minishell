/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:31:09 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/14 18:40:35 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lexer.h"

void	handle_parent_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_var.status = 1;
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
}

void	handle_signals(void)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_handler = &handle_parent_sigint;
	sa_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_sigint, NULL);
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}

void	default_signals(void)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_handler = SIG_DFL;
	sa_sigquit.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa_sigint, NULL);
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}

void	ignore_signals(void)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_handler = SIG_IGN;
	sa_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_sigint, NULL);
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}

void	sigint_heredoc(void)
{
	struct sigaction	sa_sigint;

	sa_sigint.sa_handler = &change_flag;
	sigaction(SIGINT, &sa_sigint, NULL);
}