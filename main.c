/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:12:22 by saboulal          #+#    #+#             */
/*   Updated: 2023/06/23 20:02:01 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int main(int ac, char *argv[],char *env[])
{
  (void)argv;
  // (void)env;
  (void)ac;
  char *cmd ;
  enum e_token l;
  // t_lexer *a = NULL;
  // char **str;
  int i;
  
  i = 0;
  l = -1;
   if(ac != 1)
    exit(0);
  
    while(1)
    {
         cmd = readline("minishell $");
       if(cmd && *cmd)
          add_history(cmd);
        char *av[] = {"cat", NULL};
       if(execve("/bin/pwd",av,env) == -1)
            write(1,"not available\n",14);
        else
          write(1, "available\n", 10);
        /*part lexer */
    
        
        
        // while(cmd[i])
        // {
        //   argv = ft_split(cmd,' ');
        //   if(argv != NULL)
        //     return(1);        //   i++;
        // } 
    } 
   return (0);  
}