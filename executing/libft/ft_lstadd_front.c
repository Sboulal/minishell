/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 23:29:13 by nkhoudro          #+#    #+#             */
/*   Updated: 2022/10/26 21:12:42 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
// int main()
// {
// 	char *d = "hello";
// 	char *c = "everyone";
// 	t_list *l, *l1;
// 	l = ft_lstnew(d);
// 	l1 = ft_lstnew(c);
// 	ft_lstadd_front(&l, l1);
// 	while(l)
// 	{
// 		printf("%s", l->content);
// 		l = l->next;
// 	}
// }