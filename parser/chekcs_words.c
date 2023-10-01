/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chekcs_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:24:58 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/28 20:58:31 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	close_all_fds(t_mini *head)
{
	t_mini	*tmp;

	if (!head)
		return ;
	tmp = head;
	while (tmp->next)
	{
		if (tmp->fd[1] != 1)
			ft_close(tmp->fd[1]);
		if (tmp->fd[0] != 0)
			ft_close(tmp->fd[0]);
		tmp = tmp->next;
	}
}
