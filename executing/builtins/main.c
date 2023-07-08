/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:36 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/07/08 21:08:48 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

#include <stdio.h>

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
    // printf("%s\n",new->env);
    new->value = str[1];
    new->next = NULL;
    new->prev = NULL;
    // else
    //     new->prev = (*lst);
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
void  add_env(char **env , t_envp **lst)
{
    int i;

    i = 0;
    while (env[i])
    {
        add_back_env(lst, list_env(env[i]));
        i++;
    }
}
int main(int ac, char **av, char **env)
{
    int i;
    t_envp *list_env;

    i = 0;
    (void )ac;
    char *c = av[i];
    c = c + 1;
    add_env(env, &list_env);
    
    while (list_env)
    {
        printf("%s\n", list_env->variable);
        printf("%s\n", list_env->value);
        list_env = list_env->next;
    }
}