/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   need_this_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:47:07 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/24 05:40:22 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lexer.h"

void	free_cmd(t_mini *head)
{
	t_mini	*tmp;
	if(!head)
		return ;
	while (head)
	{
		if (head->arg)
			tabfree(head->arg);
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

void	close_fds(t_mini *cmd)
{
	if (cmd->fd[0] != 0 && cmd->fd[0] != -4)
		close(cmd->fd[0]);
	if (cmd->fd[1] != 0 && cmd->fd[1] != -4)
		close(cmd->fd[1]);
}

void	add(t_mini **cmds, t_mini *new)
{
	t_mini	*last;

	last = *cmds;
	if (!last)
		*cmds = new;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

t_lexer	*free_cmds(t_mini *new, t_lexer *tokens)
{
	t_lexer	*tmp;

	free(new);
	if (!tokens)
		return (NULL);
	if (tokens->type == PIPE_LINE)
		tokens = tokens->next;
	while (tokens && tokens->type != PIPE_LINE)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->type == WORD)
			free(tmp->token);
	}
	return (tokens);
}

t_lexer	*add_cmd(t_mini **cmds, t_lexer *tokens, t_envp *env)
{
	t_mini	*new;
	int		status;

	new = ft_calloc(sizeof(t_mini));
	// if(handle_heredocs(new, tokens, env) == 4)
	// 	return (NULL);
	handle_pipes(new, tokens);
	if (tokens->type == PIPE_LINE)
		tokens = tokens->next;
	status = (handle_heredocs(new, tokens, env) && handle_redirection(new, tokens, env));
	if (!status)
	{
		close_fds(new);
		g_var.status = 1;
		return (free_cmds(new, tokens));
	}
	else
		g_var.status = 0;
	new = handle_cmd(new, tokens);
	add(cmds, new);
	return (next_pipe(tokens));
}