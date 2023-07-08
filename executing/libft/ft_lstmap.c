/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:28:24 by nkhoudro          #+#    #+#             */
/*   Updated: 2022/10/28 20:07:25 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
void del(void *p)
{
	free(p);
}

void	*f(void *p)
{
	char *c = (char *)p;
	int i = 0;
	while (c[i])
	{
		c[i] = ft_toupper(c[i]);
		i++;
	}
	return (c);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*head;

	if (!lst)
		return (NULL);
	head = NULL;
	while (lst && f)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		lst = lst->next;
		ft_lstadd_back(&head, new);
	}
	return (head);
}

int	main()
{
	t_list	*lst, *head, *temp;

	head = ft_lstnew(ft_strdup("ggggg"));

	lst = ft_lstnew(ft_strdup("everyone"));

	ft_lstadd_front(&head, lst);
	temp = ft_lstmap(head, f, del);

	while (temp)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
}