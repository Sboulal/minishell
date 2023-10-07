/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:11:43 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/07 02:03:36 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_invalid_operator(t_lexer *lexer)
{
	while (lexer)
	{
		if (lexer->type == OPERATOR)
			return (0);
		lexer = lexer->next;
	}
	return (1);
}

int	check_redirections(t_lexer *lexer)
{
	while (lexer)
	{
		if (lexer->type == REDIRECTION || lexer->type == HERE_DOC)
		{
			if (lexer->next)
			{
				if ((lexer->next)-> type != WORD)
					return (0);
			}
			else
				return (0);
		}
		lexer = lexer->next;
	}
	return (1);
}

int	word_after(t_lexer *lexer)
{
	lexer = lexer->next;
	while (lexer && lexer->type != PIPE_LINE)
	{
		if (lexer->type == WORD)
			return (1);
		lexer = lexer->next;
	}
	return (0);
}

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
