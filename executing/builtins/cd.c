/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:46:28 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/20 23:06:22 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"

void	change_olde_pwd_exp(t_export **list, char *old)
{
	t_export	*head;

	head = *list;
	if (!old)
		return ;
	while ((head)->next && ft_strncmp((head)->next->variable, "OLDPWD", 4))
		(head) = (head)->next;
	if (!(head->next))
	{
		add_back_exp(&head, list_exp(ft_strjoin("OLDPWD=", old)));
		return ;
	}
	head = head->next;
	if (head)
	{
		head->value = old;
		head->exp = ft_strjoin("OLDPWD=", "=");
		head->exp = ft_strjoin(head->exp, "\"");
		head->exp = ft_strjoin(head->exp, head->value);
		head->exp = ft_strjoin(head->exp, "\"");
		return ;
	}
}

void	change_pwd_exp(t_export **list)
{
	char		str[PATH_MAX];
	t_export	*head;

	head = *list;
	while ((head)->next && ft_strncmp((head)->next->variable, "PWD", 4))
		(head) = (head)->next;
	change_olde_pwd_exp(list, (head)->next->value);
	getcwd(str, PATH_MAX);
	if (!(head->next))
	{
		add_back_exp(list, list_exp(ft_strjoin("PWD=", str)));
		return ;
	}
	head = head->next;
	if (head)
	{
		head->value = str;
		head->exp = ft_strjoin("PWD", "=");
		head->exp = ft_strjoin(head->exp, "\"");
		head->exp = ft_strjoin(head->exp, head->value);
		head->exp = ft_strjoin(head->exp, "\"");
		return ;
	}
}

void	change_pwd(t_envp **list, t_exec **exp)
{
	char	str[260];
	t_envp	*head;

	head = *list;
	change_pwd_exp(&(*exp)->exp);
	while ((head)->next && ft_strncmp((head)->next->variable, "PWD", 4))
		(head) = (head)->next;
	change_olde_pwd(list, (head)->next->value);
	getcwd(str, 260);
	if (!(head->next))
	{
		add_back_env(list, list_env(ft_strjoin("PWD=", str)));
		return ;
	}
	head = head->next;
	if (head)
	{
		(head)->value = str;
		(head)->env = ft_strjoin("PWD=", str);
		return ;
	}
}

void	change_olde_pwd(t_envp **list, char *old)
{
	char	str[260];
	t_envp	*head;

	head = *list;
	if (!old)
		return ;
	while ((head)->next && ft_strncmp((head)->next->variable, "OLDPWD", 4))
		(head) = (head)->next;
	if (!(head->next))
	{
		add_back_env(list, list_env(ft_strjoin("OLDPWD=", old)));
		return ;
	}
	head = head->next;
	if (head)
	{
		(head)->value = str;
		(head)->env = ft_strjoin("OLDPWD=", old);
		return ;
	}
}

void	cd_derc(char **args, t_envp **list_env, t_exec **exp, t_mini *cmd)
{
	t_envp	*head;
	char	*c;

	head = *list_env;
	if (cmd->nbr_arg == 0)
	{
		c = get_env(head);
		chdir(c);
		if (!c)
		{
			printf("minishell: cd: HOME: No such file or directory\n");
			g_var.status = 1;
		}
		change_pwd(&head, exp);
		return ;
	}
	else if (chdir(args[0]) != 0)
	{
		printf("minishell: cd: %s: No such file or directory\n", args[0]);
		g_var.status = 2;
	}
	change_pwd(&head, exp);
	g_var.status = 0;
	if ((*exp)->nbr_cmd > 1)
		exit(0);
}
