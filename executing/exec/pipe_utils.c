/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:51:30 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/28 21:16:50 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	close_file(int **pipfd, int nb_pip)
{
	int	i;

	i = 0;
	while (i < nb_pip)
	{
		close(pipfd[i][READ_END]);
		close(pipfd[i][WRITE_END]);
		i++;
	}
}

void	wait_pid(pid_t *pid, t_exec *exp)
{
	int	i;
	int s;

	i = 0;
	while (i < exp->nbr_cmd)
	{
		waitpid(pid[i++], &s, 0);
	}
	if (WIFEXITED(s))
		g_var.status = WEXITSTATUS(s);
	else if (WIFSIGNALED(s))
		g_var.status = 128 + WTERMSIG(s);
}

int	**incial_pipe(int nb_pip, t_exec *exp)
{
	int	i;
	int	**pipfd;
	int	return_result;

	i = 0;
	pipfd = (int **) malloc(sizeof(int *) * (exp->nbr_cmd - 1));
	while (i < nb_pip)
	{
		pipfd[i] = (int *)malloc(sizeof(int) * 2);
		return_result = pipe(pipfd[i]);
		if (return_result < 0)
		{
			close_pipe(pipfd, i);
			perror("pipe");
			return (NULL);
		}
		i++;
	}
	return (pipfd);
}
