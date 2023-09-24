/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:12:37 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/24 08:10:44 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"

// t_mini *ft_new_command(int i,char **str)
// {
//    int k;
//    t_mini *new;

//    k = 1;
//     if (!str)
//         return (NULL);
//     (new) = (t_mini *)malloc(sizeof(t_mini));
//     (new)->nbr_arg = i;
//     if (!str[0])
//         return (NULL);
//     (new)->cmd = str[0];
//     (new)->next = NULL;
//     while (str[k])
//         k++;
//     (new)->arg = (char **)malloc(sizeof(char *) * (k + 1));
//     k = 1;
//     int d;

//     d = 0;
//     while (str[k])
//     {
//         (new)->arg[d] = ft_strdup(str[k]);
//         d++;
//         k++;
//     }
//     (new)->arg[d] = NULL;
//     (new)->fd[0] = -4;
//     (new)->fd[1] = -4;
//     return ((new));
// }

void	sort_list(t_export **exp)
{
	t_export	*head;
	t_export	*tomp;
	int			i;

	i = 0;
	head = *exp;
	while (head->next)
	{
		tomp = head->next;
		while (tomp)
		{
			if ((ft_strcmp(head->variable, tomp->variable) > 0))
				sort_utile(head, tomp);
			else
				tomp = tomp->next;
		}
		head = head->next;
	}
}

void	buil_exec_pipe(t_exec **exp, t_mini *cmd)
{
	if (!cmd)
		return ;
	if (ft_strcmp(cmd->cmd, "./minishell") == 0)
		edit_shlvl(exp);
	if ((ft_strcmp(cmd->cmd, "env") != 0) && ft_strcmp(cmd->cmd, "exit") != 0
		&& ft_strcmp(cmd->cmd, "echo") != 0 && ft_strcmp(cmd->cmd, "pwd") != 0
		&& ft_strcmp(cmd->cmd, "unset") != 0 && ft_strcmp(cmd->cmd, "cd") != 0
		&& ft_strcmp(cmd->cmd, "export") != 0)
		exec_pipe(exp, cmd);
	else
		builtins(exp, cmd);
}

void	protect_cmd(t_envp **env)
{
	char	str[PATH_MAX];
	char	**string;
	char	*str1;
	char	*tmp;

	getcwd(str, PATH_MAX);
	string = ft_split(str, '/');
	g_var.env = (char **)malloc(sizeof(char *) * 5);
	str1 = ft_strjoin("PATH=/Users/", string[1]);
	str1 = ft_strjoin2(str1, "/.brew/bin:/usr/local/bin:/usr/bin:");
	str1 = ft_strjoin2(str1, ":/bin:/usr/sbin:/sbin:/usr/local/munki:");
	str1 = ft_strjoin2(str1, "/Library/Apple/usr/bin:/Users/");
	str1 = ft_strjoin2(str1, string[1]);
	str1 = ft_strjoin2(str1, "/.brew/bin");
	add_back_env(env, list_env(str1));
	g_var.env[0] = ft_strdup(str1);
	free(str1);
	tmp = ft_strjoin("PWD=", str);
	add_back_env(env, list_env(tmp));
	g_var.env[1] = ft_strdup(tmp);
	free(tmp);
	tmp = ft_strjoin("HOME=/Users/", string[1]);
	add_back_env(env, list_env(tmp));
	g_var.env[2] = ft_strdup(tmp);
	free(tmp);
	add_back_env(env, list_env("SHLVL=1"));
	g_var.env[3] = ft_strdup("SHLVL=1");
	tmp = ft_strjoin("_=", "/usr/bin/env");
	add_back_env(env, list_env(tmp));
	g_var.env[4] = ft_strdup(("_=/usr/bin/env"));
	free(tmp);
	g_var.env[5] = NULL;
	tabfree(string);
}

// void instiall_index(t_exec *exp)
// {
// 	t_envp *head;
// 	int	i;

// 	head = exp->env;
// 	i = 0;
// 	while (head)
// 	{
// 		i++;
// 		head = head->next;
// 	}
// }
void	exec_cmd(t_exec **exp, char **env)
{
	t_mini *head;
	int i;
	i = 0;
	(void)env;
	sig_cmd();
	if (!(*exp)->cmd)
		return ;
	if ((*exp)->cmd && (*exp)->cmd->next)
	{
		head = (*exp)->cmd;
		while (head)
		{
			head = head->next;
			i++;
		}
		(*exp)->nbr_cmd = i;
	}
	else
		(*exp)->nbr_cmd = 1;
	if ((!(*exp)->exp))
		return ;
	if (!((*exp)))
		return ;
	if (!((*exp)))
		return ;
	if (((*exp)->nbr_cmd == 1 && ft_strcmp((*exp)->cmd->cmd, "cd") == 0) || ((*exp)->nbr_cmd == 1 && ((*exp)->cmd->nbr_arg > 0)
		&&  (ft_strcmp((*exp)->cmd->cmd, "export") == 0)) || (ft_strcmp((*exp)->cmd->cmd, "exit") == 0) || ((*exp)->nbr_cmd == 1 && ft_strcmp((*exp)->cmd->cmd, "unset") == 0))
		builtins(exp, (*exp)->cmd);
	else
		use_pipe(exp, (*exp)->cmd);
}
