/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:15:22 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/07 06:16:01 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_expand(char **limiter)
{
	if (contains(*limiter, '"') || contains(*limiter, '\''))
	{
		*limiter = quotes_removal(*limiter);
		return (0);
	}
	*limiter = ft_strdup(*limiter);
	return (1);
}

void	change_flag(int s)
{
	(void)s;
	g_var.sig_heredoc = dup(0);
	close(0);
}

int	handle_heredoc_suite(t_mini *cmd, char *limiter, char *file, int fd)
{
	close(fd);
	(void)limiter;
	fd = open(file, O_RDONLY, 0);
	if (fd == -1)
		return (0);
	cmd->fd[0] = fd;
	free(file);
	return (1);
}

void	check_heredoc(void)
{
	if (g_var.sig_heredoc)
	{
		ft_dup2(g_var.sig_heredoc, 0);
		ft_close(g_var.sig_heredoc);
		g_var.sig_status = 1;
	}
}

void	ft_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		ft_putstr_fd("error", 2);
}
