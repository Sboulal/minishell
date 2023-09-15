/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:17:33 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/15 18:10:57 by nkhoudro         ###   ########.fr       */
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
	pt = (char **)malloc(sizeof(char *) * (cmd->nbr_arg + 2));
	if (!pt)
		return (NULL);
	pt[i] = ft_strdup(path);
	i++;
	j = 0;
	while (cmd->arg[j])
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

void	exec_pipe(t_exec **exp, t_mini *cmd)
{
	int		i;
	t_envp	*head;
	char	**str;
	char	**pt;
	char	*path;

	i = 0;
	head = (*exp)->env;
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
	g_var.status = execve(*pt, pt, g_var.env);
	printf("minishell: %s: command not found\n", cmd->cmd);
	exit(1);
	// perror("execve");
}
