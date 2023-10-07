/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:35:27 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/07 02:44:31 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/exec.h"

int	is_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

void	ft_lstclear_cmd(t_mini **lst)
{
	t_mini	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		if (tmp)
		{
			if (tmp->arg)
			{
				tabfree(tmp->arg);
				tmp->arg = NULL;
			}
			if (tmp->cmd)
			{
				free(tmp->cmd);
				tmp->cmd = NULL;
			}
			free(tmp);
			tmp = NULL;
		}
	}
}

void	ft_lstclear_exp(t_export **lst)
{
	t_export	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}

void	ft_lstclear_env(t_envp **lst)
{
	t_envp	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}

void	ft_add_history(char *bas)
{
	char	*ptr;

	ptr = bas;
	if (!bas) 
		return ;
	while (*bas && is_isspace(*bas))
		bas++;
	if (*bas != 0)
		add_history(ptr);
}
