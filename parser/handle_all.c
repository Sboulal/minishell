/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:21:31 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/06 04:12:49 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/lexer.h"

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

t_mini	*handle_cmd(t_mini *cmd, t_lexer *tokens)
{
	// int		wc;
	int		i;
	int		j;
	t_list	*list;
	t_list	*tmp;
	int		in;
	int		out;
	t_lexer	*head;

	// wc = 0;
	j = 0;
	head = tokens;
	list = NULL;
	int k = check_redirections(tokens);
	if (k == 0)
	{
		in = -4;
		out = -4;
		if (cmd->fd[0] > 2)
			in = cmd->fd[0];
		if (cmd->fd[1] > 2)
			out = cmd->fd[1];
	}
	else
	{
		in = -4;
		out = - 4;
	}
	head = tokens;
	i = 0;
	// head = tokens;
	while ((head) && head->type != PIPE_LINE)
	{
		if (head && head->type == WORD && head->type != LIMITER)
		{
			ft_lstadd_back(&list, ft_lstnew(head->token));
		}
		head = head->next;
	}
	tmp = list;
	// list = list->next;
	// if (!list)
	// 	list = tmp;
	t_list *list_head;
	
	if (list)
	{
		cmd->cmd = ft_strdup(list->content);
		cmd->next = NULL;
		list = list->next;
	}
	else
	{
		cmd->cmd = NULL;
		cmd->next = NULL;
	}
	if (list)
	{
		list_head = list;
		while (list_head)
		{
			list_head = list_head->next;
			i++;
		}
	}
	cmd->nbr_arg = i;
	if (list)
	{
		cmd->arg = (char **)malloc(sizeof(char *) * (i + 1));
		if (!cmd->arg)
			return (cmd);
		list_head = list;
		while (list_head)
		{
			cmd->arg[j] = ft_strdup(list_head->content);
			list_head = list_head->next;
			j++;
		}
		cmd->arg[j] = NULL;
	}
	else
		cmd->arg = NULL;
	if (!k)
	{
		cmd->fd[0] = in;
		cmd->fd[1] = out;
	}
	ft_lstclear(&tmp);
	return (cmd);
}
