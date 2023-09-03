/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:57:02 by saboulal          #+#    #+#             */
/*   Updated: 2023/07/14 14:07:11 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_list *initial_type(t_list *tk)
{
    tk = (t_list *)malloc(sizeof(t_list));
    if(!tk)
        return(NULL);
    return(tk);
}

t_lexer *add_element(char *str,int size,enum e_token tok,enum e_state state)
{
    t_lexer *lex;
    int len;
    char *copy;

    lex = malloc(sizeof(t_lexer));
    if(!lex)
        return (NULL);
    while(str[len])
        len++;
    copy = malloc(sizeof(char *) * len + 1);
    if(!copy)
        return(NULL);
    lex->str = str;
    lex->lenght = size;
    lex-> type= tok;
    lex->state = state;
    return(lex);
}

void free_any(t_list *list)
{
    t_lexer *temp;
    
    temp = list->head;
    while(temp != NULL)
    {
        free(temp->str);
        free(temp);
        temp = temp->next;
    }
    free(list);
}

void add_end(t_list *all,t_lexer *end)
{
    if(all->head == NULL)
        all->head = end; 
    else
    {
        all->last->next = all;
        end->prev = all->last;
    }      
    all->last = end;
    all->how++;
        
}