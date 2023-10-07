/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:57:08 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 09:49:37 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	test_file(char *file)
{
	if (file[0] == '$')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		return (1);
	}
	return (0);
}

int	redirect_right(char *file, t_mini **cmd, char *type)
{
	int	fd;

	if (!ft_strcmp(type, ">>"))
	{
		fd = ft_open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
		{
			if ((*cmd)->fd[1] != 1 && (*cmd)->fd[1] != -4)
				close((*cmd)->fd[1]);
			(*cmd)->x = 1;
			(*cmd)->fd[1] = -4;
			ft_putstr_fd(file, 2);
			perror(" ");
			g_var.sig_status = 1;
			return (0);
		}
		check_and_redirect(&(*cmd)->fd[1], fd);
	}
	return (1);
}

int	redirect_in(char *file, t_mini **cmd, char *type)
{
	int	fd;

	if (!ft_strcmp(type, ">"))
	{
		fd = ft_open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			if ((*cmd)->fd[1] != 1 && (*cmd)->fd[1] != -4)
				close((*cmd)->fd[1]);
			(*cmd)->x = 1;
			(*cmd)->fd[1] = -4;
			ft_putstr_fd(file, 2);
			perror(" ");
			g_var.sig_status = 1;
			return (0);
		}
		check_and_redirect(&(*cmd)->fd[1], fd);
	}
	return (1);
}

int	redirect(t_mini *cmd, char *type, char *file, t_envp *env)
{
	int	fd;

	(void)env;
	cmd->x = 0;
	if (!redirect_right(file, &cmd, type))
		return (0);
	if (!redirect_in(file, &cmd, type))
		return (0);
	if (!ft_strcmp(type, "<"))
	{
		fd = ft_open(file, O_RDONLY, 0644);
		if (fd == -1)
		{
			if (cmd->fd[0] != 0 && cmd->fd[0] != -4)
				close(cmd->fd[0]);
			cmd->x = 1;
			cmd->fd[0] = -4;
			ft_putstr_fd(file, 2);
			perror(" ");
			g_var.sig_status = 1;
			return (0);
		}
		check_and_redirect(&cmd->fd[0], fd);
	}
	return (1);
}

void	check_and_redirect(int *inf_out, int fd)
{
	if (*inf_out != 0)
		close(*inf_out);
	*inf_out = fd;
}
