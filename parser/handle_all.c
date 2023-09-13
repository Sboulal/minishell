/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:21:31 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/13 18:19:15 by nkhoudro         ###   ########.fr       */
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

void	handle_cmd(t_mini *cmd, t_lexer *tokens)
{
	int		wc;
	int		i;
	char	**options;
	t_lexer	*head;

	wc = 0;
	head = tokens;
	while (tokens && tokens->type != PIPE_LINE)
	{
		if (tokens->type == WORD)
			wc++;
		tokens = tokens->next;
	}
	options = ft_calloc(sizeof(char *) * (wc + 1));
	i = 0;
	while (head && head->type != PIPE_LINE)
	{
		if (head->type == WORD)
			options[i++] = ft_strdup(head->token);
		head = head->next;
	}
	options[i] = NULL;
	cmd->arg = options;
	cmd->cmd = options[0];
}
