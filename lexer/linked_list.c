/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:57:02 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/13 17:25:36 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lexer.h"

t_lexer *create_node(char *s)
{
		t_lexer *p;

		p = ft_calloc(sizeof(t_lexer));
		p->token = s;
		p->type =check_token(s);
		return(p);
}

void add_back(t_lexer **head, char *s)
{
	t_lexer *p;
	t_lexer *i;

	i = *head;
	p = create_node(s);
	if(i == NULL)
	{
		*head = p;
		return ;
	}
	while(i->next)
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