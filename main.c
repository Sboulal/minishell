/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:12:22 by saboulal          #+#    #+#             */
/*   Updated: 2023/06/25 23:46:30 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
int check_word(char *str)
{
	int i;
	int k;
	int len;	
	i = 0;
	k = 0;
	len = ft_strlen(str);
	while (str[i])
	{
	   if (ft_isalpha(str[i]))
	     k++;
	   else
	     break;
	   i++;
	}
	if (len == k)
	 return (-1);
	return (0);
}

int check_token(char **cmd)
{
	int i;
	
	enum e_token token;
	
	
	i = -1;
	while (cmd[++i])
	{
		if (check_word(cmd[i]) == -1)
			token = WORD;
		else if (ft_strchr(cmd[i],'|'))
			token = PIPE_LINE;	
		else if (ft_strchr(cmd[i],'\n'))
			token = NEW_LINE;	
		else if (ft_strchr(cmd[i],'$'))
			token = ENV;	
		else if (ft_strchr(cmd[i],'\''))
			token = QOUTE;	
		else if (ft_strchr(cmd[i],'<'))
			token = REDIR_IN;	
		else if(ft_strchr(cmd[i],'>'))
			token = REDIR_OUT;
		else if(ft_strchr(cmd[i],'&'))
			token = AND;
		else if(ft_strchr(cmd[i],HERE_DOC))
			token = HERE_DOC;
		else if(ft_strchr(cmd[i],DREDIR_OUT))
			token = DREDIR_OUT;
		else if(ft_strchr(cmd[i],DOUBLE_QOUTE))
			token = DOUBLE_QOUTE;
		
	}
   
	return (0);
}
int main(int ac, char *argv[],char *env[])
{
  (void)argv;
  (void)env;
  (void)ac;
  char *cmd ;
  char **comand;
 
  // t_lexer *a = NULL;
  // char **str;
  int i;
  
  i = 0;
   if(ac != 1)
    exit(0);
  
    while(1)
    {
         cmd = readline("minishell$ ");
       if(cmd && *cmd)
          add_history(cmd);
		while(cmd[i])
		{
			comand = ft_split(cmd, ' ');
        	check_token(comand);
            i++;			
		}
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