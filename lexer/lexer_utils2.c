/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:50:51 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/24 08:37:14 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../headers/lexer.h"

int	check_token(char *s)
{
		size_t	i;

	i = 0;
	if (!s)
		return (-1);
	if (!ft_strcmp(s, "|"))
		return (PIPE_LINE);
	if (!ft_strcmp(s, "<<"))
		return (HERE_DOC);
	if (!ft_strcmp(s, ">>"))
		return (REDIRECTION);
	if (!ft_strcmp(s, "<") || !ft_strcmp(s, ">"))
		return (REDIRECTION);
	if (s[i] && is_operator(s[i]))
		return (OPERATOR);
	else
		return (WORD);
}

static char	*get_id(char *name)
{
	char		*id;
	static int	i;
	char		*id2;
	char		*tmp;

	if (!name)
		return (NULL);
	while (*name && !ft_isalnum(*name))
		name++;
	while (1)
	{
		id2 = ft_itoa(i);
		tmp = ft_strjoin_sep(name, id2, '_');
		id = ft_strjoin("/tmp/.heredoc_", tmp);
		free(id2);
		free(tmp);
		i++;
		if (access(id, F_OK) == -1)
			break ;
		free(id);
	}
	return (id);
}

char	*here_doc_name(void)
{
	char	*name;
	char	*tty_name;

	tty_name = ttyname(0);
	name = get_id(tty_name);
	return (name);
}


