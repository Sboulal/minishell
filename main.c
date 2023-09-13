/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:12:22 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/13 18:24:09 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "headers/lexer.h"
#include "headers/exec.h"

int main(int ac, char *av[],char *env[])
{
  char *bas;
  int i;
  t_exec exec;

	i = 0;
    if(ac != 1)
    {
	    while(av[i])
	    {
	    	printf("%s: ", av[i]);
	    	i++;
	    }
	    printf("No such file or directory\n");
        return (0);
    }
  while(1)
  {
	sig_cmd();
    bas = readline("bash$ ");
    if(bas == 0)
      break;
    if(ft_strlen(bas) > 0)
      add_history(bas);
    exec.cmd = parse(bas);
	if (*env)
		g_var.env = env;
	else
		g_var.env = NULL;
	printf("%s\n", exec.cmd->arg[0]);
    exec_cmd(&exec, env);
  }
   return (0);  
}

