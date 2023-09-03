/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:09:34 by saboulal          #+#    #+#             */
/*   Updated: 2023/07/18 09:02:56 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int token_line(t_list *tok,char *str,enum e_state *state)
{
    int i ;

    i = 0;
    while(str[i])
    {
        if(!ft_special_char(str[i]))
           string_word();
       else if(str[i] == '\'')
            single_quote();
        else if(str[i] == '\"')
            Double_quote();
        else if(str[i] == '$')
            Dollar();
        else if(str[i] == '>' || str[i] == '<')
            redirections();
        else if(str[i] == '|')
            pipe();
        
        
        i++;
    }
}
t_list  ft_check_lexical(char *lex)
{
    int a[1];
    /*This is token type word pipe ........*/
    t_list *type;
    enum e_state any;

    any = GENERAL;
    type = NULL;
    type = initial_type(type);
    
    if(type)
    {
        while(lex[a[0]])
        {
            a[0] = tok_line(type,lex,&any);
            a[0]++;
        }
    }
    free(lex);
    return (type);
    
    
    
}