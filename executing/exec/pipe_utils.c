/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:51:30 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/24 00:26:44 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"
 void close_all_fd(t_mini *head)
 {
	 int i;
	if(!head)
		return;
	 i = 0;
	 while (i < 2)
	 {
		 if (head->fd[i] > 2)
			 close(head->fd[i]);
		 i++;
	 }
 }
void	close_file(int **pipfd, int nb_pip)
{
	int	i;

	i = 0;
	while (i < nb_pip - 1)
	{
		close(pipfd[i][READ_END]);
		close(pipfd[i][WRITE_END]);
		i++;
	}
	
}

void	wait_pid(pid_t *pid, t_exec *exp)
{
	int	i;
	int	status;
	i = 0;
	if (exp->nbr_cmd == 1)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			g_var.status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
			{
				printf("Quit: %d\n", SIGQUIT);
				g_var.status = 131;
			}
			else if (WTERMSIG(status) == SIGINT)
			{
				printf("\n");
				g_var.status = 130;
			}
			
		}
	}
	else if (exp->nbr_cmd > 1)
	{
		while (i < exp->nbr_cmd - 1)
		{
			waitpid(pid[i], &status, 0);
			if (WIFEXITED(status))
				g_var.status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
				{
					printf("Quit: %d\n", SIGQUIT);
					g_var.status = 131;
				}
				else if (WTERMSIG(status) == SIGINT)
				{
					printf("\n");
					g_var.status = 130;
				}
				
			}
			i++;
		}
	}
}

// {
// 	int	i;
	
// 	i = 0;
// 	while (i < exp->nbr_cmd)
// 		waitpid(pid[i++], NULL, 0);
// }

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
