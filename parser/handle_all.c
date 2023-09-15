/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:21:31 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/15 00:18:41 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../headers/lexer.h"

void	handle_pipes(t_mini *cmd, t_lexer *tokens)
{
	if (tokens->type == PIPE_LINE)
		cmd->fd[0] = tokens->pipe[READ_END];
	tokens = next_pipe(tokens);
	if (tokens)
		cmd->fd[1] = tokens->pipe[WRITE_END];
}

int	handle_redirection(t_mini *cmd, t_lexer *tokens)
{
	int	status;

	while (tokens && tokens->type != PIPE_LINE)
	{
		if (tokens->type == REDIRECTION)
		{
			if (!tokens->next)
				return (0);
			status = redirect(cmd, tokens->token, (tokens->next)->token);
			if (!status)
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
	int		wc;
	int		i;
	int		in;
	int		out;
	char	**options;
	t_lexer	*head;

	wc = 0;
	head = tokens;
	if (!check_redirections(tokens))
	{
		if (cmd->fd[0])
			in = cmd->fd[0];
		if (cmd->fd[1])
			out = cmd->fd[1];
	}
	else
	{
		in = -4;
		out = - 4;
	}
	cmd = (t_mini *) malloc(sizeof(t_mini));
	while (tokens && tokens->type != PIPE_LINE)
	{
		if (tokens->type == WORD)
			wc++;
		tokens = tokens->next;
	}
	options = (char **) malloc(sizeof(char *) * (wc + 1));
	i = 0;
	while (head && head->type != PIPE_LINE)
	{
		if (head->type == WORD)
			options[i++] = ft_strdup(head->token);
		head = head->next;
	}
	options[i] = NULL;
	cmd->nbr_arg = i - 1;
	cmd->arg = (char **)malloc(sizeof(char *) * i);
	cmd->cmd = options[0];
	cmd->next = NULL;
	int j = 0;
	i = 1;
	while (options[i])
	{
		cmd->arg[j] = ft_strdup(options[i]);
		i++;
		j++;
	}
	cmd->arg[j] = NULL;
	cmd->fd[0] = in;
	cmd->fd[1] = out;
	return (cmd);
}