/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:45:16 by saboulal          #+#    #+#             */
/*   Updated: 2023/07/18 11:34:22 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
int ft_isspace(char c)
{
     if(c == '\n' || c == '\t' || c == ' ' || c == '\r' || c == '\v' || c == '\f')
        return(1);
    return(0);
}

int ft_special_char(char c)
{
    if(c == '\'' || c == '\"' || c == '>' || c == '<'  || c == '$' || c == '\0' || ft_isspace(c) || c == '|')
        return(1);
    return (0);
}

int string_word(t_list *tok,char *str,enum e_state state)
{
    int a[1];
    
    a[0] = 0;
    while(ft_special_char(str[a[0]]))
        a[0]++;
    add_end(tok,add_element(str,a[0],WORD,GENERAL));
    return (a[0]);
}


