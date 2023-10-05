/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:46:28 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/05 21:56:53 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}
void	change_olde_pwd_exp(t_export **list, char *old)
{
	t_export	*head;

	head = *list;
	if (!old)
		return ;
	while ((head)->next && ft_strncmp((head)->next->variable, "OLDPWD", 4))
		(head) = (head)->next;
	if (!(head->next))
		return ;
	head = head->next;
	if (head)
	{
		if (head->value)
			ft_free(&head->value);
		free((head)->exp);
		head->value = old;
		head->exp = ft_strjoin("OLDPWD=", "=");
		head->exp = ft_strjoin2(head->exp, "\"");
		head->exp = ft_strjoin2(head->exp, head->value);
		head->exp = ft_strjoin2(head->exp, "\"");
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
	if (!(head->next))
		return ;
	change_olde_pwd_exp(list, (head)->next->value);
	getcwd(str, PATH_MAX);
	if (!(head->next))
		return ;
	head = head->next;
	if (head)
	{
		if (head->value)
			ft_free(&head->value);
		free((head)->exp);
		head->value = str;
		head->exp = ft_strjoin("PWD", "=");
		head->exp = ft_strjoin2(head->exp, "\"");
		head->exp = ft_strjoin2(head->exp, head->value);
		head->exp = ft_strjoin2(head->exp, "\"");
		return ;
	}
}
void	change_pwd_dir(void)
{
	ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent",2);
	ft_putstr_fd(":directories: No such file or directory\n",2);
	g_var.status = 126;
}
void	change_pwd(t_envp **list, t_exec **exp)
{
	char	str[PATH_MAX];
	char	*src;
	t_envp	*head;

	head = *list;
	(void) exp;
	change_pwd_exp(&(*exp)->exp);
	while ((head)->next && ft_strncmp((head)->next->variable, "PWD", 4))
		(head) = (head)->next;
	if (!(head->next))
		return ;
	change_olde_pwd(list, (head)->next->value);
	src = getcwd(str, PATH_MAX);
	if (!src && errno == ENOENT)
		change_pwd_dir();
	if (!(head->next))
		return ;
	head = head->next;
	if (head)
	{
		if (head->value)
			ft_free(&head->value);
		free((head)->env);
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
		return ;
	head = head->next;
	if (head)
	{
		if (head->value)
			ft_free(&head->value);
		free((head)->env);
		(head)->value = str;
		(head)->env = ft_strjoin("OLDPWD=", old);
		return ;
	}
}


void	cd_derc_err(char **args)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_var.status = 1;
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
			ft_putstr_fd(": cd: HOME not set\n", 2);
			g_var.status = 1;
		}
		change_pwd(&head, exp);
		if (c)
			free(c);
		return ;
	}
	else if (chdir(args[0]) == -1 && ft_strcmp(args[0], "-"))
	{
		cd_derc_err(args);
		return ;
	}
	change_pwd(&head, exp);
	g_var.status = 0;
	if ((*exp)->nbr_cmd > 1)
		exit(g_var.status);
}
