/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:57:02 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/04 20:06:39 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

t_lexer *create_node(char *s)
{
		t_lexer *p;

		// p = NULL;
		// if(p == NULL)
		// 	return(NULL);
		p = ft_calloc(sizeof(t_lexer));
		p->token = ft_strdup(s);
		p->type = check_token(s);
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
