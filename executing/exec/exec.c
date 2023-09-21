/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:17:33 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/21 12:58:58 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"

char	**execve_join(t_exec *exp, char *path, t_mini *cmd)
{
	char	**pt;
	int		i;
	int		j;

	i = 0;
	(void) exp;
	if (!path || !cmd)
		return (NULL);
	pt = (char **)malloc(sizeof(char *) * (cmd->nbr_arg + 2));
	if (!pt)
		return (NULL);
	pt[i] = ft_strdup(path);
	i++;
	j = 0;
	while (j < cmd->nbr_arg)
	{
		pt[i] = ft_strdup(cmd->arg[j]);
		j++;
		i++;
	}
	pt[i] = NULL;
	return (pt);
}

char	**exec_chec_join(char *str, char *path, t_mini *cmd, t_exec **exp)
{
	char	**pt;

	if (str)
		pt = execve_join((*exp), path, cmd); //need check
	else
		pt = execve_join((*exp), cmd->cmd, cmd);
	return (pt);
}
void check_permision(t_mini *cmd)
{
	struct stat sb;
	
	if (!cmd)
		return ;
		// stat is a system call that returns information about a file pointed to by path.
		// stat() stats the file pointed to by path and fills in buf.
		//access() checks whether the calling process can access the file pathname.
	if (stat(cmd->cmd, &sb) == -1 && access(cmd->cmd, X_OK) == 0 && !ft_strncmp(cmd->cmd, "/", 2))
	{
		ft_putstr_fd("minishell : ",2);
		ft_putstr_fd(cmd->cmd,2);
		ft_putstr_fd(": Is a directory\n",2);
		g_var.status = 126;
		exit(1);
	}
	
}
void	exec_pipe(t_exec **exp, t_mini *cmd)
{
	int		i;
	t_envp	*head;
	char	**str;
	char	**pt;
	char	*path;

	i = 0;
	if (!(*exp) || !(cmd))
		return ;
	head = (*exp)->env;
	check_permision(cmd);
	while (head && ft_strcmp(head->variable, "PATH") != 0)
		head = head->next;
	path = head->env;
	str = ft_split(path, ':');
	while (str[i])
	{
		path = ft_strjoin(str[i], "/");
		path = ft_strjoin(path, cmd->cmd);
		if (!access(path, F_OK | X_OK))
			break ;
		i++;
	}
	pt = exec_chec_join(str[i], path, cmd, exp);
	if (!pt)
		return ;
	g_var.status = execve(*pt, pt, g_var.env);
	ft_putstr_fd("minishell : ",2);
	ft_putstr_fd(cmd->cmd,2);
	ft_putstr_fd(": command not found\n",2);
	exit(1);
	// perror("execve");
}
