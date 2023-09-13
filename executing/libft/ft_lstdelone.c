/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:26:28 by nkhoudro          #+#    #+#             */
/*   Updated: 2022/10/26 21:50:45 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// void del(void *p)
// {
// 	free(p);
// }
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst && del)
	{
		del(lst-> content);
		free(lst);
	}
}
// int main()
// {
// 	t_list **lst = NULL;
// 	t_list *second = NULL;
// 	t_list *third = NULL;
// 	t_list *new = NULL;
// 	*lst = ft_lstnew("d");
// 	second = ft_lstnew("a");
// 	third = ft_lstnew("m");
// 	new = ft_lstnew("n");
// 	lst = &second;
// 	ft_lstadd_front(lst, new);
// 	ft_lstdelone(lst, del);
// 	while (lst)
// 	{
// 		printf("%d", lst->content);
// 		lst = lst->next;
// 	}
// }