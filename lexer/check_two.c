/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:41:04 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/21 16:45:39 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lexer.h"

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
int	ft_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("error", 2);
		return (1);
	}
	return (0);
}