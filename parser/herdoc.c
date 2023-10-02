/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:51:21 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/02 12:21:52 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

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
	(void)limiter;
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
 void	sigint_heredoc(void)
{
	struct sigaction	sa_sigint;

	sa_sigint.sa_handler = &change_flag;
	sigaction(SIGINT, &sa_sigint, NULL);
}

int close_her(void)
{
	int fd;

	fd = open("/dev/stdin", O_RDONLY);
	if(fd == -1)
	{
		dup2(1,0);
		return (0);
	}
	return (close(fd), 1);
}

int	handle_heredoc(t_mini *cmd, char *limiter, char *file, t_envp *env) // void
{
	int		expand_mode;
	char	*line;
	char	*joined_line;
	int		fd[2];

	free(file);
	if (ft_pipe(fd))
		return (-1);
	while (1)
	{
		sigint_heredoc();
		line = readline("> ");
		if(!close_her())
			break;
		if (!line || !ft_memcmp(line, limiter, ft_strlen(line) + 1))
		{
			if (line)
				free(line);
			cmd->fd[0] = fd[0];
			close(fd[1]);
			return(1);
		}
		expand_mode = is_expand(&limiter);
		if (expand_mode &&line)
		    line = heredoc_expansion(line, env);
		joined_line = ft_strjoin2(line, "\n");
		if (write(fd[1], joined_line, ft_strlen(joined_line)) < 0)
			return ( -1);
		free(joined_line);
		line = NULL;
	}
			close(fd[0]);
			close(fd[1]);
	
	return (1); // remove
}

void	ft_close(int fd)
{
	printf("salma");
	if (close(fd) == -1)
		perror("minishell$ ");
}

int	replace_before_name_here(char *new_token, char *token)
{
	int	i;

	i = 0;
	while (token[i] != '$')
	{
		new_token[i] = token[i];
		i++;
	}
	return (i);
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

char	*get_name_here(char *token)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = -1;
	while (token[i])
	{
		name_len = -1;
		if (token[i] == '$')
			name_len = get_name_len(token, i);
		if (name_len == 0)
			token[i] = -1;
		if (name_len > 0)
			break ;
		i++;
	}
	if (name_len == 0 || name_len == -1)
		return (NULL);
	return (ft_substr(token, i, i + name_len));
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
	if (value)
		free(value);
	free(name);
	return (heredoc_expansion(new_line, env));
}
