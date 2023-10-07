/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:37:01 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/07 02:49:01 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/exec.h"

int	cmt_string(char **env)
{
	int	i;

	i = 0;
	if (!(*env))
		return (i);
	while (env[i])
		i++;
	return (i);
}

char	**creat_string_env(char **env)
{
	char	**env_string;
	int		i;

	i = cmt_string(env);
	env_string = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		env_string[i] = ft_strdup(env[i]);
		i++;
	}
	env_string[i] = NULL;
	return (env_string);
}

int	check_line(int ac, char **av)
{
	if (ac != 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	return (1);
}

int	check_env(t_exec *exec, char **env, int	*k)
{
	if (*k == 0)
	{
		if (*env)
			exec->env_string = creat_string_env(env);
		if (!(*env) && !((exec->env)))
			protect_cmd(&exec);
		else if (!(exec->env) && (*(exec->env_string)))
			creat_env(&exec);
		creat_exp(&exec->exp, exec->env);
		*k = 1;
	}
	return (0);
}

int	exec_part(t_exec *exec, char **env)
{
	if (exec && exec->cmd)
		exec_cmd(&exec, env);
	return (0);
}
