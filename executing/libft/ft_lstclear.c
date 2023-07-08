/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:35:52 by nkhoudro          #+#    #+#             */
/*   Updated: 2022/10/26 23:04:35 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void del(void *p)
// {
// 	free(p);
// }
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cmp;
	if (!lst || !del)
		return ;
	while (*lst)
	{
		cmp = *lst;
		*lst = (*lst)->next;
		del(cmp);
	}
}

// int main()
// {
// 	char *p ="hello";
// 	char *q = "everyone";
// 	t_list *lst, *l, *tmp;
// 	l = ft_lstnew(p);
// 	lst = ft_lstnew(q);
// 	tmp = l;
// 	ft_lstadd_front(&tmp, lst);
// 	printf("%s\n", lst->content);
// 	ft_lstclear(&tmp, del);
// 	printf("%s\n", lst->content);
// 	printf("%s\n", tmp->content);
// 	printf("hello\n");
// 	while (tmp)
// 	{
// 		printf("%s\n", tmp->content);
// 		tmp = tmp->next;
// 	}
// }