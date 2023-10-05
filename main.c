/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:12:22 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/05 13:37:55 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lexer.h"
#include "includes/exec.h"

t_global	g_var;
static int is_isspace(char c)
{
    return (c == ' ' || (c >= '\t' && c <= '\r'));
}

void	ft_lstclear_cmd(t_mini **lst)
{
	t_mini	*tmp;
	// int i = 0;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		if (tmp)
		{
			if (tmp->arg)
			{
				tabfree(tmp->arg);
				tmp->arg = NULL;
			}
			if (tmp->cmd)
			{
				free(tmp->cmd);
				tmp->cmd = NULL;
			}
			free(tmp);
			tmp = NULL;
		}
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
// void ft_leaks()
// {
//     system("leaks minishell");
// }
int	cmt_string(char **env)
{
	int	i;

	i = 0;
	if (!(*env))
		return (i);
	while (env[i])
		i++;
	return (i);
}
char	**creat_string_env(char **env)
{
	int	i;
	char	**env_string;

	i = cmt_string(env);
	env_string = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		env_string[i] = ft_strdup(env[i]);
		i++;
	}
	env_string[i] = NULL;
	return (env_string);
}
int main(int ac, char *av[],char *env[])
{
  char *bas;
  t_mini *head;
//   `
 
  int k;
//   t_export *exp;
  t_exec *exec;
//   t_mini *tmp;

//   exp = NULL;
  k = 0;
  // atexit(ft_leaks);
  exec = (t_exec *)ft_calloc(sizeof(t_exec));
	
    if(ac != 1)
    {
      ft_putstr_fd("minishell: ", 2);
	    ft_putstr_fd(av[1], 2);
      ft_putstr_fd(": No such file or directory\n", 2);
        return (0);
    }	  
  while(1)
  {
	  sig();
    bas = readline("minishell$ ");
	if(bas == 0)
	{
		printf("exit\n");
		exit(0);
	}
	int w = 0;
	while(is_isspace(bas[w]) && bas[w])
	{
		w++;
	}
	if (bas[w] == '\0')
	{
		free(bas);
		continue;
	}
	if (ft_strlen(bas) == 0)
	{
		free(bas);
		continue;
	}
	ft_add_history(bas);
    if (k == 0)
    {
        if (*env)
			exec->env_string = creat_string_env(env);
        if (!(*env) && !((exec->env)))
			protect_cmd(&exec);
	    else if (!(exec->env) && (*(exec->env_string)))
        	creat_env(&exec);
	    creat_exp(&exec->exp, exec->env);
         k = 1;
    }
	
    exec->cmd = parse(bas, exec->env);
	// if(exec->cmd->x == 1)
	// 	continue;
	if(g_var.heredoc_flag)
	{
		
		if (exec->cmd)
			free_cmd(exec->cmd);
		  free(bas);
		  close(g_var.heredoc_flag);
		  g_var.heredoc_flag = 0;
		  g_var.status = 1;
		continue;
	}
	if (exec && exec->cmd && exec->cmd->cmd)
    	exec_cmd(&exec, env);
	head = exec->cmd;
	while (head)
	{
		if (head->fd[READ_END] > 2)
			close(head->fd[READ_END]);
		if (head->fd[WRITE_END] > 2)
			close(head->fd[WRITE_END]);
		head = head->next;
	}
  if (exec->cmd)
	{
    ft_lstclear_cmd(&exec->cmd);
	}
	if (bas)
	{
    	free(bas);
	}
  }
  tabfree(exec->env_string);
  ft_lstclear_env(&exec->env);
  ft_lstclear_exp(&exec->exp);
  free(exec);
   return (0);  
}

