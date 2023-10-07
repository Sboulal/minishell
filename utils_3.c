/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:38:50 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/07 02:49:05 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	check_fd(t_mini *head, t_exec *exec, char *bas)
{
	while (head)
	{
		if (head->fd[READ_END] > 2)
			close(head->fd[READ_END]);
		if (head->fd[WRITE_END] > 2)
			close(head->fd[WRITE_END]);
		head = head->next;
	}
	if (exec->cmd)
		ft_lstclear_cmd(&exec->cmd);
	if (bas)
		free(bas);
}

int	ft_read(char *line)
{
	int	w;

	line = readline("minishell$ ");
	if (line == 0)
	{
		printf("exit\n");
		exit(0);
	}
	w = 0;
	while (is_isspace(line[w]) && line[w])
		w++;
	return (0);
}

void	clear_end(t_exec	*exec)
{
	tabfree(exec->env_string);
	ft_lstclear_env(&exec->env);
	ft_lstclear_exp(&exec->exp);
	free(exec);
}
