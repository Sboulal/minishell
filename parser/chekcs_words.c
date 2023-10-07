/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chekcs_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:24:58 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 02:20:51 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_all_fds(t_mini *head)
{
	t_mini	*tmp;

	if (!head)
		return ;
	tmp = head;
	while (tmp->next)
	{
		if (tmp->fd[1] != 1)
			ft_close(tmp->fd[1]);
		if (tmp->fd[0] != 0)
			ft_close(tmp->fd[0]);
		tmp = tmp->next;
	}
}

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	handle_pipes(t_mini *cmd, t_lexer *tokens)
{
	if (tokens->type == PIPE_LINE)
		cmd->fd[0] = tokens->pipe[READ_END];
	tokens = next_pipe(tokens);
	if (tokens)
		cmd->fd[1] = tokens->pipe[WRITE_END];
}

int	handle_redirection(t_mini *cmd, t_lexer *tokens, t_envp *env)
{
	int	status;

	while (tokens && tokens->type != PIPE_LINE)
	{
		if (tokens->type == REDIRECTION)
		{
			if (!tokens->next)
				return (0);
			status = redirect(cmd, tokens->token, (tokens->next)->token, env);
			if (!status || status == -1)
				return (status);
			tokens = tokens->next;
			tokens->type = FILE;
		}
		else
			tokens = tokens->next;
	}
	return (1);
}

t_list	*cmd_list(t_lexer *tokens)
{
	t_lexer	*head;
	t_list	*list;

	if (!tokens)
		return (NULL);
	list = NULL;
	head = tokens;
	while ((head) && head->type != PIPE_LINE)
	{
		if (head && head->type == WORD && head->type != LIMITER)
		{
			ft_lstadd_back(&list, ft_lstnew(head->token));
		}
		head = head->next;
	}
	return (list);
}
