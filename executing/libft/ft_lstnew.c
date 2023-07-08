/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 21:54:30 by nkhoudro          #+#    #+#             */
/*   Updated: 2022/10/25 12:20:05 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}

// int	main(void)
// {
// 	char *data = "hello, i'm a data";
//         t_list *l = ft_lstnew(data);

// 	while (l != NULL)
// 	{
// 		printf("%s", l->content);
// 		l = l -> next;
// 	}
// 	return (0);
// }