/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:57:08 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/13 17:25:36 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../headers/lexer.h"

int check_invalid_operator(t_lexer *lexer)
{
	while(lexer)
	{
		if(lexer->type == OPERATOR)
			return (0);
		lexer = lexer->next;
	}
	return(1);
}

int check_redirections(t_lexer *lexer)
{
	while(lexer)
	{
		if(lexer->type == REDIRECTION || lexer->type == HERE_DOC)
		{
			if(lexer->next)
			{
				if((lexer->next)-> type != WORD)
					return (0);
			}
			else
				return (0);
		}
		lexer = lexer->next;
	}
	return (1);
}

int word_after(t_lexer *lexer)
{
	lexer = lexer->next;
	while(lexer && lexer->type != PIPE_LINE)
	{
		if (lexer->type == WORD)
			return (1);
		lexer = lexer->next;
	}
	return (0);
}

int check_pipes(t_lexer *lexer)
{
	int word_before;

	word_before = 0;
	while(lexer)
	{
		if(lexer->type == WORD)
			word_before = 1;
		if(lexer->type == PIPE_LINE)
		{
			if(!word_before || !word_after(lexer))
				return (0);
			word_before = 0;
		}
		lexer = lexer->next;
	}
	return (1);
}

int check_parse(t_lexer *lexer)
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
	while(lexer)
	{
		if(lexer->type == HERE_DOC)
			(lexer->next)->type =WORD;
		lexer = lexer->next;
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

void	ft_pipe(int fd[2])
{
	if (pipe(fd) == -1)
		ft_putstr_fd("error",2);
}

int	ft_open(char *path, int flags, int mode)
{
	int	fd;

	fd = open(path, flags, mode);
	if (fd == -1)
		perror(path);
	return (fd);
}
 
int	redirect(t_mini *cmd, char *type, char *file)
{
	int	fd;

	if (!ft_strcmp(type, ">>"))
	{
		fd = ft_open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			return (0);
		check_and_redirect(&cmd->fd[1], fd);
	}
	if (!ft_strcmp(type, ">"))
	{
		fd = ft_open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			return (0);
		check_and_redirect(&cmd->fd[1], fd);
	}
	if (!ft_strcmp(type, "<"))
	{
		fd = ft_open(file, O_RDONLY, 0);
		if (fd == -1)
			return (0);
		check_and_redirect(&cmd->fd[0], fd);
	}
	return (1);
}

void	check_and_redirect(int *inf_out, int fd)
{
	if (*inf_out != 0)
		close(*inf_out);
	*inf_out = fd;
}