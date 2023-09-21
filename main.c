/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:12:22 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/21 21:26:00 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "headers/lexer.h"
#include "headers/exec.h"

static int is_isspace(char c)
{
    return (c == ' ' || (c >= '\t' && c <= '\r'));
}

void	ft_lstclear_cmd(t_mini **lst)
{
	t_mini	*tmp;

	if (!lst )
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}
void	ft_lstclear_exp(t_export **lst)
{
	t_export	*tmp;

	if (!lst )
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}
void	ft_lstclear_env(t_envp **lst)
{
	t_envp	*tmp;

	if (!lst )
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}
static void ft_add_history(char *bas)
{
  char *ptr;

  ptr = bas;
  if(!bas) 
    return ;
  while(*bas && is_isspace(*bas))
    bas++;
  if(*bas != 0)
    add_history(ptr);
}

int main(int ac, char *av[],char *env[])
{
  char *bas;
  int i;
  int k;
  t_export *exp;
  t_exec *exec;

  exp = NULL;
  k = 0;
  exec = (t_exec *)ft_calloc(sizeof(t_exec));
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
	  sig();
    bas = readline("minishell$ ");
	if(bas == 0)
		break;
	if (ft_strlen(bas) == 0)
		continue;
	ft_add_history(bas);
    if (k == 0)
    {
        if (*env)
		      g_var.env = env;
        if (!(*env) && !((exec->env)))
			      protect_cmd(&exec->env);
	      else if (!(exec->env) && (*(g_var.env)))
          creat_env(&exec->env);
	      creat_exp(&exec->exp, exec->env);
        exp = exec->exp;
         k = 1;
    }
    exec->cmd = parse(bas, exec->env);
//     if (exec->cmd)
//         exec_cmd(&exec, env);
//     if (exec->cmd)
//         ft_lstclear_cmd(&exec->cmd);
  }
  ft_lstclear_exp(&exp);
  ft_lstclear_env(&exec->env);
  free(exec);
   return (0);  
}

