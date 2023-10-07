/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:21:31 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 02:21:24 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_fil(int *fd, t_mini **cmd, int k)
{
	fd[0] = -4;
	fd[1] = -4;
	if (k == 0)
	{
		if ((*cmd)->fd[0] > 2)
			fd[0] = (*cmd)->fd[0];
		if ((*cmd)->fd[1] > 2)
			fd[1] = (*cmd)->fd[1];
	}
}

t_mini	*handle_cmd(t_mini *cmd, t_lexer *tokens)
{
	int		i;
	t_list	*list;
	int		fd[2];
	int		k;

	k = check_redirections(tokens);
	open_fil(fd, &cmd, k);
	i = 0;
	list = cmd_repl(tokens, &cmd, &i);
	cmd->nbr_arg = i;
	if (arg_repl(list, i, &cmd))
		return (cmd);
	if (!k)
	{
		cmd->fd[0] = fd[0];
		cmd->fd[1] = fd[1];
	}
	ft_lstclear(&list);
	return (cmd);
}
