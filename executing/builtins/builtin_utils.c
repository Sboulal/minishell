/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:57:58 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/06 22:01:20 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	ft_strcmp1(const char *s1, const char *s2)
{
	unsigned char	*my_s1;
	unsigned char	*my_s2;
	size_t			i;

	if (!s1 || !s2)
		return (5);
	i = 0;
	my_s1 = (unsigned char *)s1;
	my_s2 = (unsigned char *)s2;
	while ((my_s1[i] != '\0' || my_s2[i] != '\0'))
	{
		if (my_s1[i] != my_s2[i])
			return (my_s1[i] - my_s2[i]);
		i++;
	}
	return (0);
}

void	sort_list(t_export **exp)
{
	t_export	*head;
	t_export	*tomp;

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
	if (ft_strcmp1(cmd->cmd, "./minishell") == 0)
		edit_shlvl(exp);
	if (!cmd->cmd || ((ft_strcmp(cmd->cmd, "env") != 0) && \
		ft_strcmp(cmd->cmd, "exit") != 0
			&& ft_strcmp(cmd->cmd, "echo") != 0 
			&& ft_strcmp(cmd->cmd, "pwd") != 0
			&& ft_strcmp(cmd->cmd, "unset") != 0 
			&& ft_strcmp(cmd->cmd, "cd") != 0
			&& ft_strcmp(cmd->cmd, "export") != 0))
		exec_pipe(exp, cmd);
	else
		builtins(exp, cmd);
}
