/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:51:21 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/15 23:34:03 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lexer.h"

int	is_expand(char **limiter)
{
	if (contains(*limiter, '"') || contains(*limiter, '\''))
	{
		*limiter = quotes_removal(*limiter);
		return (0);
	}
	return (1);
}

void	change_flag(int s)
{
	(void)s;
	g_var.heredoc_flag = dup(0);
	close(0);
}

int	handle_heredoc_suite(t_mini *cmd, char *limiter, char *file, int fd)
{
	close(fd);
	free(limiter);
	fd = open(file, O_RDONLY, 0);
	if (fd == -1)
		return (0);
	cmd->fd[0] = fd;
	free(file);
	return (1);
}

void	check_heredoc(void)
{
	if (g_var.heredoc_flag)
	{
		ft_dup2(g_var.heredoc_flag, 0);
		ft_close(g_var.heredoc_flag);
		g_var.status = 1;
	}
}

void	ft_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		ft_putstr_fd("error",2);
}
 
int	handle_heredoc(t_mini *cmd, char *limiter, char *file, t_envp *env)
{
	int		expand_mode;
	char	*line;
	char	*joined_line;
	int		fd;

	expand_mode = is_expand(&limiter);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (0);
	line = readline("> ");
	while (line && ft_strcmp(line, limiter))
	{
		if (expand_mode && *line)
			line = heredoc_expansion(line, env);
		joined_line = ft_strjoin(line, "\n");
		write(fd, joined_line, ft_strlen(joined_line));
		free(line);
		free(joined_line);
		line = readline("> ");
	}
	free(line);
	check_heredoc();
	return (handle_heredoc_suite(cmd, limiter, file, fd));
}
void	ft_close(int fd)
{
	if (close(fd) == -1)
		ft_putstr_fd("error",2);
}
char	*replace_name_value_here(char *token, char *name, char *value)
{
	char	*new_token;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	new_token = ft_calloc(ft_strlen(token)
			+ (ft_strlen(value) - ft_strlen(name)) + 1);
	i = replace_before_name_here(new_token, token);
	k = i;
	j = 0;
	while (value[j])
	{
		if (value[j] == '$')
			value[j] = -1;
		new_token[i++] = value[j++];
	}
	k += ft_strlen(name);
	while (token[k])
		new_token[i++] = token[k++];
	free(token);
	return (new_token);
}

char	*heredoc_expansion(char *line, t_envp *env)
{
	char	*name;
	char	*value;
	char	*new_line;

	name = get_name_here(line);
	if (!name)
	{
		expands_dollars_dollars(line);
		return (line);
	}
	value = get_env_value(name + 1, env);
	new_line = replace_name_value_here(line, name, value);
	if (*(name + 1) == '?')
		free(value);
	free(name);
	return (heredoc_expansion(new_line, env));
}
