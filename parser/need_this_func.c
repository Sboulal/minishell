/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   need_this_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:47:07 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/25 01:30:08 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lexer.h"

void	free_cmd(t_mini *head)
{
	t_mini	*tmp;

	if (!head)
		return ;
	while (head)
	{
		free(head->cmd);
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
	t_lexer	*tmp;
	int		status;

	new = ft_calloc(sizeof(t_mini));
	handle_pipes(new, tokens);
	if (tokens->type == PIPE_LINE)
		tokens = tokens->next;
	status = (handle_heredocs(new, tokens, env) && handle_redirection(new, tokens, env));
	if (status == -1)
	{
		close_fds(new);
		g_var.status = 1;
		return (free_cmds(new, tokens));
	}
	new = handle_cmd(new, tokens);
	add(cmds, new);
	tmp = next_pipe(tokens);
	return (tmp);
}
