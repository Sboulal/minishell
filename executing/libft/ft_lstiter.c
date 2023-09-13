/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:47:19 by nkhoudro          #+#    #+#             */
/*   Updated: 2022/10/27 19:21:58 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	f(void *p)
// {
// 	char *c = (char *)p;
// 	while (*c)
// 	{
// 		 ft_toupper(*c);
// 		printf("%c\n", *c);
// 		c += 1;
// 	}

// }
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst-> content);
		lst = lst->next;
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
// 	ft_lstiter(tmp, f);
// 	printf("%s\n", lst->content);
// 	while (tmp)
// 	{
// 		printf("%s\n", tmp->content);
// 		tmp = tmp->next;
// 	}
// }