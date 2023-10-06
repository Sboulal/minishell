/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:46:28 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/06 22:14:33 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	change_pwd_dir(void)
{
	ft_putstr_fd("cd: error retrieving current directory", 2);
	ft_putstr_fd(": getcwd: cannot access parent", 2);
	ft_putstr_fd(":directories: No such file or directory\n", 2);
	g_var.status = 126;
}

void	change_pwd_free(t_envp	*head, char	*str)
{
	if (head->value && *str)
	{
		ft_free(&head->value);
		(head)->value = ft_strdup(str);
	}
	free((head)->env);
	(head)->env = ft_strjoin("PWD=", str);
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
		change_pwd_free(head, str);
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
		ft_free(&head->value);
		free((head)->env);
		(head)->value = ft_strdup(str);
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
