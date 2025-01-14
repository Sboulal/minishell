/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:16:36 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/07 12:09:12 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	close_her(void)
{
	int	fd;

	fd = open("/dev/stdin", O_RDONLY);
	if (fd == -1)
	{
		dup2(1, 0);
		return (0);
	}
	return (close(fd), 1);
}

int	handle_heredoc_nor(char *line, char *limiter, t_mini *cmd, int *fd)
{
	if (!line || !ft_memcmp(line, limiter, ft_strlen(line) + 1))
	{
		if (line)
			free(line);
		cmd->fd[0] = fd[0];
		close(fd[1]);
		return (1);
	}
	return (0);
}

int	handle_nor(char **line, int *fd)
{
	char	*joined_line;

	joined_line = ft_strjoin2(*line, "\n");
	if (write(fd[1], joined_line, ft_strlen(joined_line)) < 0)
		return (-1);
	free(joined_line);
	*line = NULL;
	return (0);
}

char	*expand_herd(char *token, t_envp *env)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup("");
	while (token[i])
	{
		if (token[i] == '$' && (token[i + 1] == '\'' || token[i + 1] == '\"'))
		{
			str = ft_strjoin3(str, to_string(token[i]));
			i++;
		}
		if (!expand_do(token, &i, &str, env))
			continue ;
		else if (expand_do(token, &i, &str, env) == 2)
			break ;
		str = ft_strjoin3(str, to_string(token[i]));
		i++;
	}
	return (free(token), str);
}

int	handle_heredoc(t_mini *cmd, char *limiter, char *file, t_envp *env)
{
	int		expand_mode;
	char	*line;
	int		fd[2];

	free(file);
	if (ft_pipe(fd))
		return (-1);
	expand_mode = is_expand(&limiter);
	while (1)
	{
		sigint_heredoc();
		line = readline("> ");
		if (!close_her())
			break ;
		if (handle_heredoc_nor(line, limiter, cmd, fd))
			return (free(limiter), 1);
		if (expand_mode && line)
			line = expand_herd(line, env);
		if (handle_nor(&line, fd) == -1)
			return (free(limiter), -1);
	}
	free(limiter);
	close(fd[0]);
	return (close(fd[1]), 1);
}
