/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:04:00 by nkhoudro          #+#    #+#             */
/*   Updated: 2022/10/27 19:21:28 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst)
		return ;
	if (*lst == 0)
	{
		(*lst) = new;
		return ;
	}
	while ((*lst)->next != NULL) {
		(*lst) = (*lst)->next;
	}
	(*lst)->next = new;
	new->next = NULL;
}

// int main()
// {
// 	char *p = "hello";
// 	char *d = "everyone";
// 	t_list *l, *l1;
// 	l = ft_lstnew(p);
// 	l1 = ft_lstnew(d);
// 	ft_lstadd_back(&l, l1);
// 	while (l)
// 	{
// 		printf("%s\n", l->content);
// 		l = l->next;
// 	}
// }