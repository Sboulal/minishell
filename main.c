/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:12:22 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/12 20:17:04 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lexer.h"

int main(int ac, char *argv[],char *env[])
{
  char *bas;
  (void)argv;
  (void)ac;
  (void)env;
  
 
  t_mini *mini;
  while(1)
  {
    bas = readline("bash$ ");
    if(bas == 0)
      break;
    if(ft_strlen(bas) > 0)
      add_history(bas);
    mini = parse(bas);
    
  }
   return (0);  
}

