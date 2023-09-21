/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:42:48 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/21 16:43:39 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lexer.h"

int	check_pipes(t_lexer *lexer)
{
	int	word_before;

	word_before = 0;
	while (lexer)
	{
		if (lexer->type == WORD)
			word_before = 1;
		if (lexer->type == PIPE_LINE)
		{
			if (!word_before || !word_after(lexer))
				return (0);
			word_before = 0;
		}
		lexer = lexer->next;
	}
	return (1);
}

int	check_parse(t_lexer *lexer)
{
	if (!check_invalid_operator(lexer))
		return (0);
	if (!check_redirections(lexer))
		return (0);
	if (!check_pipes(lexer))
		return (0);
	return (1);
}

void	token_herdoc(t_lexer *lexer)
{
	t_lexer	*head;

	head = lexer;
	while (head)
	{
		if (head->type == HERE_DOC)
			(head->next)->type = LIMITER;
		head = head->next;
	}
}

void	ft_exit(int status, char *msg)
{
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(status);
}