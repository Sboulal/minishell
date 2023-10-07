/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:57:02 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 11:28:46 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*create_node(char *s)
{
	t_lexer	*p;

	p = ft_calloc(sizeof(t_lexer)); 
	p->token = ft_strdup(s);
	p->type = check_token(s);
	p->y = 0;
	p->am = 0;
	p->next = NULL;
	return (p);
}

void	add_back(t_lexer **head, char *s)
{
	t_lexer	*p;
	t_lexer	*i;

	i = *head;
	p = create_node(s);
	if (i == NULL)
	{
		*head = p;
		return ;
	}
	while (i->next)
		i = i->next;
	i->next = p;
}

void	add_middle(t_lexer *token, char *word)
{
	t_lexer	*p;

	p = create_node(word);
	p->type = WORD;
	p->next = token->next;
	token->next = p;
}

void	add_ambg(t_lexer **lexer)
{
	t_lexer	*tmp;
	t_lexer	*prv;

	prv = NULL;
	tmp = *lexer;
	while (tmp)
	{
		if (prv)
		{
			if (prv->type == REDIRECTION && tmp->type == WORD)
				tmp->am = 1;
		}
		prv = tmp;
		tmp = tmp->next;
	}
}
