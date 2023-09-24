/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chekcs_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:24:58 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/24 04:43:38 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lexer.h"

void    close_all_fds(t_mini *head)
{
    t_mini    *tmp;
    if (!head)
        return ;
    tmp = head;
    while (tmp->next)
    {
        if (tmp->fd[1] != -4 && tmp->fd[1] != 0)
            ft_close(tmp->fd[1]);
        if (tmp->fd[0] != -4 && tmp->fd[0] != 0)
            ft_close(tmp->fd[0]);
        tmp = tmp->next;
    }
}