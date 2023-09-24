/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_to_execute.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:20:31 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/24 04:50:03 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lexer.h"
void	open_pipes(t_lexer	*tokens)
{
	while (tokens)
	{
		if (tokens->type == PIPE_LINE)
			ft_pipe(tokens->pipe);
		tokens = tokens->next;
	}
}

t_lexer	*next_pipe(t_lexer *tokens)
{
	if (!tokens)
		return (NULL);
	if (tokens->type == PIPE_LINE)
		tokens = tokens->next;
	while (tokens && tokens->type != PIPE_LINE)
		tokens = tokens->next;
	return (tokens);
}

// in this function we remplace the -1 occurences with $
// i need dollars dollars dollars is what i need
void	expands_dollars_dollars(char *token)
{
	char *head;

	if (!token)
		return ;
	head = token;
	while (*head)
	{
		if (*head == -1)
			*head = '$';
		head++;
	}
}

void	free_token_word(t_lexer *token, char *word)
{
	free(word);
	free(token);
}

t_mini	*convert_to_cmds(t_lexer *tokens, t_envp *env)
{
	t_lexer	*head;
	t_mini	*cmds;

	head = tokens;
	cmds = NULL;
	while (tokens)
		tokens = add_cmd(&cmds, tokens, env);
	
	return (cmds);
}