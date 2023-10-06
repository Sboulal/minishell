/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:12:37 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/06 21:59:59 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	protect_path(char **string, t_exec **exp)
{
	char	*str1;

	if (!(*string))
		return ;
	str1 = ft_strjoin("PATH=/Users/", string[1]);
	str1 = ft_strjoin2(str1, "/.brew/bin:/usr/local/bin:/usr/bin:");
	str1 = ft_strjoin2(str1, ":/bin:/usr/sbin:/sbin:/usr/local/munki:");
	str1 = ft_strjoin2(str1, "/Library/Apple/usr/bin:/Users/");
	str1 = ft_strjoin2(str1, string[1]);
	str1 = ft_strjoin2(str1, "/.brew/bin");
	add_back_env(&(*exp)->env, list_env(str1));
	(*exp)->env_string[0] = ft_strdup(str1);
	free(str1);
}

void	protect_home(char **string, t_exec **exp)
{
	char	*tmp;

	if (!(*string))
		return ;
	tmp = ft_strjoin("HOME=/Users/", string[1]);
	add_back_env(&(*exp)->env, list_env(tmp));
	(*exp)->env_string[2] = ft_strdup(tmp);
	free(tmp);
}

void	protect_cmd(t_exec **exp)
{
	char	str[PATH_MAX];
	char	**string;
	char	*tmp;

	getcwd(str, PATH_MAX);
	string = ft_split(str, '/');
	(*exp)->env_string = (char **)malloc(sizeof(char *) * 5);
	if (!(*exp)->env_string)
		return ;
	protect_path(string, exp);
	tmp = ft_strjoin("PWD=", str);
	add_back_env(&(*exp)->env, list_env(tmp));
	(*exp)->env_string[1] = ft_strdup(tmp);
	free(tmp);
	protect_home(string, exp);
	add_back_env(&(*exp)->env, list_env("SHLVL=1"));
	(*exp)->env_string[3] = ft_strdup("SHLVL=1");
	tmp = ft_strjoin("_=", "/usr/bin/env");
	add_back_env(&(*exp)->env, list_env(tmp));
	(*exp)->env_string[4] = ft_strdup(("_=/usr/bin/env"));
	free(tmp);
	(*exp)->env_string[5] = NULL;
	tabfree(string);
}

void	cmpt_cmd(t_exec **exp)
{
	t_mini	*head;
	int		i;

	i = 0;
	if (!(*exp) && !(*exp)->cmd)
		return ;
	head = (*exp)->cmd;
	while (head)
	{
		head = head->next;
		i++;
	}
	(*exp)->nbr_cmd = i;
}

void	exec_cmd(t_exec **exp, char **env)
{
	(void)env;
	sig_cmd();
	if (!(*exp)->cmd)
		return ;
	cmpt_cmd(exp);
	if (!((*exp)))
		return ;
	if (!((*exp)))
		return ;
	if (((*exp)->nbr_cmd == 1 && ft_strcmp1((*exp)->cmd->cmd, "cd") == 0)
		|| ((*exp)->nbr_cmd == 1 && ((*exp)->cmd->nbr_arg > 0)
			&& (ft_strcmp1((*exp)->cmd->cmd, "export") == 0))
		|| ((*exp)->nbr_cmd == 1 && ft_strcmp1((*exp)->cmd->cmd, "exit") == 0)
		|| ((*exp)->nbr_cmd == 1 && ft_strcmp1((*exp)->cmd->cmd, "unset") == 0))
		builtins(exp, (*exp)->cmd);
	else
		use_pipe(exp, (*exp)->cmd);
}
