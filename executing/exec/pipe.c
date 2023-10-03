/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:43:46 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/28 20:58:31 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	edit_shlvl(t_exec **exp)
{
	t_envp	*head;
	int		nb;
	char	*str;

	if (!(*exp)->env)
		return ;
	head = (*exp)->env;
	while (head && ft_strcmp(head->variable, "SHLVL") != 0)
		head = head->next;
	if (head)
	{
		nb = ft_atoi(head->value) + 1;
		if (nb == 1000)
			nb = 1;	
		head->value = ft_itoa(nb);
		str = ft_strjoin(head->variable, "=");
		head->env = ft_strdup(ft_strjoin(str, head->value));
		edit_in_string(head);
	}
}

int	error_fork(pid_t pid, int **pipfd, int nbr_cmd)
{
	if (pid < 0)
	{
		close_file(pipfd, nbr_cmd - 1);
		perror("fork");
		return (-1);
	}
	return (0);
}

void	norm_pipe(t_mini *head, int **pipfd, t_exec **exp, int j)
{
	if (head->fd[READ_END] > 2)
		dup2(head->fd[READ_END], READ_END);
	else if (j > 0)
		dup2(pipfd[j - 1][READ_END], READ_END);
	if (head->fd[WRITE_END] > 2)
		dup2(head->fd[WRITE_END], WRITE_END);
	else if (j < (*exp)->nbr_cmd - 1)
		dup2(pipfd[j][WRITE_END], WRITE_END);
	if (head->fd[READ_END] > 2)
		close(head->fd[READ_END]);
	if (head->fd[WRITE_END] > 2)
		close(head->fd[WRITE_END]);
	close_file(pipfd, (*exp)->nbr_cmd - 1);
	buil_exec_pipe(exp, head);
	// if (ft_strcmp(head->cmd, "exit") == 0)
		exit(g_var.status);
}
void close_pipe(int **pip, int j)
{
	int i;

	i = 0;
	while (i < j)
	{
		close(pip[i][0]);
		close(pip[i][1]);
		i++;
	}
}
void	use_pipe(t_exec **exp, t_mini *cmd)
{
	pid_t	*pid;
	int		**pipfd;
	int		j;
	t_mini	*head;

	head = cmd;
	j = 0;
	
	if (!*exp || !cmd)
		return ;
	pid = (pid_t *)malloc((sizeof(pid_t) * ((*exp)->nbr_cmd + 1)));
	pipfd = incial_pipe((*exp)->nbr_cmd - 1, (*exp));
	if (!pipfd)
		return ;
	while (head)
	{
		pid[j] = fork();
		if (error_fork(pid[j], pipfd, (*exp)->nbr_cmd) < 0)
			return ;
		else if (pid[j] == 0)
			norm_pipe(head, pipfd, exp, j);
		j++;
		head = head->next;
	}
	close_file(pipfd, (*exp)->nbr_cmd - 1);
	int i;

	i = 0;
	while (i < (*exp)->nbr_cmd - 1)
	{
		free(pipfd[i]);
		i++;
	}
	free(pipfd);
	wait_pid(pid, (*exp));
	free(pid);
}
