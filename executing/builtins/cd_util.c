/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:09:51 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 05:49:33 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	ft_free(char **ptr)
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
		ft_free(&head->value);
		free((head)->exp);
		head->value = ft_strdup(old);
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
		ft_free(&head->value);
		free((head)->exp);
		head->value = ft_strdup(str);
		head->exp = ft_strjoin("PWD", "=");
		head->exp = ft_strjoin2(head->exp, "\"");
		head->exp = ft_strjoin2(head->exp, head->value);
		head->exp = ft_strjoin2(head->exp, "\"");
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
			ft_putstr_fd(": cd: HOME not set\n", 2);
			g_var.sig_status = 1;
		}
		change_pwd(&head, exp);
		return ;
	}
	else if (chdir(args[0]) == -1 && ft_strcmp(args[0], "-"))
	{
		cd_derc_err(args);
		return ;
	}
	change_pwd(&head, exp);
	g_var.sig_status = 0;
	if ((*exp)->nbr_cmd > 1)
		exit(g_var.sig_status);
}

void	print_env(t_exec *exp)
{
	int	i;

	i = 0;
	if (!exp->env)
	{
		g_var.sig_status = 127;
		return ;
	}
	while (exp->env)
	{
		printf("%s\n", exp->env->env);
		i++;
		exp->env = exp->env->next;
	}
	g_var.sig_status = 0;
}
