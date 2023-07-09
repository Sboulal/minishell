/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:36 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/07/09 16:03:56 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

#include <stdio.h>
// t_mini *cmd_new(char **av)
// {
//     t_mini *new;
//     int i;
//     int k;
//     int j;
//     int len 

//     i = 1;
//     char **str;
//     j = 2;
//     new = (t_mini *)malloc(sizeof(t_mini));
//     new->cmd = av[1];
//     while (av[j][0] == '-' && av[j][0] != '-')
//     {
//         len = ft_strlen(av[2]);
//         len = len - 1;
//         new->nbr_arg = len;
//         new->arg = (char **)malloc(sizeof(char *) * (len + 1));
//         i = 1;
//         while (av[j][i])
//         {
//             new->arg[i] = malloc(sizeof(char));
//             new->arg[i][k] = 
//             i++;
//         }
//         j++;
//     }
    
// }
// void    creat_command(char **av, t_mini **cmd)
// {
//     cmd_new()
// }
void  add_env(t_envp **env, char *data)
{
    if (ft_strchr(data, '='))
        add_back_env(env, list_env(data));
}
void  delete_var_env(char *data)
{
    if (!ft_strchr(data, '='))
        free(getenv(data));
}
int main(int ac, char **av, char **env)
{
    int i;
    char *cmd;
    t_envp *list_env;

    i = 1;
    if(ac != 1)
   {
	    while(av[i])
	    {
	    	printf("%s: ", av[i]);
	    	i++;
	    }
	    printf("No such file or directory\n");
        return (0);
    }
	i = 0;
    while(1)
    {
         cmd = readline("minishell$ ");
        if(cmd && *cmd)
          add_history(cmd);
        creat_env(env, &list_env);
        if (ft_strncmp(cmd, "env", 3) == 0)
        {
            print_env(list_env);
            // exit(1);
        }

        if (ft_strncmp(cmd, "export", 6) == 0)
        {
            add_env(&list_env, av[i + 1]);
            print_env(list_env);
            // exit(1);
        }

        if (ft_strncmp(cmd, "unset", 5) == 0)
        {
            delete_var_env(av[i + 1]);
            print_env(list_env);
            // exit(1);
        }
	}

    // if (ft_strncmp(cmd, "unset", 5) == 0)
    // {
    //     print_env(list_env);
    //     exit(1);
    // }
    // printf("%s\n", getenv(av[i]));
}