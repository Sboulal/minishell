/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:17:33 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/06 23:25:34 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

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
		pt = execve_join((*exp), path, cmd);
	else
		pt = execve_join((*exp), cmd->cmd, cmd);
	return (pt);
}

void	check_permision(t_mini *cmd)
{
	struct stat	sb;

	if (!cmd)
		return ;
	if (stat(cmd->cmd, &sb) == 0 
		&& (access(cmd->cmd, X_OK) == 0) && !S_ISREG(sb.st_mode))
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		g_var.status = 126;
		exit(g_var.status);
	}
}

char	**find_cmd(char *path, t_exec **exp, t_mini *cmd)
{
	char	**str;
	char	**pt;
	int		i;

	i = 0;
	if (!path)
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		g_var.status = 127;
		exit(g_var.status);
	}
	str = ft_split(path, ':');
	while (str[i])
	{
		path = ft_strjoin(str[i], "/");
		path = ft_strjoin2(path, cmd->cmd);
		if (!access(path, F_OK | X_OK))
			break ;
		i++;
	}
	pt = exec_chec_join(str[i], path, cmd, exp);
	tabfree(str);
	return (pt);
}

void	exec_pipe(t_exec **exp, t_mini *cmd)
{
	t_envp	*head;
	char	*path;
	char	**pt;

	if (!(*exp))
		return ;
	head = (*exp)->env;
	check_permision(cmd);
	while (head && ft_strcmp(head->variable, "PATH") != 0)
		head = head->next;
	if (head)
		path = head->env;
	else
		path = NULL;
	pt = find_cmd(path, exp, cmd);
	if (!pt && cmd->cmd)
		return ;
	g_var.status = execve(*pt, pt, (*exp)->env_string);
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(cmd->cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_var.status = 127;
	exit(g_var.status);
}
