/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 01:19:12 by nkhoudro          #+#    #+#             */
/*   Updated: 2022/10/24 21:59:17 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
// int	main(void)
// {
// 	int	i;
// 	t_list *lst = malloc(sizeof(t_list));
// 	t_list *second = malloc(sizeof(t_list));
// 	t_list *third = malloc(sizeof(t_list));
// 	t_list *new = malloc(sizeof(t_list));
// 	lst->content = "ab";
// 	lst->next = second;
// 	second->content = "content";
// 	second->next = third;
// 	third->content = "kbk";
// 	third->next = new;
// 	new->content = "ent";
// 	new->next = NULL;
// 	i = ft_lstsize(lst);
// 	printf("%d", i);
// 	return (0);
// }