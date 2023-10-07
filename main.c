/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:12:22 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 02:48:38 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/exec.h"

int	control_line(char *bas, t_exec **exec, char **env, int *k)
{
	int	w;

	w = 0;
	if (bas == 0)
	{
		printf("exit\n");
		exit(0);
	}
	w = 0;
	while (is_isspace(bas[w]) && bas[w])
		w++;
	if (bas[w] == '\0' || ft_strlen(bas) == 0)
	{
		free(bas);
		return (1);
	}
	ft_add_history(bas);
	check_env((*exec), env, k);
	(*exec)->cmd = parse(bas, (*exec)->env);
	return (0);
}

void	herdoc_norm(t_exec *exec, char *bas)
{
	if (exec->cmd)
		free_cmd(exec->cmd);
	free(bas);
	close(g_var.heredoc_flag);
	g_var.heredoc_flag = 0;
	g_var.status = 1;
}

int	main(int ac, char	*av[], char	*env[])
{
	int			k;
	char		*bas;
	t_mini		*head;
	t_exec		*exec;

	k = 0;
	exec = (t_exec *) ft_calloc(sizeof(t_exec));
	check_line(ac, av);
	while (1)
	{
		sig();
		bas = readline("minishell$ ");
		if (control_line(bas, &exec, env, &k))
			continue ;
		if (g_var.heredoc_flag)
		{
			herdoc_norm(exec, bas);
			continue ;
		}
		exec_part(exec, env);
		head = exec->cmd;
		check_fd(head, exec, bas);
	}
	clear_end(exec);
	return (0);
}
