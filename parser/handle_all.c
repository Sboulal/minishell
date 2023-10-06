/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:21:31 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/06 21:43:03 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

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
// int handle_norm(t_mini *mini,)
// {
// 	int		in;
// 	int		out;
// 	int		k;

// 	k = check_redirections(tokens);
// 	if (k == 0)
// 	{
// 		in = -4;
// 		out = -4;
// 		if (mini->fd[0] > 2)
// 			in = mini->fd[0];
// 		if (mini->fd[1] > 2)
// 			out = mini->fd[1];
// 	}
// 	else
// 	{
// 		in = -4;
// 		out = - 4;
// 	}
// 	return (0);
// }
t_list *cmd_list(t_lexer *tokens)
{
	t_lexer *head;
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
void	cmd_repl_nor(t_mini **cmd, t_list	**list)
{
	(*cmd)->cmd = ft_strdup((*list)->content);
	(*cmd)->next = NULL;
	(*list) = (*list)->next;
}
t_list	*cmd_repl(t_lexer *tokens, t_mini **cmd, int *i)
{
	t_list	*list;
	t_list	*tmp;
	t_list	*list_head;

	list = cmd_list(tokens);
	tmp = list;
	if (list)
		cmd_repl_nor(cmd, &list);
	else
	{
		(*cmd)->cmd = NULL;
		(*cmd)->next = NULL;
	}
	if (list)
	{
		list_head = list;
		while (list_head)
		{
			list_head = list_head->next;
			(*i)++;
		}
	}
	list = tmp;
	return (list);
}
t_mini	*arg_repl(t_list *list, int i,t_mini **cmd)
{
	t_list *list_head;
	int		j;

	j = 0;
	if (list)
	{
		(*cmd)->arg = (char **)malloc(sizeof(char *) * (i + 1));
		if (!(*cmd)->arg)
			return ((*cmd));
		list_head = list->next;
		while (list_head)
		{
			(*cmd)->arg[j] = ft_strdup((char *)list_head->content);
			list_head = list_head->next;
			j++;
		}
		(*cmd)->arg[j] = NULL;
	}
	else
		(*cmd)->arg = NULL;
	return (NULL);
}
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
	int	k;

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
