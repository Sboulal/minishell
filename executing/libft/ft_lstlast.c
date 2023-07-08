/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:29:08 by nkhoudro          #+#    #+#             */
/*   Updated: 2022/10/26 23:05:05 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
// int main()
// {
// 	char *p ="hello";
// 	char *q = "everyone";
// 	t_list *lst, *l, *tmp;
// 	l = ft_lstnew(p);
// 	lst = ft_lstnew(q);
// 	ft_lstadd_front(&tmp, lst);
// 	// printf("%s\n", lst->content);
// 	tmp = ft_lstlast(l);
// 	printf("%s\n", tmp->content);
// 	// while (tmp)
// 	// {
// 	// 	printf("%s\n", tmp->content);
// 	// 	tmp = tmp->next;
// 	// }
// }