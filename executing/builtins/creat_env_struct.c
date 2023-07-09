/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:38:56 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/07/09 11:39:16 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

t_envp *list_env(char *env)
{
    t_envp *new;
    char **str;
    int i;
    
    i = 0;
    if (!env)
        return (NULL);
    new = (t_envp *)malloc(sizeof(t_envp));
    if (!new)
        return (NULL);
    new->env = env;
    str = ft_split(env, '=');
    new->variable = str[0];
    new->value = str[1];
    new->next = NULL;
    new->prev = NULL;
    return (free(str),new);
}
t_envp *ft_lst(t_envp *lst)
{
    	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
void add_back_env(t_envp **lst, t_envp *new)
{
    if (!lst || !new)
		return ;
	if (*lst == 0)
	{
		(*lst) = new;
		return ;
	}
	ft_lst(*lst)->next = new;
}
void  creat_env(char **env , t_envp **lst)
{
    int i;

    i = 0;
    while (env[i])
    {
        add_back_env(lst, list_env(env[i]));
        i++;
    }
}
void print_env(t_envp *lst)
{
    while (lst)
    {
        printf("%s\n", lst->env);
        lst = lst->next;
    }
}