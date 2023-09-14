/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_to_execute.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:20:31 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/14 16:30:46 by saboulal         ###   ########.fr       */
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
	while (*token)
	{
		if (*token == -1)
			*token = '$';
		token++;
	}
}

void	free_token_word(t_lexer *token, char *word)
{
	free(word);
	free(token);
}

t_mini	*convert_to_cmds(t_lexer *tokens)
{
	t_lexer	*head;
	t_mini	*cmds;

	head = tokens;
	cmds = NULL;
	open_pipes(head);
	while (tokens)
		tokens = add_cmd(&cmds, tokens);
	
	return (cmds);
}