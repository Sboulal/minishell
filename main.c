/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:12:22 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/02 11:31:46 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lexer.h"

int main(int ac, char *argv[],char *env[])
{
  char *bas;
  int e_l;
  (void)argv;
  (void)ac;
  (void)env;
  while(1)
  {
    bas = readline("bash$ ");
    if(ft_strlen(bas) > 0)
      add_history(bas);
    if(bas == 0)
      return(0);
    e_l = lexer;
    // free(bas);
  }
   return (0);  
}