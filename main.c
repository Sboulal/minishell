/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:12:22 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 02:23:53 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/exec.h"

static int	is_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

void	ft_lstclear_cmd(t_mini **lst)
{
	t_mini	*tmp;

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

	if (!lst)
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

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}

static void	ft_add_history(char *bas)
{
	char	*ptr;

	ptr = bas;
	if (!bas) 
		return ;
	while (*bas && is_isspace(*bas))
		bas++;
	if (*bas != 0)
	add_history(ptr);
}

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

int	check_line(int ac, char **av)
{
	if (ac != 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	return (1);
}

int	check_env(t_exec	*exec, char	**env, int	*k)
{
	if (*k == 0)
    {
        if (*env)
			exec->env_string = creat_string_env(env);
        if (!(*env) && !((exec->env)))
			protect_cmd(&exec);
	    else if (!(exec->env) && (*(exec->env_string)))
        	creat_env(&exec);
	    creat_exp(&exec->exp, exec->env);
         *k = 1;
    }
	return (0);
}
int exec_part(t_exec *exec,char **env)
{
	if (exec && exec->cmd)
    	exec_cmd(&exec, env);
	return (0);
}

void check_fd( t_mini *head, t_exec *exec, char *bas)
{
	while (head)
	{
		if (head->fd[READ_END] > 2)
			close(head->fd[READ_END]);
		if (head->fd[WRITE_END] > 2)
			close(head->fd[WRITE_END]);
		head = head->next;
	}
	if (exec->cmd)
    	ft_lstclear_cmd(&exec->cmd);
  	if (bas)
    	free(bas);
}

int	ft_read(char *line)
{
	int w;
	
	line = readline("minishell$ ");
	if(line == 0)
	{
		printf("exit\n");
		exit(0);
	}
	w = 0;
	while(is_isspace(line[w]) && line[w])
		w++;
	return (0);
}
void	clear_end(t_exec	*exec)
{
	tabfree(exec->env_string);
	ft_lstclear_env(&exec->env);
	ft_lstclear_exp(&exec->exp);
	free(exec);
}

int	control_line(char *bas, t_exec **exec, char **env, int *k)
{
	int	w;

	w = 0;
	if(bas == 0)
	{
		printf("exit\n");
		exit(0);
	}
	w = 0;
	while(is_isspace(bas[w]) && bas[w])
		w++;
	if (bas[w] == '\0' || ft_strlen(bas) == 0)
	{
		free(bas);
		return (1);
	}
	ft_add_history(bas);
	check_env((*exec), env, k);
	(*exec)->cmd = parse(bas, (*exec)->env);
	return (0);
}

void	herdoc_norm(t_exec *exec, char *bas)
{
	if (exec->cmd)
		free_cmd(exec->cmd);
	free(bas);
	close(g_var.heredoc_flag);
	g_var.heredoc_flag = 0;
	g_var.status = 1;
}

int	main(int	ac, char	*av[], char	*env[])
{
	int			k;
	char		*bas;
	t_mini		*head;
	t_exec		*exec;

  k = 0;
  exec = (t_exec *) ft_calloc(sizeof(t_exec));
	check_line(ac, av);
	while (1)
	{
		sig();
		bas = readline("minishell$ ");
		if (control_line(bas, &exec, env, &k))
			continue;
		if (g_var.heredoc_flag)
		{
			herdoc_norm(exec, bas);
			continue ;
		}
		exec_part(exec,env);
		head = exec->cmd;
		check_fd(head, exec, bas);
	}
	clear_end(exec);
	return (0);
}



