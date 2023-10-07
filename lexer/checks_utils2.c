/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:13:28 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/07 02:03:24 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("error", 2);
		return (1);
	}
	return (0);
}

int	ft_open(char *path, int flags, int mode)
{
	int	fd;

	fd = open(path, flags, mode);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(path);
	}
	return (fd);
}

void	token_herdoc(t_lexer *lexer)
{
	t_lexer	*head;

	head = lexer;
	while (head)
	{
		if (head->type == HERE_DOC)
			(head->next)->type = LIMITER;
		head = head->next;
	}
}
